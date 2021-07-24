
/*

Harshit Gupta | 5th July, 2021
---------------------------------

You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.
Return the size of the largest island in grid after applying this operation.
An island is a 4-directionally connected group of 1s.

https://leetcode.com/problems/making-a-large-island/
------

Solution: 
    1. We want to find the largest area of an island by changing just one element.
    2. We would use Disjoint Set Union to group all the 1s and create a few sets. One of them would be largest.
         - We iterate over the matrix and if find a 1, we will union it with other adjacent 1s. 
         - We will mark the 1 as -1 once it has been traversed so that it doesnt get counted more than once.
    3. Now once the Disjoint set data structure is created, we will search for Zeros again in the whole matrix
    4. Once we see any Zero, we will look for 1s in 4 adjacent cells and count the sizes as if by 
         changing this 0 to 1, what will happen
         - If multiple 1 groups belong to the same parent, we count it only once (we use parentPresence vector for this)
    5. By checking for every 0 -> 1 conversion we will get a size, and out of all sizes we select the maxSize!

TC: O(n2)
SC: O(n2)

Paradigm: Union Find

---
  NOTE: 

*/



class DSU {
public:
    // size will help us figure out the size of the components.
    // Initially, all the fields will have a size 1, we will add them up in union fn.
    vector<int> parent, rank, size;
    
    DSU(vector<vector<int>> grid){
        int m = grid.size();
        int n = grid[0].size();
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                parent.push_back(i*n + j);
                rank.push_back(0);
                size.push_back(1);
            }
        }
    }
    
    int find (int x){
        if(x != parent[x])
            parent[x] = find(parent[x]);
        return parent[x];
    }

    // After merging x and y, it returns the size of the merged set.
    int Union(int x, int y){
        int px = find(x);
        int py = find(y);
        if(px != py){
            // When rank of px is greater, we update the parent of py to be px & update add size of py to sizeof px
            if(rank[px] > rank[py]){
                parent[py] = px;
                size[px] += size[py];
                return size[px];
            }
            else if(rank[py] > rank[px]){
                parent[px] = py;
                size[py] += size[px];
                return size[py];
            }
            else {
                parent[py] = px;
                rank[px]++;
                size[px] += size[py];
                return size[px];
            }
        }
        else{
            // doesnt matter since both x and y belong to the same parent
            return size[px]; // return anything!
        }
    }
    
    int getSize(int x){
        return size[find(x)];
    }
    
};

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;  
        int m = grid.size();
        int n = grid[0].size();
        
        int res = 0;
        DSU uf(grid);
        
        // Creating the DSU by unionifying the elements
        // Finally we will have a bunch of sets of different sizes each having a parent/leader.
        // We also change 1 to -1 of those which are traversed already.
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j] == 1){
                    grid[i][j] = -1;
                    if(i-1 >=0 && grid[i-1][j] == 1)
                        uf.Union(i*n + j, (i-1)*n + j);
                    if(i+1 < m && grid[i+1][j] == 1)
                        uf.Union(i*n + j, (i+1)*n + j);
                    if(j-1 >=0 && grid[i][j-1] == 1)
                        uf.Union(i*n + j, i*n + j-1);
                    if(j+1 < n && grid[i][j+1] == 1)
                        uf.Union(i*n + j, i*n + j+1);
                }
            }
        }
        
        // We iterate searching for 0s and the adjacent -1s. If we find an adjacent -1, we will
        // Check if it belongs to a known parent already (from other adjacent -1s?). If yes, then ignore.
        // If No, then it means this -1 belongs to some other set and if we change this 0 to 1, then 
        // it will join 2 or more sets together.
        // 1 1 0
        // 1 0 1
        // 0 1 1
        // A central 0 if changed would join 2 groups of 3 1s each and so the final size would be 7
        int maxSize = -1;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j] == 0){
                    vector<int> parentPresence;
                    int currSize = 1;
                    if(i-1 >=0 && grid[i-1][j] == -1){
                        int newParent = uf.find((i-1)*n + j);
                        if(find(begin(parentPresence), end(parentPresence), newParent) == end(parentPresence)){
                            currSize += uf.getSize((i-1)*n + j);
                            parentPresence.push_back(newParent);
                        }
                    }
                    if (i+1 <m && grid[i+1][j] == -1){
                        int newParent = uf.find((i+1)*n + j);
                        if(find(begin(parentPresence), end(parentPresence), newParent) == end(parentPresence)){
                            currSize += uf.getSize((i+1)*n + j);
                            parentPresence.push_back(newParent);
                        }
                    }
                    if (j-1 >=0 && grid[i][j-1] == -1){
                        int newParent = uf.find(i*n + j-1);
                        if(find(begin(parentPresence), end(parentPresence), newParent) == end(parentPresence)){
                            currSize += uf.getSize(i*n + j-1);
                            parentPresence.push_back(newParent);
                        }
                    }
                    if (j+1 <n && grid[i][j+1] == -1){
                        int newParent = uf.find(i*n + j+1);
                        if(find(begin(parentPresence), end(parentPresence), newParent) == end(parentPresence)){
                            currSize += uf.getSize(i*n + j+1);
                            parentPresence.push_back(newParent);
                        }
                    }
                    maxSize = max(maxSize, currSize);
                }
            }
        }
        
        return maxSize == -1 ? m*n : maxSize;
    }
};