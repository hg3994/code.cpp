
/*

Harshit Gupta | 4th July, 2021
---------------------------------

Given an m x n 2D binary grid grid which represents a map of '1's (land) and '0's (water), return the number of islands.
An island is surrounded by water and is formed by connecting adjacent lands horizontally or vertically. 
        You may assume all four edges of the grid are all surrounded by water.

https://leetcode.com/problems/number-of-islands/

Similar Questions: 
    1. Number of connected components in an undirected graph
        - https://leetcode.com/problems/number-of-connected-components-in-an-undirected-graph/
        - O(E)
    2. Is the graph a valid Tree?
        - https://leetcode.com/problems/graph-valid-tree/
        - A graph is a valid tree iff 
            - It does not have any cycles (nodes > edges)
            - It must be fully connected!
-----

Solution:   
    1. DFS:
        - Iterate over the graph
        - For the elements which are 1, increase the ans by 1 and call dfs
        - DFS would change the element to 0 (so we dont call them again - visited[][])
            and call dfs to the adjacent cells
        - When all the adjoining cells are marked 1, it will come back
        - Again search for an element 1 in the grid, this will not be connected 
            since if it were, it would have changed to 0. So, we increase ans by 1 again.

    TC: O(mn) where M is the number of rows and N is the number of columns
    SC: O(mn) in case that the grid map is filled with lands where DFS goes by M×N deep.

---

    2. Union Find:
        - Create the Union Find DS with parent and rank of size(m*n)
        - Fill parents by 0....mn and rank by 0s.
        - DSU DS will also have a variable count init to number of 1s. This is no. of islands.
        - Find operation will find the parent for an element
        - Union operation will try to union elements with different parent under the same parent by ranks.
        - In the main function, for all 1s, we will change them to 0s and try to union the adjacent 1s

    TC: O(mn) where M is the number of rows and N is the number of columns. Note that Union operation takes 
        essentially constant time[1] when UnionFind is implemented with both path compression and union by rank.
    SC: O(mn) as required by UnionFind data structure.

Paradigm: DFS, Union Find

---
  NOTE: This can also be solved with BFS

*/

// ------------
// DFS Solution
// ------------

class Solution {
public:
    
    void DFS(vector<vector<char>>& grid, int r, int c){        
        int m = grid.size();
        int n = grid[0].size();
        
        if(r<0 || r==m || c<0 || c==n|| grid[r][c]=='0')
            return;
        
        grid[r][c] = '0';
        DFS(grid, r-1, c);
        DFS(grid, r+1, c);
        DFS(grid, r, c+1);
        DFS(grid, r, c-1);
    }
    
    int numIslands(vector<vector<char>>& grid) {  
        if (grid.size() == 0)
            return 0;
        int m = grid.size();
        int n = grid[0].size();
        
        int ans = 0;
        for(int i=0; i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    ans++;
                    DFS(grid, i, j);
                }
            }
        }
        return ans;
    }
};



// --------------------
// UNION FIND SOLUTION
// --------------------

class DSU {
public: 
    // parent and rank will be vectors for m*n elements 
    // but they are 1D vectors so access grid[i][j] element like i*n+j
    // count will keep the count of number of connected components
    // After constructor the count = number of 1s in the graph
    // But union function will decrease the count when it will unify two 1s
    vector<int> parent, rank;
    int count; 
    
    DSU(vector<vector<char>> grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for(int i=0; i<m; i++) {
            for(int j=0; j<n; j++) {
                if(grid[i][j] == '1') {
                    count++;
                }
                parent.push_back(i*n + j);
                rank.push_back(0);
            }
        }
    }
    
    // path compression
    int find (int x){
        if(x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    // union by rank
    void Union(int x, int y) {
        int xp = find(x);
        int yp = find(y);
        if(xp != yp){
            if(rank[xp] > rank[yp])
                parent[yp] = xp;
            else if(rank[yp] > rank[xp])
                parent[xp] = yp;
            else {
                parent[yp] = xp;
                rank[xp]++;
            }
            count--;
        }
    }
    
    int getCount(){
        return count;
    }
    
};

class Solution {
public:
    
    int numIslands(vector<vector<char>>& grid) {  
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;  
        int m = grid.size();
        int n = grid[0].size();
        
        // Create a DSU data structure.
        DSU uf(grid);
        
        // Iterate and check for 1s.
        // If 1 is found, change it to 0 and try to union that 1 with the adjacent 1s (if any)
        // so that they come under just one component and have same parent
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j] == '1'){
                    grid[i][j] = '0';
                    if(i-1 >=0 && grid[i-1][j] == '1')
                        uf.Union(i*n + j, (i-1)*n + j);
                    if(i+1 <m  && grid[i+1][j] == '1')
                        uf.Union(i*n + j, (i+1)*n + j);
                    if(j-1 >=0 && grid[i][j-1] == '1')
                        uf.Union(i*n + j, i*n + j-1);
                    if(j+1 <n  && grid[i][j+1] == '1')
                        uf.Union(i*n + j, i*n + j+1);
                }
            }
        }
        return uf.getCount();
    }
};

// --------------------------------------------------------------------------
// SIMILAR QUESTION 1 - NUMBER OF CONNECTED COMPONENTS IN AN UNDIRECTED GRAPH
// --------------------------------------------------------------------------

class DSU {
    public:
    vector<int> parent, rank;
    int count;
    
    DSU (int n) {
        count = n;
        parent.resize(n);
        rank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void Union(int x, int y){
        int px = find(x);
        int py = find(y);
        
        if(px != py){
            if(rank[px] > rank[py])
                parent[py] = px;
            else if(rank[px] < rank[py])
                parent[px] = py;
            else {
                parent[py] = px;
                rank[px]++;
            }
            count--;
        }
    }
    
    int getCount(){
        return count;
    }
    
};

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& e) {
        DSU uf(n);
        for(auto E: e){
            uf.Union(E[0], E[1]);
        }
        return uf.getCount();
    }
};


// -------------------------------------------
// SIMILAR QUESTION 2 - IS GRAPH A VALID TREE? 
// -------------------------------------------

// For a graph to be a tree:
//      1. Graph must be fully connected.       => Use UF to find it.
//      2. Graph must not have any cycles.      => If edges >= n, then there would be cycles.

class DSU {
    public:
    vector<int> parent, rank;
    int count;
    
    DSU(int n){
        count = n;
        parent.resize(n);
        rank.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    
    int find(int x){
        if(x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }
    
    void Union(int x, int y){
        int px = find(x);
        int py = find(y);
        if(px != py){
            if(rank[px] > rank[py])
                parent[py] = px;
            else if(rank[px] < rank[py])
                parent[px] = py;
            else {
                parent[py] = px;
                rank[px]++;
            }
            count--;
        }
    }
    int getCount(){
        return count;
    }
    
};

class Solution {
public:
    bool validTree(int n, vector<vector<int>>& e) {
        if(e.size() >= n)
            return false;
        DSU uf(n);
        for(auto E: e){
            uf.Union(E[0], E[1]);
        }
        if(uf.getCount() == 1)
            return true;
        else
            return false;
    }
};
