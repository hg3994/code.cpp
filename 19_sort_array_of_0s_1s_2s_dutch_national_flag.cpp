/* 
Harshit Gupta | 20th October, 2018

http://users.monash.edu/~lloyd/tildeAlgDS/Sort/Flag/
https://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/
https://ide.geeksforgeeks.org/fEZHX0McCw
https://leetcode.com/problems/sort-colors/

C++ program for Sorting ana array of 0s, 1s and 2s.

Solution: We will divided the array into 4 parts with help of three pointers.
    - [0..low-1]: Will contain 0s.
    - [low..mid-1]: Will contain 1s.
    - [mid..high]: Will contain UNKNONWS.
    - [high+1..n]: Will contain 2s.
    
    *   low: points to the starting of 1s. (NOT STARTING OF 0s)
        mid: points to the starting of UNKNONWS (NOT ENDING OF 1s)
        high: points to the ending of UNKNONWS (NOT STARTING OF 2s)

    *   We will start with all in the UNKNOWNS bracket and then gradually move pointers
        so that this UNKNOWN window reduces to 0. We swap values and move pointers to do it.

Time Complexity: O(n)

*/

#include <bits/stdc++.h>
using namespace std; 

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort0s1s2s(vector<int> arr){
    int n= arr.size();
    
    // Start with everything in the UNKNOWN bracket.
    int low = 0;
    int mid = 0;
    int high = n-1;
    
    // We need to reduce the unknowns set, and till it becomes 0, we loop
    while(mid<=high){ 
        
        // If arr[mid] is 0, then throw it in the front. Move so that 
        // low points to the starting of 1s
        // mid-1 points to the ending of 1s.
        if(arr[mid]==0){
            swap(&arr[mid],&arr[low]);
            low++;
            mid++;
        }
        
        // If arr[mid] is 1, then we just move the mid's ending by 1.
        // It means that this is already in the correct place 
        else if(arr[mid]==1){
            mid++;
        }
        
        // If arr[mid] is a 2, then we throw it in the back and 
        // get a new element in place of it. That will be treated in the next turn since 
        // mid is not getting increased. We decrease high by one 
        // since we have settled a 2 there.
        else{
            swap(&arr[high],&arr[mid]);
            high--;
        }
        
        // Uncomment to see the array changing at every stage.
        // for(int i=0;i<n;++i)
        //     cout<<arr[i]<<" ";
        // cout<<endl;
    }
    
    for(int i=0;i<n;++i)
        cout<<arr[i]<<" ";
    cout<<endl;
    
}

int main(){
    vector<int> arr = { 1, 0, 2, 2, 0, 1, 2, 2, 0, 0, 1, 2};
    sort0s1s2s(arr);
    return 0;
}