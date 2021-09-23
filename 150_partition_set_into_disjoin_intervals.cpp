
/*

Harshit Gupta | 23rd July, 2021
---------------------------------

Problem Statement:

Given an array nums, partition it into two (contiguous) subarrays left and right so that:

Every element in left is less than or equal to every element in right.
left and right are non-empty.
left has the smallest possible size.
Return the length of left after such a partitioning.  It is guaranteed that such a partitioning exists.

Example 1:
	Input: nums = [5,0,3,8,6]
	Output: 3
	Explanation: left = [5,0,3], right = [8,6]

Example 2:
	Input: nums = [1,1,1,0,6,12]
	Output: 4
	Explanation: left = [1,1,1,0], right = [6,12]

------

Solution: 
	Instead of checking whether all(L <= R for L in left for R in right), let's check whether max(left) <= min(right).

	1. Create the maxLeft array which tells the maximum to the left of every element
	2. Create the minRight array which tells the minimum to the right of every element.
	3. Any element which has maxleft <= minright is what we are looking for

  TC: O(n)
  SC: O(n)

Paradigm:
---
  NOTE: 

*/


// arr:     [5,0,3,8,6]
// maxleft: [5,5,5,8,8]
// minright:[0,0,3,6,6]
// At i=2, maxleft (5) <= minright(6), so that is the ans
class Solution {
public:
    int partitionDisjoint(vector<int>& nums) {
        int n = nums.size();
        vector<int> maxLeft(n,0), minRight(n,0);
        
        maxLeft[0] = nums[0];
        for (int i = 1; i < n; ++i)
            maxLeft[i] = max(maxLeft[i-1], nums[i]);
        
        minRight[n-1] = nums[n-1];
        for(int i=n-2; i>=0; i--)
            minRight[i] = min(minRight[i+1], nums[i]);

        for (int i = 1; i < n; ++i)
            if(maxLeft[i-1] <= minRight[i])
                return i;
        
        return -1;
    }
};