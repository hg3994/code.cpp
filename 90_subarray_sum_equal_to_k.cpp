/*

Harshit Gupta | 24th May, 2021
---------------------------------

C++ program for "Count number of contiguous subarrays with sum=k"
https://leetcode.com/problems/subarray-sum-equals-k/

Example 1:
    Input: nums = [1,1,1], k = 2
    Output: 2

Example 2:
    Input: nums = [1,2,3], k = 3
    Output: 2

------

Solution: Explained below

Time Complexity: O(n)
Space Complexity:
---
  NOTE: 
  Similar Problem: https://leetcode.com/problems/binary-subarrays-with-sum

*/

class Solution {
public:
    
    // We iterate over the array and keep calculating the cumulative sum
    // We keep a map which tells us the number of times we have encountered a particular sum
    // We update the map with the frequency of the 'sum' variable (+1)
    // We check for the frequncy of "sum-k" for each particular sum, and add the freq of "sum-k" to ans.
    
    int subarraySum(vector<int>& nums, int k) {

        int ans=0;
        int sum=0;
        unordered_map<int, int> m = {{0,1}}; // Sum 0 can be made 1 number of times.
        
        
        for(int i=0;i<nums.size(); i++){
            // Keep updating 'sum' variable which contains the cumulative sum
            sum += nums[i];
            
            // If (sum-k) is present in the map, then it means that current_sum-k has already been found
            // m[sum-k] times so add that to the answer
            // (Difference between 'sum-k' and sum is 'k')
            if(m.count(sum-k)){
                ans += m[sum-k];
            }
            
            // Update the map with the frequency of "sum" and increase it by 1.
            // This whole code below can be written like: m[sum]++ only (it will automatically handle everything)
            if(m.count(sum)){
                m[sum]++;
            }
            else{
                m[sum] = 1;
            }
        }
        
        return ans;
    }
};