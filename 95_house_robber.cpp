
/*

Harshit Gupta | 1st June, 2021
---------------------------------

C++ program for "House Robbers"

You are a professional robber planning to rob houses along a street. Each house has a certain 
amount of money stashed, the only constraint stopping you from robbing each of them is that 
adjacent houses have security systems connected and it will automatically contact the police 
if two adjacent houses were broken into on the same night.

Given an integer array nums representing the amount of money of each house, 
return the maximum amount of money you can rob tonight without alerting the police.

Example 1:
	Input: nums = [1,2,3,1]
	Output: 4
	Explanation: Rob house 1 (money = 1) and then rob house 3 (money = 3).
	Total amount you can rob = 1 + 3 = 4.

Example 2:
	Input: nums = [2,7,9,3,1]
	Output: 12
	Explanation: Rob house 1 (money = 2), rob house 3 (money = 9) and rob house 5 (money = 1).
	Total amount you can rob = 2 + 9 + 1 = 12.


https://leetcode.com/problems/house-robber/
------

Solution: 
	- We have an array dp[i] which will contain the maximum amount of money we can make till house[i]
	- dp[0] = house[0]
	- dp[1] = max(house[0], house[1])
	- Think of it this way... For every house[i], we always have two choices:
		- Do not rob this house. This way the maximum money we will have is dp[i] = dp[i-1]
		- Rob this house with house[i] and choose the max we had from dp[i-2]
	- We always keep choosing the maximum money we get from these two choices and continue till the end

Time Complexity: O(n)
Space Complexity:

Paradigm: DP
---
  NOTE: 

*/



class Solution {
public:
  int rob(vector<int>& nums) {
    
    if(nums.size() == 0)
      return 0;
    if(nums.size() == 1)
      return nums[0];
    if(nums.size() == 2)
      return max(nums[0],nums[1]);
    
    int n = nums.size();
    vector<int> dp(n+1,0);
    
    dp[0] = nums[0];
    
    dp[1] = max(nums[0], nums[1]);
    
    for(int i=2;i<n;i++){
      dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
    }
    int ans1 = dp[n-2];
    cout<<ans1<<endl;
    return ans1;
  }
};