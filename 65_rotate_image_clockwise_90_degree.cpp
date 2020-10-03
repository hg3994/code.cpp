#include <bits/stdc++.h>
using namespace std;

/*

Harshit Gupta | 29th September, 2020
-------------------------------------

C++ program for "You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
  You have to rotate the image in-place, which means you have to modify the input 2D matrix directly. 
  DO NOT allocate another 2D matrix and do the rotation."


https://leetcode.com/problems/rotate-image/

Input: matrix = [[1,2,3],[4,5,6],[7,8,9]]
Output: [[7,4,1],[8,5,2],[9,6,3]]

------
https://ideone.com/cHhJk5
Solution: We can rotate an image by first transposing and then swapping along the leading diagonal.

Time Complexity: O(n2)
Space Complexity: O(1)

*/


class Solution {
public:
  void rotate(vector<vector<int>>& a) {
    int n = a.size();
    
    /* Transpose the matrix 
      1 2 3      7 8 9 
      4 5 6  =>  4 5 6 
      7 8 9      1 2 3
    */
    for(int i=0;i<n/2;i++){
      for(int j=0;j<n;j++){
        swap(a[i][j], a[n-1-i][j]);
      }
    }
    
    
    /* Swap along the leading diagonal
      1 2 3      7 8 9      7 4 1
      4 5 6  =>  4 5 6  =>  8 5 2
      7 8 9      1 2 3      9 6 3
    
    */
    for(int i=0;i<n;i++){
      for(int j=i+1;j<n;j++){
          swap(a[i][j], a[j][i]);
      }
    }
  }

  void printMatrix(vector<vector<int>> a) {
    int n = a.size();
    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        cout<<a[i][j]<<" ";
      }
      cout<<endl;
    }
  }

};

int main(){
  Solution s;
  vector<vector<int>> a = { {1,2,3}, {4,5,6}, {7,8,9}};
  s.rotate(a);
  s.printMatrix(a);
  return 0;
}