
/*

Harshit Gupta | 26th August, 2021
---------------------------------

Problem Statement:

1. You are climbing a staircase. It takes n steps to reach the top.
	Each time you can either climb 1 or 2 steps. In how many distinct ways can you climb to the top?
	- https://leetcode.com/problems/climbing-stairs/

2. You are given an integer array cost where cost[i] is the cost of ith step on a staircase. Once you 
	pay the cost, you can either climb one or two steps.
	You can either start from the step with index 0, or the step with index 1.
	Return the minimum cost to reach the top of the floor.
	- https://leetcode.com/problems/min-cost-climbing-stairs/

------

Solution: 

    TC: 
    SC:

Paradigm: DP
---
    NOTE: 

    Similar Questions:
        1.

*/


class Solution {
public:
    int climbStairs(int n) {
        if (n<=3)
            return n;
        vector<int> dp(n+1);
        dp[1] = 1;
        dp[2] = 2;
        for(int i=3;i<=n;i++){
            dp[i] = dp[i-1]+dp[i-2];
        }
        return dp[n];
    }
};


// ---------------------------
// 2. Min Cost Climbing Stairs
// ---------------------------

// Approach 3: DP
class Solution {
public:
    int minCostClimbingStairs(vector<int>& cost) {
        int n = cost.size();
        vector<int> dp (n+1);
        dp[0]= cost[0];
        dp[1]= cost[1];
        for(int i=2; i<n; i++)
            dp[i] = min(dp[i-1], dp[i-2])+cost[i];
        return min(dp[n-1], dp[n-2]);
    }
};


// Approach 1: Recursive Solution: Gives TLE 
class Solution {
public:
    
    int helper(vector<int>& cost, int pos, int currentCost){
        if(pos >= cost.size())
            return currentCost;
        int jump1 = helper(cost, pos+1, currentCost+cost[pos]);
        int jump2 = helper(cost, pos+2, currentCost+cost[pos]);
        return min(jump1, jump2);
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        if(cost.size() == 2)
            return min(cost[0], cost[1]);
        return min(helper(cost, 0, 0), helper(cost, 1, 0));
    }
};


// Approach 2: Recursion with Memoization (TLE) since a huge dp[][] array is there.
class Solution {
public:
    int helper(vector<int>& cost, vector<vector<int>>& dp, int pos, int currentCost){
        if(pos >= cost.size())
            return currentCost;
        if(dp[pos][currentCost] != -1)
            return dp[pos][currentCost];
        
        dp[pos+1][currentCost+cost[pos]] = helper(cost, dp, pos+1, currentCost+cost[pos]);
        dp[pos+2][currentCost+cost[pos]] = helper(cost, dp, pos+2, currentCost+cost[pos]);
        return min(dp[pos+1][currentCost+cost[pos]], dp[pos+2][currentCost+cost[pos]]);
    }
    
    int minCostClimbingStairs(vector<int>& cost) {
        if(cost.size() == 2)
            return min(cost[0], cost[1]);
        vector<vector<int>> dp (cost.size()+2, vector<int>(1000000, -1));
        return min(helper(cost, dp, 0, 0), helper(cost, dp, 1, 0));
    }
};
