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
  NOTE: 
    1. This can also be done with Union Find
    2. This DFS is a bit different from the regulat DFS method since in this graph, there is data 1->2 and 2->1 are both marked 1
        if they are connected.

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
        // we need only 1D visited since finally there are only N nodes, the matrix is just N*N
        // If we visit a node once, it's fine, no need to come back to this node again.
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


// Using BFS
class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        vector<int> visited(n, 0);
        queue<int> q;
        int ans=0;
        for(int i=0; i<n; i++){
            if(visited[i] == 0){
                q.push(i);
                while(!q.empty()) {
                    int top = q.front();
                    q.pop();
                    visited[top] = 1;
                    for(int j=0; j<n; j++){
                        if(isConnected[top][j]==1 && visited[j]==0)
                            q.push(j);
                    }
                }
                ans++;
            }
        }
        return ans;
    }
};