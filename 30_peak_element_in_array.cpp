/* 
Harshit Gupta | 2nd November, 2018

https://ide.geeksforgeeks.org/rbmr5e2qf8
https://www.geeksforgeeks.org/find-a-peak-in-a-given-array/
https://leetcode.com/problems/find-peak-element/

C++ program for Finding a peak element in an array. 
    An array element is peak if it is NOT smaller than its neighbors. 
    For corner elements, we need to consider only one neighbor. 
    For example, for input array {5, 10, 20, 15}, 20 is the only peak element. 
    For input array {10, 20, 15, 2, 23, 90, 67}, there are two peak elements: 20 and 90. 
    Note that we need to return any one peak element.

Solution: We can use Divide and Conquer to find a peak in O(Logn) time. 
    The idea is Binary Search based, we compare middle element with its neighbors.
    If middle element is not smaller than any of its neighbors, then we return it.
    If the middle element is smaller than the its left neighbor, 
        then there is always a peak in left half (Why? take few examples). 
    If the middle element is smaller than the its right neighbor, 
        then there is always a peak in right half (due to same reason as left half).

Paradigm: Divide and Conquer

Time Complexity: O(logn)

Similar Question:
    1. https://leetcode.com/problems/find-a-peak-element-ii/
        - Finding peak element in a 2D matrix.
*/

#include <bits/stdc++.h>
using namespace std; 

int findPeakElement(int *arr, int l, int h){
    int m = l+(h-l)/2;
    
    // Base condition:  Compare middle element with its neighbours (if neighbours exist)
    // cond1 satisfies when the element is first or is greater than the left
    // cond2 satisfies when the element is last or is greater than the right
    // If the peak element is somewhere in between a[m-1]<=a[m]>=a[m+1] is satisfied.
    // If the peak element is at first:  m==0 && arr[m]>=a[m+1] , last: a[m] >= a[m-1] && m==h-1

    if((m==0 || arr[m]>=arr[m-1]) && (m==h-1 || arr[m]>=arr[m+1])){
        return arr[m];
    }
    
    // If middle element is not peak and its left neighbour is greater  
    // than it, then left half must have a peak element 
    if(m>0 && arr[m-1]>arr[m]){
        return findPeakElement(arr,l,m-1);
    }
    
    // If middle element is not peak and its right neighbour is greater 
    // than it, then right half must have a peak element 
    else { // if(m<n-1 && arr[m+1]>arr[m])
        return findPeakElement(arr,m+1,h);
    }
}

int main() 
{
    int arr[] = {10, 20, 15, 2, 23, 90, 67};
    // int arr[] = {10, 20, 30, 40, 50, 60, 70};
    // int arr[] = {70, 60, 50, 40, 30, 20, 10};
    // int arr[] = {5, 10, 20, 15};
    
    int n = sizeof(arr)/sizeof(arr[0]);
    int p = findPeakElement(arr,0,n-1);
    if(p!=-1)
        cout<<p<<" is the peak element."<<endl;
    else
        cout<<"-1"<<endl;
        
    return 0; 
} 
