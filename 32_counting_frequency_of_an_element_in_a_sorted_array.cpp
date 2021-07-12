/* 
Harshit Gupta | 5th November, 2018

https://ide.geeksforgeeks.org/ob0edrctUY
https://www.geeksforgeeks.org/count-number-of-occurrences-or-frequency-in-a-sorted-array/

C++ program for counting the frequency of an element in a sorted array.

Solution: We use Binary search to find the starting index of the element.
    We use Binary Search again to find the ending index of the element.
    We get the number of times the element is present by just subtracting.

Examples: 

  Input: arr[] = {1, 1, 2, 2, 2, 2, 3,},   x = 2
  Output: 4 // x (or 2) occurs 4 times in arr[]

  Input: arr[] = {1, 1, 2, 2, 2, 2, 3,},   x = 3
  Output: 1 

  Input: arr[] = {1, 1, 2, 2, 2, 2, 3,},   x = 1
  Output: 2 

  Input: arr[] = {1, 1, 2, 2, 2, 2, 3,},   x = 4
  Output: -1 // 4 doesn't occur in arr[] 
  

Paradigm: Binary Search

Time Complexity: O(logn)

Similar Questions:
    1. https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/
        - Find the starting and ending position of a given target value.
        - If element is not found, return [-1,-1]

#GOOGLE

*/

// ---------------------
// Approach 1: USING STL
// ---------------------
int frequencyOfKey(vector<int> A, int K){
 return upper_bound(A.begin(),A.end(),K)-lower_bound(A.begin(),A.end(),K); //O(log(n))
}

// -----------------------------------------------
// Approach 2: Total Implementation
// -----------------------------------------------

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


// --------------------------------------------------------------
// Similar Prob 1: Finding the start and ending index of element
// --------------------------------------------------------------
// Approach 1:
// Will Find make it O(n) solution?
class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int>ans;
        vector<int>::iterator it, lower, upper;
        it = find(nums.begin(), nums.end(), target);
        if(it != nums.end()){
            lower = lower_bound(nums.begin(), nums.end(), target);
            upper = upper_bound(nums.begin(), nums.end(), target);
            ans.push_back(lower - nums.begin());
            ans.push_back(upper - nums.begin() - 1);
            return ans;
        }
        else{
            return {-1, -1};
        }
    }
};

// Approach 2:
class Solution {
public:
    
    int searchForEnd(vector<int> nums, int target, int low, int  high){
        if(low > high)
            return -1;
        
        int mid = low + (high-low)/2;
        if(nums[mid] == target && (mid+1 == nums.size() || nums[mid+1]!=target) ) {
            return mid;
        }
        else if (nums[mid] > target){
            return searchForEnd(nums, target, low, mid-1);
        }
        else{
            return searchForEnd(nums, target, mid+1, high);
        }
        
    }
    
    int searchForStart(vector<int> nums, int target, int low, int  high){
        if(low > high)
            return -1;
        
        int mid = low + (high-low)/2;
        if(nums[mid] == target && (mid-1 == -1 || nums[mid-1]!=target) ) {
            return mid;
        }
        else if (nums[mid] < target){
            return searchForStart(nums, target, mid+1, high);
        }
        else{
            return searchForStart(nums, target, low, mid-1);
        }
    }
    
    vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.size() == 0)
            return {-1,-1};
        vector<int>ans;
        int start = searchForStart(nums, target, 0, nums.size()-1);
        if(start != -1){
            int end = searchForEnd(nums, target, 0, nums.size()-1);
            return {start, end};
        }
        else{
            return {-1, -1};
        }
    }
};
