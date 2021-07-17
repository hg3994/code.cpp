
/*

Harshit Gupta | 17th July, 2021
---------------------------------

Problem Statement:

You are given an array arr which consists of only zeros and ones, divide the array into 
	three non-empty parts such that all of these parts represent the same binary value.

------

Solution: 
	Approach 1:
		1. Calculate the number of 1s.
		     a. If number of 1s is not a multiple of 3, no solution.
		     b. If number of 1s is 0, solution is {0, n-1}
		2. Calculate the number of one to be distributed in the three parts T=S/3
		3. We can find the position of the 1st, T-th, T+1-th, 2T-th, 2T+1-th, and 3T-th one.
		     a. The positions of these ones form 3 intervals: [i1, j1], [i2, j2], [i3, j3].
		4. The intervals contain a few 1s and 0s in between the 1s (1101), so the number in all 
			three intervals should be exactly same. If not, No Solution!
		5. The zeros after j3 must be included in each part: say there are z of them
		     a. The remaining 0s after intervals must be used to add z zeros after the intervals
		     b. If there are extra zeros, then we can consider pad them before the 
		         next number so that it doesnt change the value
		6. If z > the avaiable zeros between the intervals, no solution
		     a. Else the solution is {j1+z, j2+z+1}
  
  TC: O(n)
  SC:

	Approach 2:
		1. Key obseration is that three parts must have same number and pattern of 1s except 
			the leading part.
		2. Count how many ones (if num%3!=0 return [-1,-1])
		3. Search from right side to left, until we found num/3 1s. 
			This index is not final answer, but it defines patten of 1s
		4. From left, ignore leading 0s, and then match the pattern found in step 2, 
			to get the first EndIndex
		5. Do another matching to found second EndIndex

Paradigm:
---
  NOTE: 

*/

// Approach 1:
class Solution {
public:
    vector<int> threeEqualParts(vector<int>& arr) {
        int n = arr.size();
        int ones = 0;
        for(auto a: arr)
            ones +=a;
        if(ones%3 != 0)
            return {-1,-1};
        if(ones == 0)
            return {0, n-1};
        int ones_each_part = ones/3;
        
        int i1=-1, j1=-1,i2=-1, j2=-1, i3=-1, j3=-1, sum=0;
        for(int i=0; i<n; i++){
            if (arr[i] == 1){
                sum +=1;
                if(sum == 1)                   i1 = i;
                if(sum == ones_each_part)      j1 = i;
                if(sum == ones_each_part+1)    i2 = i;
                if(sum == ones_each_part*2)    j2 = i;
                if(sum == ones_each_part*2+1)  i3 = i;
                if(sum == ones_each_part*3)    j3 = i;
            }
        }
        // 0..0[i1..j1]00..00[i2..j2]00..00[i3..j3]00..
        // Also, the intervals contain a few 1s and 0s in between the 1s (1101), so the number in all three intervals should be exactly same.
        // if(arr.substr(i1, j1-i1+1) != arr.substr(i2, j2-i2+1)) return {-1,-1};
        // if(arr.substr(i2, j2-i2+1) != arr.substr(i3, j3-i3+1)) return {-1,-1};
        vector<int> part1(arr.begin()+i1, arr.begin()+j1+1);
        vector<int> part2(arr.begin()+i2, arr.begin()+j2+1);
        vector<int> part3(arr.begin()+i3, arr.begin()+j3+1);
        
        if (part1 != part2) return {-1, -1};
        if (part2 != part3) return {-1, -1};
        
        // If zeros are plugged ahead of the intervals, then no prob 
        // but if placed after the intervals, then it is a prob
        // so we must select the number of zeros after j3 both the other 
        // two intervals as well.
        // num of zeroes after interval1, interval2, and interval3
        // 00-1101-0000-1101-000-1101-00
        // 00110100-00110100-0110100 => [7, 16]
        int x = i2-j1-1;
        int y = i3-j2-1;
        int z = n-j3-1;
        
        if(z>x || z>y) return {-1, -1};
        return {j1+z, j2+z+1};
    }
};


// Approach 2: In Java

public int[] threeEqualParts(int[] A) {
	int numOne = 0;
	for (int i: A){
		if (i==1) numOne++;
	}
    
    int[] noRes = {-1, -1};
    if (numOne == 0) return new int[]{0,2};
    if (numOne%3 != 0) return noRes;
    
    //find index of starting 1 of third string
    int idxThird=0;
	int temp = 0;
    for (int i = A.length-1; i>=0; i--){
        if (A[i]==1){
            temp++;
            if (temp == numOne / 3){
                idxThird = i;
                break;
            }
        } 
    }
    
    int res1 = findEndIdx(A, 0, idxThird);
    if (res1<0) return noRes;
    
    int res2 = findEndIdx(A, res1+1, idxThird);
    if (res2<0) return noRes;
    
    return new int[]{res1, res2+1};
}

//right is the pattern to compare to.  
//return EndIdx of left pattern that matches right side.
private int findEndIdx(int[] A, int left, int right){
    while (A[left]==0) left++;
    while (right < A.length){
        if (A[left]!=A[right]) return -1;
        left++;
        right++;            
    }
    return left-1;
}