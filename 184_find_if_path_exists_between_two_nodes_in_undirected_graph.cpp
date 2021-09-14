
/*

Harshit Gupta | 17th August, 2021
---------------------------------

Problem Statement:  Find if Path Exists in Graph

	There is a bi-directional graph with n vertices, where each vertex is labeled from 0 to n - 1 (inclusive). The edges in 
	the graph are represented as a 2D integer array edges, where each edges[i] = [ui, vi] denotes a bi-directional edge between 
	vertex ui and vertex vi. Every vertex pair is connected by at most one edge, and no vertex has an edge to itself.

	You want to determine if there is a valid path that exists from vertex start to vertex end.

	Given edges and the integers n, start, and end, return true if there is a valid path from start to end, or false otherwise.

https://leetcode.com/problems/find-if-path-exists-in-graph/
------

Solution: 
	1. BFS: Simple BFS search in a graph starting fromt the start node looking for the end node. Keep pushing the nbrs
	    TC: O(n) Each node is traversed at most once.
	    SC: O(n) for queue


	2. DFS: Recursively keep visiting the nodes and checking if this is the end
	    TC: O(n) Each node is traversed at most once.
	    SC: O(n) for recursion stack


	3. Disjoint Set Union: Create a DSU and then check if start and end have the same leaders?
		TC: O(n*α(n)) ≈ O(n), the time complexity of each find call after union-by-rank and path 
			compression comes out to be O(α(n)), where α(n) is the inverse Ackermann function. It doesn't exceed 4 
			for any n < 10600 and hence is practically constant. We make O(n) calls in total.
		SC: O(n) for UF Data structure


Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/



// Approach 1: BFS based approach
// ==============================

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        vector<vector<int>> graph(n);
        // Build the graph
        for(int i=0; i<edges.size(); i++) {
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }
        
        // BFS
        queue<int> q;
        vector<int> visited(n, 0);
        q.push(start);
        visited[start] = 1;
        while(!q.empty()){
            int top = q.front();
            q.pop();
            if(top == end)
                return true;

            for(int i=0; i<graph[top].size(); i++){
                if(visited[graph[top][i]] == 0){
                    q.push(graph[top][i]);
                    visited[graph[top][i]] = 1;
                }
            }
        }
        return false;
    }
};


// Approach 2: DFS BASED SOLUTION
// ===============================
class Solution {
public:
    
    bool dfs(vector<vector<int>>& graph, vector<int>& visited, int current, int end) {
        if(current == end)
            return true;
        if(visited[current])
            return false;
        
        visited[current] = 1;
        
        for(int i=0; i<graph[current].size(); i++){
            if(dfs(graph, visited, graph[current][i], end))
                return true;
        }
        
        return false;
    }
    
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        vector<vector<int>> graph(n);
        for(int i=0; i<edges.size(); i++) {
            graph[edges[i][0]].push_back(edges[i][1]);
            graph[edges[i][1]].push_back(edges[i][0]);
        }
        vector<int> visited(n, 0);
        return dfs(graph, visited, start, end);
    }
};


// Approach 3: UNION FIND BASED SOLUTION
// =====================================

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n){
        parent.resize(n);
        rank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(x !=parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    bool Union(int x, int y){
        int xp = find(x);
        int yp = find(y);
        
        if(xp == yp)
            return true;
        else {
            if(rank[xp] > rank[yp])
                parent[yp] = xp;
            else if (rank[xp] < rank[yp])
                parent[xp] = yp;
            else {
                parent[yp] = xp;
                rank[xp]++;
            }
            return false;
        }
    }
    
};

class Solution {
public:
    bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
        DSU uf(n);
        for(int i=0; i<edges.size(); i++) {
            uf.Union(edges[i][0], edges[i][1]);
        }
        return uf.Union(start, end);
    }
};

