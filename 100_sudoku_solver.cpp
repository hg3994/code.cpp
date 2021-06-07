
/*

Harshit Gupta | 4th June, 2021
-------------------------------

C++ program for "Sudoku Solver"
https://leetcode.com/problems/sudoku-solver/
https://leetcode.com/problems/valid-sudoku/
------

Solution: We use backtracking to solve the sudoku

Time Complexity: O((9!)^9)

    Time complexity is constant here since the board size is fixed and there is no N-parameter 
    to measure. Though let's discuss the number of operations needed.

    Let's consider one row, i.e. not more than 9 cells to fill. 
    There are not more than 9 possibilities for the first number to put, 
    not more than 9×8 for the second one, not more than 9×8×7 for the third one etc. 
    In total that results in not more than 9! possibilities for a just one row, that means 
    not more than (9!)^9 operations in total.

Space Complexity: O(1)

Paradigm: BackTracking

---
  NOTE: 

*/

class Solution {
     
public:
        
    // To check if it is valid..
    //  - Check for the entire row if it already has the same character twice? Return false if it does
    //  - Check for the entire col if it already has the same character twice? Return false if it does
    //  - Check for the 3x3 box to see it already has it? Return false if it does
    
    // NOTE: Given a row, col, if we need to find the starting i,j of that 3x3 box, then we do row/3*3 and col/3*3
    bool isValidPlacement(vector<vector<char>>& board, int row, int col, char c){
        for(int i=0;i<9;i++)
            if(board[row][i] == c) return false;
        for(int i=0;i<9;i++)
            if(board[i][col] == c) return false;
        
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                if(board[row/3*3 + i][col/3*3 + j] == c)
                    return false;
        return true;
    }
    
    
    bool solve(vector<vector<char>>& board){
        // Looking in the whole board, trying to fill in the '.'
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                // If a '.' is found, we will try to fill it in
                if(board[i][j] == '.'){            
                    // Iterate over all the integers from 1 to 9 to get it filled 
                    // (trick used since it's actually a char ('1'+k to convert it to get the char)
                    for(int k=0;k<9;k++){
                        // If this is a valid placement 
                        if(isValidPlacement(board, i, j, k+'1')){
                            // Place it and then try to solve further ...
                            board[i][j] = '1'+k;
                            if(solve(board))
                                // Try to solve futher, once everything is filled, this func will 
                                // return true (see at end) and this is when we will realize we have solved it!!
                                return true;
                            else
                                // If it is not solvable then we know that the choice we made(k) was 
                                // wrong, so we place a '.' back and then try to place some other 'k' here
                                board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        solve(board);
    }

};