
/*

Harshit Gupta | 28th May, 2021
---------------------------------

C++ program for "Search in a rotated sorted array"

There is an integer array nums sorted in ascending order (with distinct values).
Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) 
such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). 

For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.
You must write an algorithm with O(log n) runtime complexity.

Example 1:
    Input: nums = [4,5,6,7,0,1,2], target = 0
    Output: 4
Example 2:
    Input: nums = [4,5,6,7,0,1,2], target = 3
    Output: -1
Example 3:
    Input: nums = [1], target = 0
    Output: -1

https://leetcode.com/problems/search-in-rotated-sorted-array/
------

Solution: The trick is to find the index of the lowest element using binary search
    and then use binary search in the required side of it to find the target

Time Complexity: O(logn)
Space Complexity: O(1)

Paradigm: Binary Search
---
  NOTE: One can do it in just 1 pass as well, read: https://leetcode.com/problems/search-in-rotated-sorted-array/solution/

*/

class Solution {
    
public:
    int search(vector<int>& v, int target) {
        int n = v.size();
        int low = 0, high = n-1;
    
        // Finding the index of the lowest element
        while(low < high){
            int mid = low + (high-low)/2;
            if (v[mid] > v[high])
                low = mid+1;
            else
                high = mid;
        }
        // Now low = high = index of the lowest element
        int index_lowest = low;
        if (target == v[index_lowest])
            return index_lowest;
        
        // Now we need to figure out which side we need to search for target, left or right of lowest element
        // we do that by comparing the target with the first element and we should know in which half it should lie
        if (index_lowest == 0)
            low=0, high=n-1;
        else if (target >= v[0])
            low=0, high=index_lowest-1;
        else if (target < v[0])
            low=index_lowest, high=n-1;
        
        // Now do binary search from low to high
        while(low <= high){
            int mid = low + (high-low)/2;
            if(v[mid] == target)
                return mid;
            else if (v[mid] > target)
                high = mid-1;
            else 
                low = mid+1;
        }
        
        // If it reaches here means that we could not find the element in the array
        return -1;
        
    }
};