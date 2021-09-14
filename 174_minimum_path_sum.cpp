
/*

Harshit Gupta | 11th August, 2021
---------------------------------

Problem Statement:
    Given a m x n grid filled with non-negative numbers, find a path from top left to bottom 
    right, which minimizes the sum of all numbers along its path.

    Note: You can only move either down or right at any point in time.

https://leetcode.com/problems/minimum-path-sum/

Example:
    1 3 1    1->3->1
    1 5 1 => 1  5  1 => 1+3+1+1+1 = 7
    4 2 1    4  2  1


------

Solution: 
    1. Taking a 2D DP array where dp[0][0] = grid[0][0]
    2. Consider 1st row, we can fill the dp[][] array with the dp[0][j-1]+grid[0][j]
        1 3 1    1 4 5
        1 5 1 => 
        4 2 1    
    3. Consider 1st Colmn, we can fill the dp[][] array with dp[i-1][0]+grid[i][j]
        1 3 1    1 4 5
        1 5 1 => 2
        4 2 1    6
    4. Fill the rest of the matrix by min(dp[i-1][j], dp[i][j-1]) + grid[i][j]
        since we want to move with minimum cost.
        1 3 1    1 4 5
        1 5 1 => 2 7 6
        4 2 1    6 8 7

    TC: O(n2)
    SC: O(n2)

Paradigm:
---
    NOTE: 
        1. Asked in OYO. BOLT.

    Similar Questions:
        1.

*/


class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));
        dp[0][0] = grid[0][0];
        
        for(int i=1; i<n; i++)
            dp[0][i] = dp[0][i-1]+grid[0][i];
        
        for(int i=1; i<m; i++)
            dp[i][0] = dp[i-1][0]+grid[i][0];
        
        for(int i=1; i<m; i++){
            for(int j=1; j<n; j++){
                dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j];
            }
        }
        return dp[m-1][n-1];
    }
};