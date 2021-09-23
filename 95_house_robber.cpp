
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
Space Complexity: O(n)

Paradigm: DP

Similar Questions:
    1. https://leetcode.com/problems/house-robber-ii/
        - Similar question + houses are arranged in a circle. 1st house is the neighbour of the last one.
        - Problem becomes to rob either (House[1] to House[n-1]) or (House[2] to House[n])
        - It reduces to two house-robber problems and max of them would be the ans.

    2. https://leetcode.com/problems/house-robber-iii/
        - Besides the root, each house has one and only one parent house. After a tour, the smart thief 
            realized that all houses in this place form a binary tree. It will automatically contact the 
            police if two directly-linked houses were broken into on the same night.
            Given the root of the binary tree, return the maximum amount of money the thief can rob without alerting the police.
        - Check link for Graphical Examples
        - VERY interesting problem
        

---
  NOTE: 

*/


class Solution {
public:
    int rob(vector<int>& nums) {
        if(nums.size() == 0)
            return 0;
        else if(nums.size() == 1)
            return nums[0];
        else if(nums.size() == 2)
            return max(nums[0],nums[1]);
        
        int n = nums.size();
        vector<int> dp(n,0);
        
        dp[0] = nums[0];
        dp[1] = max(nums[0], nums[1]);
        
        for(int i=2;i<n;i++)
            dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
          
        return dp[n-1];
    }
};


// -----------------------------------------
// SIMILAR PROBLEM 1 - CIRCULAR HOUSE ROBBER
// -----------------------------------------
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
    vector<int> dp(n,0);
    
    // Robbing house 0 to n-2
    dp[0] = nums[0];
    dp[1] = max(nums[0], nums[1]);
    for(int i=2;i<n-1;i++){
      dp[i] = max(dp[i-1], dp[i-2]+nums[i]);
    }
    int ans1 = dp[n-2];
    
    // Robbing house 1 to n-1 (loop is same just accessing nums[i+1] instead of nums[i])
    dp.clear();
    dp[0] = nums[1];
    dp[1] = max(nums[1], nums[2]);
    for(int i=2;i<n-1;i++){
      dp[i] = max(dp[i-1], dp[i-2]+nums[i+1]);
    }
    int ans2 = dp[n-2];
    
    return max(ans1, ans2);
  }
};


// --------------------------------------------------
// SIMILAR PROBLEM 2  - HOUSE ROBBER IN A BINARY TREE
// --------------------------------------------------

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

// Time complexity: O(N) since we run the helper function for all nodes once, and saved the results to prevent the second calculation.
// Space complexity: O(N) since we need two maps with the size of O(N) to store the results, and O(N) space for stacks to start recursion.
class Solution {
public:
    // memoization maps
    unordered_map<TreeNode*, int> robResult; // if parent was robbed
    unordered_map<TreeNode*, int> notRobResult; // if parent was not robbed
    
    int helper(TreeNode* node, bool parentRobbed){
        if(node == NULL)
            return 0;
        
        if(parentRobbed){
            if(robResult.count(node))
                return robResult[node];
            int result = helper(node->left, false) + helper(node->right, false);
            robResult[node] = result;
            return result;
        }
        else {
            if(notRobResult.count(node))
                return notRobResult[node];
            int rob = node->val + helper(node->left, true) + helper(node->right, true);
            int notRob = helper(node->left, false) + helper(node->right, false);
            int result = max(rob, notRob);
            notRobResult[node] = result;
            return result;
        }
    }
    
    int rob(TreeNode* root) {
        return helper(root, false);
    }
};