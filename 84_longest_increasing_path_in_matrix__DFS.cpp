
/*

Harshit Gupta | 18th May, 2021
---------------------------------

C++ program for "Longest Increasing Path in a Matrix"
https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

Given an m x n integers matrix, return the length of the longest increasing path in matrix.
From each cell, you can either move in four directions: left, right, up, or down.

Input: matrix = 
    [   [9,9,4],
        [6,6,8],
        [2,1,1]
    ]
Output: 4
Explanation: The longest increasing path is [1, 2, 6, 9].

------

Solution: We will use DFS to traverse the matrix and whenever an element is smaller 
	than the element itself, then the longestIncreasingPath would be the 
	LIP(this element) = LIP(the smaller element)+1 
	- We also used a cache[][] which is initialized with all 1's.
	- If cache already contains a result, we dont compute it and get the result straightaway.


Time Complexity: O(mn)
Space Complexity: O(mn)

Paradigm: DFS, Memoization
---
  NOTE: 

*/


// matrix:
//     [9,9,4]
//     [6,6,8]
//     [2,1,1]

// cache: 
//     1 1 2 
//     2 2 1 
//     3 4 2 


class Solution {
    
    int dfs(vector<vector<int>>& matrix ,vector<vector<int>>& cache, int i, int j){
        int m = matrix.size();
        int n = matrix[0].size();
        
        if(cache[i][j]!=1){
            return cache[i][j];
        }
        
        vector<int> x = {1, -1, 0, 0};
        vector<int> y = {0, 0, 1, -1};
                 
        for(int k = 0; k <4; k++){
            if( i+x[k]>=0 && i+x[k]<m && j+y[k]>=0 && j+y[k]<n && 
                matrix[i+x[k]][j+y[k]] > matrix[i][j] ){
                cache[i][j] = max(cache[i][j], dfs(matrix, cache, i+x[k], j+y[k]) + 1);
            }
        }
        return cache[i][j];
    }
    
public:
    int longestIncreasingPath(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        vector<int> tmp(n, 1); vector<vector<int>> cache (m, tmp);
        int longestPath = 0;
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                longestPath = max(longestPath, dfs(matrix, cache, i, j));
            }
        }
        return longestPath;
    }
};