

/*

Harshit Gupta | 10th June, 2021
---------------------------------

C++ program for "Shortest Distance between two islands"

In a given 2D binary array grid, there are two islands.  
(An island is a 4-directionally connected group of 1s not connected to any other 1s.)
Now, we may change 0s to 1s so as to connect the two islands together to form 1 island.
Return the smallest number of 0s that must be flipped.  (It is guaranteed that the answer is at least 1.)

Example 1:
    Input: grid = [[0,1],[1,0]]
    Output: 1

Example 2:
    Input: grid = [[0,1,0],[0,0,0],[0,0,1]]
    Output: 2

Example 3:
    Input: grid = [[1,1,1,1,1],[1,0,0,0,1],[1,0,1,0,1],[1,0,0,0,1],[1,1,1,1,1]]
    Output: 1

https://leetcode.com/problems/shortest-bridge/

------
Solution: 
    https://leetcode.com/problems/shortest-bridge/discuss/189293/C%2B%2B-BFS-Island-Expansion-%2B-UF-Bonus

    1. To distinguish between the two islands, we will make one island's all 1s to be 2s. We will use DFS to do that
    2. Then we start expanding island of 2s by painting connected empty area. Each round, we increase the color 
        (3, 4, and so on) so we can keep track of the newly painted area. This ends when we "bump" into the first island.
        - We use the expand function to expand around the island of 2s
        - Once we see a 0, we make it prev color+1 
        - Check if the current accessed cell was a 1, if yes, then the cl count till here - 2 would be the min dist between them.

Time Complexity: 
Space Complexity:

Paradigm: Flood Fill, DFS
---
  NOTE: 

*/



class Solution {
public:
    
    int dfs(vector<vector<int>>& grid, int i, int j){
        // If it is unreachable index OR is not a 1, then return 0 
        if (i<0 || j<0 || i==grid.size() || j==grid.size() || grid[i][j]!= 1) 
            return 0;
        // Reaching here means that it is one of the 1s of the 1st island, change it to 2
        grid[i][j] = 2;
        // Get it done for all the other adjoining 1s in the island
        return 1 + dfs(grid, i+1, j) + dfs (grid, i-1, j)+ dfs(grid, i, j+1) + dfs(grid, i, j-1);
    }
    
    bool expand(vector<vector<int>>& grid, int i, int j, int cl) {
        // If the grid with i,j is unreachable, return false    
        if (i<0 || j<0 || i==grid.size() || j==grid.size()) return false;
        // If the grid[i][j] is 0, it means that it has water here, we can mark it with color cl+1
        if (grid[i][j] == 0) 
            grid[i][j] = cl+1;
        // return TRUE if the current grid was 1 (meaning that we have reached the other island, time to return the last cl we encountered)
        return grid[i][j] == 1;
    }
    
    int shortestBridge(vector<vector<int>>& grid) {
        int found = 0;
        // Iterate over one set of island only and then convert all the 1s in it to 2s
        // It will return a positive integer and it will make both the for loops exit
        // fodun would actually contain the number of 1s in the first island
        for(int i=0; !found && i<grid.size(); i++)
            for(int j=0; !found && j<grid.size(); j++)
                found = dfs(grid, i, j);
        
        // Then we start expanding island of 2s by painting connected empty area. Each round, we increase the color 
        // (3, 4, and so on) so we can keep track of the newly painted area. This ends when we "bump" into the first island.
        // For each color 2 ... till we reach the other island
        //      if the element is of that color then we expand around it
        //      if the element reached after expanding is a 1, it will return true and the level/color we are in is the distance between the two islands
        for (int cl = 2; ; ++cl)
            for(int i=0; i<grid.size(); i++)
                for(int j=0; j<grid.size(); j++)
                    if (grid[i][j] == cl && (expand(grid, i - 1, j, cl) || expand(grid, i, j - 1, cl) || expand(grid, i + 1, j, cl) || expand(grid, i, j + 1, cl)))
                        return cl-2;
        
    }
};