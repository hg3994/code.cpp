/* 
Harshit Gupta | 28th October, 2018

https://ide.geeksforgeeks.org/93EfY5xl77
https://www.geeksforgeeks.org/n-queen-problem-backtracking-3/

C++ program for the N-Queen Problem. The N Queen is the problem of placing N chess queens 
    on an N×N chessboard so that no two queens attack each other. 

Solution: We will start with an empty matrix and then start placing queens one-by-one.
    For a specific column, we will try to place the queen on every row.
    If placing a queen on a row,col leads to a solution 
        and we were able to place N queens on the board, well and good
    Otherwise, we will backtrack and mark it as 0 again.

    1) Start in the leftmost column
    2) If all queens are placed
        return true
    3) Try all rows in the current column.  Do following for every tried row.
        a) If the queen can be placed safely in this row then mark this [row, 
            column] as part of the solution and recursively check if placing queen here leads to a solution.
        b) If placing the queen in [row, column] leads to a solution then return 
            true.
        c) If placing queen doesn't lead to a solution then umark this [row, 
            column] (Backtrack) and go to step (a) to try other rows.
    3) If all rows have been tried and nothing worked, return false to trigger 
        backtracking.



Similar Problems: 
    1. https://leetcode.com/problems/n-queens/
        - For a given N, try to print all the valid board positions.

    2. https://leetcode.com/problems/n-queens-ii/
        - For a given N, try to print the number of valid board positions. (See leetcode link for solution)

Paradigm: Backtracking, Recursion.

*/

#include <bits/stdc++.h>
using namespace std; 
#define N 8

void printBoard(int chessboard[][N]){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            cout<<chessboard[i][j]<<" ";
        }
        cout<<endl;
    }
}

// Checks if a queen can be placed at chessboard[row][col]
bool isValidMove(int chessboard[][N], int col, int row){
    
    // If there is a queen in the same row, we can't place our queen at CB[row][col]
    for(int i=0;i<col;i++){
        if(chessboard[row][i] == 1){
            return false;
        }
    }
    
    // No need to check for the same column since we have ensure that 
    // only one queen will be placed in one column. So, no column can contain two queens.
    // for(int i=0;i<row;++i){
    //     if(chessboard[i][col] == 1){
    //         cout<<"Case 2: False"<<endl;
    //         return false;
    //     }
    // }
    
    // If there is a queen in the upper diagonal, we can't place our queen at CB[row][col]
    for(int j=col-1,i=row-1; i>=0 && j>=0; i--,j--){
        if(chessboard[i][j] == 1){
            return false;
        }
    }
    
    // If there is a queen in the lower diagonal, we can't place our queen at CB[row][col]
    for(int j=col-1,i=row+1; j>=0 && i<N; j--,i++){
        if(chessboard[i][j] == 1){
            return false;
        }
    }

    // If it passed all the conditions, we can place a queen here.
    return true;
}

bool solveNQueen(int chessboard[][N], int col){
    
    // If we reached col=N, then we have placed N queens(0 to N-1) on the board. Cheers!
    if(col==N){
        return true;
    }
    
    // Consider this column(col) and try placing this queen in all rows one by one 
    for(int i=0;i<N;i++){
        
        //Check if a queen can be placed at chessboard[i][col]
        if(chessboard[i][col]==0 && isValidMove(chessboard,col,i)){
            
            // Yes, we can place
            chessboard[i][col] = 1;
            
            // recur to place rest of the queens.
            if (solveNQueen(chessboard, col+1)){
                return true;
            }
            
            // If placing queen in board[i][col] doesn't lead to a solution, 
            // then remove queen from board[i][col]
            chessboard[i][col] = 0;
        }
    }
    
    // If the queen cannot be placed in any row in this colum col then return false 
    return false;
}

int main() 
{
    int chessboard[N][N];
    
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            chessboard[i][j] = 0;
        }
    }
    
    if(solveNQueen(chessboard, 0)){
        printBoard(chessboard);
    }
    else{
        cout<<"Can't be solved!"<<endl;
    }

    return 0; 
} 


// -------------------------------------------------------
// LEETCODE N-QUEEN PROBLEM PRINTING THE BOARD WITH QUEENS
// -------------------------------------------------------

class Solution {
public:
    
    bool isValid(vector<vector<int>> board, int row, int col){
        int n= board.size();
        for(int i=0;i<row; i++)                             if(board[i][col] == 1)  return false;
        for(int i=0;i<col; i++)                             if(board[row][i] == 1)  return false;
        for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--)   if(board[i][j] == 1)    return false;
        for(int i=row+1, j=col-1; i<n && j>=0; i++, j--)    if(board[i][j] == 1)    return false;
        return true;
    }
    
    vector<string> convertAns(vector<vector<int>> board){
        int n=board.size();
        vector<string> ans;
        for(int i=0;i<n;i++){
            string s;
            for(int j=0;j<n;j++){
                if(board[i][j] == 1) s+= "Q";
                else s+= ".";
            }
            ans.push_back(s);
        }
        return ans;
    }
    
    void solve(vector<vector<int>>& board, vector<vector<string>>& res, int col){
        int n = board.size();
        if(col == n) {
            vector<string> s = convertAns(board);
            res.push_back(s);
            return;
        }
        
        for(int i=0; i<n; i++){
            if(board[i][col] == 0 && isValid(board, i, col)) {
                board[i][col] = 1;
                solve(board, res, col+1);
                board[i][col] = 0;
            }
        }
    }
    
    vector<vector<string>> solveNQueens(int n) {
        vector<int> t(n,0);
        vector<vector<int>> board(n,t);
        
        vector<vector<string>> res;
        solve(board, res, 0);
        
        return res;
    }
};

// void printBoard(vector<vector<string>> res){
//     int n=res[0].size();
//     for(int i=0;i<2;i++){
//         for(int j=0;j<n;j++){
//             cout<<res[i][j]<<" ";
//         }
//         cout<<endl;
//     }
// }

// ---------------------------------------------------------------------------
// LEETCODE SOLUTION FOR FINDING NUMBER OF WAYS TO SOLVE N-QUEEN FOR A GIVEN N
// ---------------------------------------------------------------------------

class Solution {
public:
    
    bool isValidMove(vector<vector<int>> board, int row, int col){
        int n = board.size();
        for(int i=0; i<row; i++) if(board[i][col] == 1) return false;
        for(int i=0; i<col; i++) if(board[row][i] == 1) return false;
        for(int i=row-1, j=col-1; i>=0 && j>=0; i--, j--) if(board[i][j] == 1) return false;
        for(int i=row+1, j=col-1; i<n  && j>=0; i++, j--) if(board[i][j] == 1) return false;
        return true;
    }
    
    void solve(vector<vector<int>>board, int& res, int col){
        int n = board.size();
        if(col ==n){
            res++;
            return;
        }
        for(int i=0;i<n;i++){
            if(board[i][col] == 0 && isValidMove(board, i, col)){
                board[i][col] = 1;
                solve(board, res, col+1);
                board[i][col] = 0;
            }
        }
    }
    
    int totalNQueens(int n) {
        vector<int> t(n,0);
        vector<vector<int>> board(n,t);
        int res = 0;
        solve(board, res, 0);
        
        return res;
    }
};