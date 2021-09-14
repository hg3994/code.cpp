
/*

Harshit Gupta | 7th August, 2021
---------------------------------

Problem Statement:
	You are given an integer array nums and you have to return a new counts array. The counts array 
	has the property where counts[i] is the number of smaller elements to the right of nums[i].


Example 1:
	Input: nums = [5,2,6,1]
	Output: [2,1,1,0]
	Explanation:
	To the right of 5 there are 2 smaller elements (2 and 1).
	To the right of 2 there is only 1 smaller element (1).
	To the right of 6 there is 1 smaller element (1).
	To the right of 1 there is 0 smaller element.

Example 2:
	Input: nums = [-1]
	Output: [0]

Example 3:
	Input: nums = [-1,-1]
	Output: [0,0]

https://leetcode.com/problems/count-of-smaller-numbers-after-self/  
------

Solution: 
	1. Segment Trees Solution
		- TODO

    TC: O(NlogM) where N be the length of nums and M be the difference between the maximum and minimum values in nums.
    SC: O(M), since we need, at most, an array of size 2M+2 to store the segment tree.

	2. Merge Sort Solution:

	Time Complexity: O(Nlog(N)).
	Space COmplexity:  O(N), since we need a constant number of arrays of size O(N).


Paradigm:
---
    NOTE: 

    Similar Questions:
        1. https://leetcode.com/problems/how-many-numbers-are-smaller-than-the-current-number/
			- Given the array nums, for each nums[i] find out how many numbers in the array are smaller than it. That is, 
				for each nums[i] you have to count the number of valid j's such that j != i and nums[j] < nums[i]
        	- Example 1:
				Input: nums = [8,1,2,2,3]
				Output: [4,0,1,1,3]
				Explanation: 
					For nums[0]=8 there exist four smaller numbers than it (1, 2, 2 and 3). 
					For nums[1]=1 does not exist any smaller number than it.
					For nums[2]=2 there exist one smaller number than it (1). 
					For nums[3]=2 there exist one smaller number than it (1). 
					For nums[4]=3 there exist three smaller numbers than it (1, 2 and 2).
        	- This is comparatively a simpler question than the above

*/


// Approach 2: Merge Sort
class Solution {
public:
    
    void print_arr(string message, vector<int> a){
        cout<<message<<" ";
        for(auto e: a){
            cout<<e<<" ";
        }
        cout<<endl;
    }
    
    vector<int> countSmaller(vector<int>& nums) {
        int n = nums.size();
        vector<int> result(n);
        vector<int> indices(n);
        
        for(int i=0; i<n; i++){
            indices[i] = i;
        }
        
        // print_arr("Indices: ", indices);
        mergeSort(indices, 0, n, result, nums);
        // print_arr("Indices: ", indices);
        
        return result;
    }
    
    void mergeSort(vector<int>& indices, int left, int right, vector<int>& result, vector<int>& nums){
        // cout<<"MergeSort: left: "<<left<<" right: "<<right<<endl;
        if (right-left <= 1){
            return;
        }
        int mid = left + (right-left)/2;
        mergeSort(indices, left, mid, result, nums);
        mergeSort(indices, mid, right, result, nums);
        merge(indices, left, right, mid, result, nums);
    }
    
    void merge( vector<int>& indices, int left, int right, int mid, vector<int>& result, vector<int>& nums){
        // cout<<"Merge: left: "<<left<<" right: "<<right<<" mid: "<<mid<<endl;
        // merge [left, mid) and [mid, right)
        int i = left; // starting index for left array
        int j = mid;  // starting index for right array
        vector<int> temp; // use temp to temporarily store sorted array
        
        while(i<mid && j<right){
            // cout<<"i: "<<i<<" j: "<<j<<" nums[indices[i]]: "<<nums[indices[i]]<<" nums[indices[j]]: "<<nums[indices[j]]<<endl;
            if (nums[indices[i]] <= nums[indices[j]]) {
                // j-mid nums have jumped to the left side of indices[i]
                // cout<<nums[indices[i]]<<" <= "<<nums[indices[j]]<<endl;
                result[indices[i]] += j-mid;
                temp.push_back(indices[i]);
                i++;
            }
            else {
                // cout<<nums[indices[i]]<<" > "<<nums[indices[j]]<<endl;
                temp.push_back(indices[j]);
                j++;
            }
            // print_arr("Temp: ", temp);
        }
        
        while(i<mid){
            result[indices[i]] += j-mid;
            temp.push_back(indices[i]);
            i++;
        }
        while(j < right){
            temp.push_back(indices[j]);
            j++;
        }
        // print_arr("Indices: ", indices);
        // move elements from temp to indices arr.
        move(temp.begin(), temp.end(), indices.begin() + left);
        
        // print_arr("Indices: ", indices);
        // print_arr("Temp: ", temp);
        // print_arr("Result: ", result);
        // cout<<"****"<<endl;
    }
};


// ------------------------------------------------------
// SIMILAR QUESTION -1 - Count Number Smaller Than Itself
// ------------------------------------------------------

// Array:  [8,1,2,2,3]
// Index:   0,1,2,3,4
// Sorted: [1,2,2,3,8]

// We can use counting sort in O(n) since it is given that 0<=nums[i]<=100 but this is a more general solution.
class Solution {
public:
    vector<int> smallerNumbersThanCurrent(vector<int>& nums) {
        vector<int> orig = nums;
        vector<int> ans;
        sort(nums.begin(), nums.end());
        for(int i=0; i<orig.size(); i++){
            int index = lower_bound(nums.begin(), nums.end(), orig[i]) - nums.begin();
            ans.push_back(index);
        }
        return ans;
    }
};