
/*

Harshit Gupta | 10th June, 2021
---------------------------------

C++ program for 

Given an array of positive integers nums and a positive integer target, return the minimal length of a contiguous subarray
    of which the sum is greater than or equal to target. If there is no such subarray, return 0 instead.

Example 1:
    Input: target = 7, nums = [2,3,1,2,4,3]
    Output: 2
    Explanation: The subarray [4,3] has the minimal length under the problem constraint.

Example 2:
    Input: target = 4, nums = [1,4,4]
    Output: 1

Example 3:
    Input: target = 11, nums = [1,1,1,1,1,1,1,1]
    Output: 0


https://leetcode.com/problems/minimum-size-subarray-sum/
------

Solution: Sliding Window
    1. Slide Window and keep checking the sum of all elements in the window with the length of window
    2. If at any point, we get the sum is lesser length, update it.
    3. Outer loop expands the window
    4. Inner loop shortens it till the condition sum>=target holds true
    
    THIS SOLUTION DEALS ONLY WITH POSITIVE INTEGERS!!!

Similar Questions:
    1. https://leetcode.com/problems/shortest-subarray-with-sum-at-least-k/
        - Same question with negative integers as well.
        - TODO

TC: O(n)
SC: O(1)

Paradigm: Sliding Window
---
  NOTE: 

*/


class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        
        int i=0; // Start of sliding window (i..j-1)
        int j=0; // Next char of the sliding window, helps in adding elemens to the window
        int minlen = nums.size() + 1;
        int sum = 0;
        int currentLen = 0;
        
        // Till we reach the end
        while(j!=nums.size()){
            // Add the number to sum variable & increase the len of the window
            sum += nums[j];
            currentLen++;
            
            // while the sum is >= target, check if this window is the minimum length window and update the minlength
            // try decreasing the window from start and see if sum still is greater than the target. if yes, then we have a smaller window with sum>=target
            // Keep moving and trying till we update result to the smallest window
            while(sum >= target){
                minlen = min(minlen, currentLen);
                sum -= nums[i];
                currentLen--;
                i++;
            }
            j++;
        }
        // If there is no change in the minlen then the total sum < target, so return 0
        return minlen == nums.size()+1 ? 0 : minlen;
    }
};


// --------------------------------------------
// SAME SOLUTION WITHOUT CURRENTLENGTH VARIABLE
// --------------------------------------------

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        
        int i=0; // Start of sliding window (i..j-1)
        int j=0; // Next char of the sliding window, helps in adding elemens to the window
        int minlen = nums.size() + 1;
        int sum = 0;

        while(j!=nums.size()){
            sum += nums[j];

            while(sum >= target){
                minlen = min(minlen, j-i+1);
                sum -= nums[i];
                i++;
            }
            j++;
        }
        return minlen == nums.size()+1 ? 0 : minlen;
    }
};