/* 
Harshit Gupta | 5th November, 2018

https://ide.geeksforgeeks.org/ob0edrctUY
https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/

C++ program for counting the frequency of an element in a sorted array.

Solution: We use Binary search to find the satrting index of the element.
    We use Binary Search again to find the ending index of the element.
    We get the number of times the element is present by just subtracting.

Paradigm: Binary Search

Time Complexity: O(logn)

*/

#include <bits/stdc++.h>
using namespace std; 

int searchForEndOfNumber(int arr[], int key, int low, int high, int size){
    
    // This means that element is not found.
    if (low>high)
        return -1;
        
    int mid = low + (high-low)/2;
    
    // This means that 'mid' is the ending index of the element 'key'
    // Check for mid+1==size would be if the element is the last element 
    // and mid+1 would go out of bound.
    if(arr[mid] == key && (arr[mid+1]!=key || mid+1==size) ){
        return mid;
    }
    
    // Ending Element is present in the left half if the mid element is greater than the key
    else if(arr[mid]>key)
        return searchForEndOfNumber(arr,key,low, mid-1, size);
    
    // Ending Element is in the right half if arr[mid]==key here
    else
        return searchForEndOfNumber(arr, key, mid+1, high, size);
}

int searchForstartOfNumber(int arr[], int key, int low, int high){
    // This means that element is not found.
    if(low>high)
        return -1;
        
    int mid = low + (high-low)/2;
    
    // This means that 'mid' is the starting index of the element 'key'
    // Check for mid-1==-1 would be if the element is the first element 
    // and mid-1 woudl go out of bound.
    if(arr[mid] == key && (arr[mid-1]!=key || mid-1==-1)){
        return mid;
    }
    
    // Starting Element is in the right half if the mid element is lesser than the key.
    else if(arr[mid]<key)
        return searchForstartOfNumber(arr, key, mid+1, high);
    
    // Starting Element is in the left side if arr[mid]==key here
    else
        return searchForstartOfNumber(arr,key,low, mid-1);
}

int frequencyOfKey(int arr[], int key, int low, int high, int size){
    
    // get the starting index
    int start = searchForstartOfNumber(arr, key, low, high);
    if(start!=-1){
        // If the starting element is found, then we find the ending index.
        int end = searchForEndOfNumber(arr, key, low, high, size);
        // cout<<start<<" "<<end<<endl;
        // return +1 since indexing starts at 0.
        return (end-start+1);
    }
    else
        return -1;
    
}

int main() 
{
    int arr[] = {1, 1, 2, 2, 2, 2, 3, 4, 5, 5, 6, 7, 8, 8, 8, 8, 8, 8, 10};
    int size = sizeof(arr)/sizeof(arr[0]);
    int key = 8;
    int ans = frequencyOfKey(arr, key, 0, size-1, size);
    cout<<ans<<endl;
    return 0; 
} 
