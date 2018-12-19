/* 
Harshit Gupta | 17th October, 2018

C++ program for calculating longest increasing subsequence in O(n2) time

https://www.youtube.com/watch?v=CE2b_-XfVDk
https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/

Solution: We will use very basic dynamic Programming to solve this.
    * At every point, if a number arr[i] is greater than the number arr[j], j<i, 
        then L[i] is maximum of L[j]+1 or L[i]. j iterates from 0 to i (for all elements less than it)
        This is how we will keep track of all the numbers lesser than i and will choose the max L[] and save it in L[i].

*/

#include <bits/stdc++.h>
using namespace std; 

void longestIncreasingSubsequence(vector<int> arr){
    int n = arr.size();
    
    // This vector stores the longest increasing subsequence.
    vector<int> L(n);
    int maximum_increasing_sub=0;
    
    //Initialize the array with 1 since the Longest increasing subsequence at least can be 1.
    for(int i=0;i<n;i++)
        L[i]=1;
    
    // Iterate over all elements from i=1 to n
    for(int i=1;i<n;i++){
        
        // Iterate over all the elements from j=0 to i so that we can save the maximum value in L[i]
        for(int j=0;j<i;j++){
            
            // If the element at j is less than element at i, then we check its L[] 
            // and keep it only if it is greater than what we already have from other arr[j]s.
            if(arr[j]<arr[i]){
                L[i] = max(L[j]+1, L[i]);
            }
        }
    }
    
    for(int i=0;i<n;i++){
        // cout<<L[i]<<" ";
        if(L[i]>maximum_increasing_sub)
            maximum_increasing_sub = L[i];
    }
    
    cout<<maximum_increasing_sub<<endl;
}

int main(){
    vector<int> arr = {3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10};
    longestIncreasingSubsequence(arr);
    return 0;
}