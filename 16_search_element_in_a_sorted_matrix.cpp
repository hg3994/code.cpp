/* 
Harshit Gupta | 20th October, 2018

https://ide.geeksforgeeks.org/zPZLkQb6OD
https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/
https://leetcode.com/problems/search-a-2d-matrix-ii/

C++ program for finding an element in a sorted matrix.
    The matrix has the following properties:
        - Integers in each row are sorted in ascending from left to right.
        - Integers in each column are sorted in ascending from top to bottom.

    Example: Element to search: 20
        10 40
        20 60

Solution: We will use the property that the matrix is sorted in rows and columns wise.
    * We will start from mat[0][M-1] and if that is the key, then well and good.
        Else, if the element is less than the matrix element, 
            then we can ignore the whole column [M-1] because we know all the elements 
            will be greater than it so, we will search to its left.
        Else, if the element is greater, than we can ignore all the elements in the entire row 
            because we  know all the elements will be smaller than the key.
    * Hence for every check we either move down or left depending on the fact 
        that the number in matrix is smaller/larger than the key.
        

Time Complexity: O(N+M)

NOTE: 
    Similar Question:
        1. https://leetcode.com/problems/search-a-2d-matrix/
        - It is a bit different problem where the following condition holds true but NOT IN ABOVE PROB:
            - The first integer of each row is greater than the last integer of the previous row.
            - Hence we can apply binary search here assuming this to be a sorted 1D array.
            - Example Matrix & element to search 50:
                10 40
                50 60
                

*/

#include <bits/stdc++.h>
using namespace std; 
#define N 4
#define M 4

void findNumInSortedMatrix(int mat[][M], int key){
    int i=0, j=M-1;
    
    // Till we find the element in the matrix or go out of bound(not found element)
    while(mat[i][j]!=key && i<N && j>=0){
        // Move left if the number is greater.
        if(mat[i][j]>key)
            j--;
        else // Move down if it is smaller.
            i++;
    }
    
    if(j>=0 && i<N) // It means mat[i][j]==key
        cout<<"The element "<<key<<" is found at i: "<<i<<" j: "<<j<<endl;
    else
        cout<<"The element is not found"<<endl;
}

int main(){
    int mat[N][M] = {
        {10, 20, 30, 40},
        {15, 25, 35, 45},
        {27, 29, 39, 48},
        {32, 33, 41, 50}
    };
    int key = 10;
    findNumInSortedMatrix(mat, key);
    return 0;
}




// ---------------------------
// LEETCODE Similar Question 1
// ---------------------------


// Approach 1: Intelligent Brute Force : O(n+m)
// Here we search in each row and check if target is within matrix[i][N-1]
// If it is, we search the entire array, otherwise we do the same thing for next row.
bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int m  = matrix.size();
    if(m==0)
      return false;
    int n = matrix[0].size();
    if(n==0)
      return false;
    int i=0;

    while(i<m){
        int j=n-1;
        if(matrix[i][j] >= target){
            while(j>=0){
                if(matrix[i][j] == target){
                    return true;
                }
                j--;
            }
            return false;
        }
        i++;
    }
    return false;
}

// Approach 2: Binary Search: O(log(mn))
// Assume the matrix as one single array and find the mid element.
// The row of the mid element = mid/n and col = mid%n
class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m  = matrix.size();
        if(m==0)
          return false;
        int n = matrix[0].size();
        if(n==0)
          return false;
        int left=0, right=(m*n)-1;
        while(left<=right){
            int mid = left+(right-left)/2;
            int row = mid/n;
            int col = mid%n;
            if(matrix[row][col] == target){
                return true;
            }
            else if (matrix[row][col] < target){
                left = mid+1;
            }
            else {
                right = mid-1;
            }
        }
        return false;
    }
};

