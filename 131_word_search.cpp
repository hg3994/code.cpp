
/*

Harshit Gupta | 3rd July, 2021
---------------------------------

C++ program for "Word Search Problem"

Given an m x n grid of characters board and a string word, return true if word exists in the grid.

The word can be constructed from letters of sequentially adjacent cells, where adjacent cells 
    are horizontally or vertically neighboring. The same letter cell may not be used more than once.


Example 1:
    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCCED"
    Output: true

Example 2:
    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "SEE"
    Output: true

Example 3:
    Input: board = [["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]], word = "ABCB"
    Output: false

https://leetcode.com/problems/word-search/
------

Solution: Backtracking.
    1. Iterate over all the elements checking if this is the starting of the word
    2. If we find the start, we iterate on the rest of the board looking for more letters in the word
    3. If we are able to reach the end, return true
        If we cant reach the end, then we backtrack.
    4. We use a visited array to keep check of where we have already travelled

TC: Time Complexity: O(N * 3^L)

    where N is the number of cells in the board and L is the length of the word to be matched.
    For the backtracking function, initially we could have at most 4 directions to explore, 
    but further the choices are reduced into 3 (since we won't go back to where we come from). 
    As a result, the execution trace after the first step could be visualized as a 3-ary tree, 
    each of the branches represent a potential exploration in the corresponding direction. 
    Therefore, in the worst case, the total number of invocation would be the number of nodes 
    in a full 3-nary tree, which is about 3^L 

    We iterate through the board for backtracking, i.e. there could be N times invocation for the backtracking function in the worst case.

    As a result, overall the time complexity of the algorithm would be O(N*3^L)

SC: O(L) for recursion stack of the backtracking function.

Paradigm: Backtracking
---
  NOTE: 

*/

class Solution {
public:
    
    bool dfs(vector<vector<char>>&board, vector<vector<bool>>&visited, string word, int i, int j, int word_i ) {
        int m = board.size();
        int n = board[0].size();
        if (i<0 || i>=m || j<0 || j>=n || visited[i][j] == true || board[i][j] != word[word_i])
            return false;
        
        // cout<<"dfs called for: i: "<<i<<" j: "<<j<<" word_i: "<<word_i<<" board[i][j]: "<<board[i][j]<<" word[word_i]: "<<word[word_i]<<endl;
        
        visited[i][j] = true;
        
        // if this is the end, return true
        if(word_i == word.size()-1) {
            return true;
        }
        // go deeper ..
        else if (dfs(board, visited, word, i+1, j, word_i+1) || dfs(board, visited, word, i-1, j, word_i+1) || dfs(board, visited, word, i, j+1, word_i+1) || dfs(board, visited, word, i, j-1, word_i+1)){
            return true;
        }
        // It comes here when it can not find a solution after going in all directions after choosing baord[i][j], 
        // so we backtrack and mark the field as unvisited so that it may be used further in the string.
        visited[i][j] = false;
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                vector<bool> tmp(n, false);
                vector<vector<bool>> visited (m, tmp);
                if(dfs(board, visited, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
};