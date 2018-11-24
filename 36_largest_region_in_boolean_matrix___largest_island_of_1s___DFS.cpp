/* 
Harshit Gupta | 11th November, 2018

https://ide.geeksforgeeks.org/hkBrrpegWh
https://www.geeksforgeeks.org/find-length-largest-region-boolean-matrix/

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

Paradigm: DFS, Traversal

Time Complexity: O(ROWxCOL)

*/

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
void DFS(int M[][COL], int row, int col, 
         bool visited[][COL], int &count) 
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
        if (isSafe(M, row + rowNbr[k], col + colNbr[k], 
                                              visited)) 
        { 
            // increment region length by one 
            count++; 
            DFS(M, row + rowNbr[k], col + colNbr[k], 
                                    visited, count); 
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
