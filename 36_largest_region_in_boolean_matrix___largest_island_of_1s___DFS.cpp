/* 
Harshit Gupta | 11th November, 2018

https://ide.geeksforgeeks.org/hkBrrpegWh
https://www.geeksforgeeks.org/find-length-largest-region-boolean-matrix/
https://leetcode.com/problems/max-area-of-island/

C++ program for area of the largest island. An island would be an area 
    where the whole area is made up with 1s.
    Consider a matrix with rows and columns, where each cell contains either a ‘0’ or a ‘1’ 
    and any cell containing a 1 is called a filled cell. 
    Two cells are said to be connected if they are adjacent to each other 
    horizontally, vertically, or diagonally. If one or more filled cells are
    also connected, they form a region. find the length of the largest region/island.

Solution: We will check for each of the elements of the matrix and see if it is 1.
    If it is 1, then iterate over its neighbours and they will again iterate 
        over their neighbours till they can reach 1s. Method Name: DFS()
    We will also maintain a visited[][] array with help of which we will know what we have
        already traversed and thus ignore it we see it for the second time.

Paradigm: DFS, Traversal, Union Find

Time Complexity: O(ROWxCOL)

*/



// LEETCODE SOLTUION

// UNION FIND SOLUTION
// -------------------
// We start with a size[] array as well apart from parent and rank. This will help us figure out the max size os island.
// Updating size in the Union function will do trick, because we are updating the parent at all point of time as well.
// So, when we compare two nums, we are actually comparing the parents and then updating the size! Think about it.
// [1,1]
// [1,1]
// parent: [0,1,2,3]
// size:   [1,1,1,1]
// We are at (0,0)=>0 , we mark grid[0][0] = 0 now
//      union(0,1) called and it will update parent[1] = 0 and size[0] = 2
//      union(0,2) called and it will update parent[2] = 0 and size[0] = 3

// [0,1]
// [1,1]
// parent: [0,0,0,3]
// size:   [3,1,1,1]
// We are at (0,1)=>1 , we mark grid[0][1] = 0 now
//      union(1,3) called and it will update parent[3] = 0 (since parent[1] = 0) and size[0] = 4

// [0,0]
// [1,1]
// parent: [0,0,0,0]
// size:   [4,1,1,1]
// We are at (1,0)=>2 , we mark grid[1][0] = 0 now
//      union(2,3) called and both belong to the same parent 0 so just return the size.

// [0,0]
// [0,1]
// parent: [0,0,0,0]
// size:   [4,1,1,1]
// We are at (1,1)=>3 , we mark grid[1][1] = 0 now

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
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        if (grid.size() == 0 || grid[0].size() == 0)
            return 0;  
        int m = grid.size();
        int n = grid[0].size();
        
        int res = 0;
        DSU uf(grid);
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(grid[i][j] == 1){
                    grid[i][j] = 0;
                    // Compare the sizes of this field and the adjacent field
                    res = max(res,uf.getSize(i*n + j));
                    if(i-1 >=0 && grid[i-1][j] == 1)
                        res = max(res, uf.Union(i*n + j, (i-1)*n + j));
                    if(i+1 < m && grid[i+1][j] == 1)
                        res = max(res, uf.Union(i*n + j, (i+1)*n + j));
                    if(j-1 >=0 && grid[i][j-1] == 1)
                        res = max(res, uf.Union(i*n + j, i*n + j-1));
                    if(j+1 < n && grid[i][j+1] == 1)
                        res = max(res, uf.Union(i*n + j, i*n + j+1));
                }
            }
        }
        return res;
    }
};


// ------------------------
// DFS SOLUTION ON LEETCODE 
// ------------------------

class Solution {
    
    int isSafe(vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j){
        return (i<0 || i==grid.size() || j<0 || j==grid[0].size() || visited[i][j] == 1 || grid[i][j] == 0);
    }
    
    int dfs (vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j) {
        if(isSafe(grid,visited,i,j))
            return 0;
        visited[i][j] = 1;
        return 1+dfs(grid, visited, i+1, j)+dfs(grid, visited, i-1, j)+dfs(grid, visited, i, j+1)+dfs(grid, visited, i, j-1);
    }
    
public:
    int maxAreaOfIsland(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        vector<int> tmp(n, 0);
        vector<vector<int>> visited (m, tmp);
        int maxArea = 0;
        int area;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if (grid[i][j] == 1 &&  visited[i][j]==0){
                    area = dfs (grid, visited, i, j);
                    maxArea = max(area, maxArea);
                }
            }
        }
        return maxArea;
    }
};







// ------------
// MY GFG CODE
// ------------

#include<bits/stdc++.h> 
using namespace std; 
#define ROW 4 
#define COL 5 
  
// A function to check if a given cell (row, col) 
// can be included in DFS 
int isSafe(int M[][COL], int row, int col, 
           bool visited[][COL]) 
{ 
    // row number is in range, column number is in 
    // range and value is 1 and not yet visited 
    return (row >= 0) && (row < ROW) && 
           (col >= 0) && (col < COL) && 
           (M[row][col] && !visited[row][col]); 
} 
  
// A utility function to do DFS for a 2D boolean 
// matrix. It only considers the 8 neighbours as 
// adjacent vertices 
void DFS(int M[][COL], int row, int col, bool visited[][COL], int &count) 
{ 
    // These arrays are used to get row and column 
    // numbers of 8 neighbours of a given cell 
    static int rowNbr[] = {-1, -1, -1, 0, 0, 1, 1, 1}; 
    static int colNbr[] = {-1, 0, 1, -1, 1, -1, 0, 1}; 
  
    // Mark this cell as visited 
    visited[row][col] = true; 
  
    // Recur for all connected neighbours 
    for (int k = 0; k < 8; ++k) 
    { 
        if (isSafe(M, row + rowNbr[k], col + colNbr[k], visited)) 
        { 
            // increment region length by one 
            count++; 
            DFS(M, row + rowNbr[k], col + colNbr[k], visited, count); 
        } 
    } 
} 
  
// The main function that returns largest  length region 
// of a given boolean 2D matrix 
int  largestRegion(int M[][COL]) 
{ 
    // Make a bool array to mark visited cells. 
    // Initially all cells are unvisited 
    bool visited[ROW][COL]; 
    memset(visited, 0, sizeof(visited)); 
  
    // Initialize result as 0 and travesle through the 
    // all cells of given matrix 
    int result  = INT_MIN; 
    for (int i = 0; i < ROW; ++i) 
    { 
        for (int j = 0; j < COL; ++j) 
        { 
            // If a cell with value 1 is not visited yet, then new region found 
            if (M[i][j] && !visited[i][j]) 
            { 
                // 'count' variable is initialized to 1 since we have an island now with 1.
                // It is used to keep track of the area of this particular island.
                int count = 1 ; 
                
                // Call DFS to get the length of the island.
                // Update visited and count variables as well.
                DFS(M, i, j, visited , count); 
  
                // Check if the are of this island was greater than the already found area.
                // If yes, then update the variable result.
                result = max(result , count); 
            } 
         } 
    } 
    return result ; 
} 
  
// Driver program to test above function 
int main() 
{ 
    int M[][COL] = { {0, 0, 1, 1, 0}, 
                     {1, 0, 1, 1, 0}, 
                     {0, 1, 0, 0, 0}, 
                     {0, 0, 0, 0, 1}}; 
  
    cout << largestRegion(M); 
  
    return 0; 
} 
