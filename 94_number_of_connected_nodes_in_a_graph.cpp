/*

Harshit Gupta | 31st May, 2021
---------------------------------

C++ program for "Number of Connected Nodes in a graph"

There are n cities. Some of them are connected, while some are not. If city a is connected directly with city b, 
and city b is connected directly with city c, then city a is connected indirectly with city c.
A province is a group of directly or indirectly connected cities and no other cities outside of the group.
You are given an n x n matrix isConnected where isConnected[i][j] = 1 if the ith city and the jth city are 
    directly connected, and isConnected[i][j] = 0 otherwise.

Return the total number of provinces.

https://leetcode.com/problems/number-of-provinces/
------

Solution: Use DFS to traverse for the matrix and use visited[] to avoid being in infinite loop.

Time Complexity: O(n2)
Space Complexity: O(n)

Paradigm: DFS
---
  NOTE: This can also be done with BFS & Union Find

*/


class Solution {
public:
    
    // i is the row which is sent from main function while the for loop here is for j which is the column.
    void dfs(vector<vector<int>>& grid, vector<int>& visited, int i){
        for(int j=0; j< grid.size(); j++){
            if(i!=j && grid[i][j] == 1 && visited[j] == 0){
                visited[j] = 1;
                dfs(grid, visited, j);
            }
        }
    }
    
    int findCircleNum(vector<vector<int>>& grid) {
        int n = grid.size();
        int count = 0;
        // visited init to 0
        vector<int> visited(n,0);
        
        for(int i=0; i<n; i++){
            if(visited[i] == 0) {
                dfs(grid, visited, i);
                // once a dfs call returns here covering all the connected nodes of i, increment count
                // we also kept marking visited before so that we dont traverse them again.
                count++;
            }
        }
        return count;
    }
};