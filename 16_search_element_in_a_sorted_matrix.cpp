/* 
Harshit Gupta | 20th October, 2018

https://ide.geeksforgeeks.org/zPZLkQb6OD
https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/

C++ program for finding an element in a sorted matrix.

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
        - It is a bit different where the following condition holds true but not here:
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
    
    if(mat[i][j]==key)
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