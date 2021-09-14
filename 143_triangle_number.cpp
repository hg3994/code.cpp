
/*

Harshit Gupta | 15th July, 2021
---------------------------------

Problem Statement:
    Given an integer array nums, return the number of triplets chosen from the array that 
        can make triangles if we take them as side lengths of a triangle.

Example 1:
    Input: nums = [2,2,3,4]
    Output: 3
    Explanation: Valid combinations are: 
        2,3,4 (using the first 2)
        2,3,4 (using the second 2)
        2,2,3

Example 2:
    Input: nums = [4,2,3,4]
    Output: 4

https://leetcode.com/problems/valid-triangle-number/
------

Solution: https://leetcode.com/problems/valid-triangle-number/solution/
    1. Brute Force
    2. Using Binary Search
    3. Choosing Smart Value of K

  TC: O(n2)
  SC: O(1)

Paradigm:
---
  NOTE: 

*/


// Approach 3: O(n2) solution
// Note that for every i, j runs from i+1 till n 
// But K runs from j+1 till n for all the is and not js.
// We use the older values of k and then run from there till n and hence this is not O(n3) solution.
// Eg: [5,8,9,10,13,20], 
// i=0 (5), j=1(8), then k would stop at 13 since 5+8>13 would break the while loop, count becomes = 4-1-1 = 2
// i=0 (5), j=2(9), then k would stop at 20 since 5+9>20 would break the while loop, count becomes += 5-2-1 = 4
// ... for all values of i and j k would remain at 20 since k must be < n and so only i and j would iterate
// If you see, k only iterates over the array once and not for all values of i and j.. 
// Loop of kk and jj will be executed O(n^2) times in total, because, we do not reinitialize the value of k for a new value of j chosen(for the same i)
// Think like this: For the same 'i', we choose 'j' 'n' times but 'k' is selected only once... So, 'n' for 'i' and 'n' for 'j' makes it O(n2). 
class Solution {
public:
    
    int triangleNumber(vector<int>& nums) {
        int count = 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        for(int i=0; i<n-2; i++){
            int k = i+2;
            for(int j=i+1; j<n-1 && nums[i]!=0; j++){
                while(k < n && nums[i] + nums[j] > nums[k])
                    k++;
                count += k-j-1;
            }
        }
        return count;
    }
};

// Approach 2: O(n2 logn)
class Solution {
public:
    // If we are able to find this RIGHT LIMIT VALUE of k(indicating the element just greater than nums[i] + nums[j]), 
    // we can conclude that all the elements in nums array in the range (j+1, k-1)(both included) satisfy the required inequality. 
    // Thus, the count of elements satisfying the inequality will be given by (k-1) - (j+1) + 1 =k−j−1.
    // i:0 (5) j:1 (8)   5 8 9 10 11 11 13 20    call and search k in BS(2, 7)
    // here we will return index 6 (13) since that is equal to 8+5=13 & we are interested in k-1
    // Now we will count elements from j+1 till k-1 = (9, 10, 11, 11) = 4
    int firstGreaterOrEqual(vector<int>& nums, int l, int r, int target){
        while(l<=r){
            int mid = l+(r-l)/2;
            if(nums[mid] >= target)
                r = mid-1;
            else
                l = mid+1;
        }
        return l;
    }

    int triangleNumber(vector<int>& nums) {
        int count = 0;
        int n = nums.size();
        sort(nums.begin(), nums.end());
        
        for(int i=0; i<n-2; i++){
            int k  = i+2;
            for(int j=i+1; j<n-1 && nums[i]!=0; j++){
                k = firstGreaterOrEqual(nums, k, n-1, nums[i]+nums[j]);
                count += (k-j-1);
            }
        }
        return count;
    }
};


// Approach 1: Better Brute Force (TLE) - O(n3)
class Solution {
public:
    int triangleNumber(vector<int>& arr) {
        int n = arr.size(), ans=0;
        sort(arr.begin(), arr.end());
        for(int i=0; i<n-2; i++){
            for(int j=i+1; j<n-1; j++){
                for(int k=j+1; k<n; k++){
                    if(arr[i]+arr[j] > arr[k])
                        ans++;
                    else 
                        break;
                }
            }
        }
        return ans;
    }
};