
/*

Harshit Gupta | 12th July, 2021
---------------------------------

Given an array arr of positive integers sorted in a strictly increasing order, and an integer k.
Find the kth positive integer that is missing from this array.

Example 1:
    Input: arr = [2,3,4,7,11], k = 5
    Output: 9
    Explanation: The missing positive integers are [1,5,6,8,9,10,12,13,...]. 
        The 5th missing positive integer is 9.

Example 2:
    Input: arr = [1,2,3,4], k = 2
    Output: 6
    Explanation: The missing positive integers are [5,6,7,...]. 
        The 2nd missing positive integer is 6.

------

Solution: Binary Search

TC: O(logN)
SC: O(1)

Paradigm: Binary Search
---
Similar Questions:
    1. https://leetcode.com/problems/missing-element-in-sorted-array/
        - Return the kth missing number starting from the leftmost number of the array 
            (not 1 like previous question)
        - We just need to add Kstart = arr[0]-1 to the ans of prev solution
            & introduce K+Kstart in Binary Search condition.
        - Solution given below

*/


// Approach 1: Linear Search : O(n)
// Ex: [2,3,4,7,11], k=5
// k -= 2-1, so k=4
// i=0, currMissing = 3-2-1 = 0, k=4
// i=1, currMissing = 4-3-1 = 0, k=4
// i=2, currMissing = 7-4-1 = 2, k=2
// i=3, currMissing = 11-7-1= 3, 3>=2, so return 7+2 = 9
class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int n =  arr.size();
        if (k <= arr[0]-1)
            return k;
        // decrease k by num of positive integers which are missing before the array starts
        k -= arr[0]-1;
        
        for(int i=0; i<n-1; i++){
            // missing between arr[i] and arr[i + 1]
            int currMissing = arr[i+1]-arr[i]-1;
            // if the kth missing is between arr[i] and arr[i + 1] -> return it
            if(currMissing >= k)
                return arr[i]+k;
            // otherwise, proceed further
            else
                k -= currMissing;
        }
        
        // if the missing number is greater than arr[n-1]
        return arr[n-1]+k;
        
    }
};


// Approach 2: Binary Search : O(logn)
// Arr[i]:          [2,3,4,7,11], k=5
// Index (i):       [0,1,2,3, 4], 
// arr[i]-(i+1):    [1,1,1,3, 6],

// left=0, right=4, mid=2, arr[mid]-(mid+1) = 1 < k so left=mid+1
// left=3, right=4, mid=3, arr[mid]-(mid+1) = 3 < k so left=mid+1
// left=4, right=4, mid=4, arr[mid]-(mid+1) = 6 > k so right=mid-1
// left=4, right=3, loop break.
// Kth Missing positive is between arr[left]=11 and arr[right]=7
// The number of integers missing before arr[right] is 
//      arr[right] - right - 1
// The number to return is:
//      arr[right] + k - (arr[right] - right - 1) = k + right + 1 = k+ left

class Solution {
public:
    int findKthPositive(vector<int>& arr, int k) {
        int left =0, right = arr.size()-1;
        while(left <= right){
            int mid = left+(right-left)/2;
            if(arr[mid]-mid-1 < k){
                left = mid+1;
            }
            else{
                right = mid-1;
            }
        }
        return left + k;
    }
};


// --------------------------------------------------------
// Leetcode Similar Question 1 Solution using Binary Search
// --------------------------------------------------------

// Similar to: LC-1539 - https://leetcode.com/problems/kth-missing-positive-number/discuss/1333068/c-explained-with-testcases-linear-binary-search-solution
// arr[i]:          [4,7,9,10], k=1, kStart = 3
// i:               [0,1,2, 3]
// arr[i]-(i+1):    [3,5,6, 6]
// left=0, right=3,  mid=1, arr[mid]-(mid+1)=5 > 4, so right=mid-1
// left=0, right=0,  mid=0, arr[mid]-(mid+1)=3 < 4, so left=mid+1
// left=1, right=0, so break & return left+k+Kstart

class Solution {
public:
    int missingElement(vector<int>& nums, int k) {
        int left = 0, right = nums.size()-1;
        int Kstart = nums[0]-1;
        while(left <= right){
            int mid = left + (right-left)/2;
            if(nums[mid]-mid-1 < k+Kstart){         // Condition change here
                left = mid+1;
            }
            else {
                right = mid-1;
            }
        }
        return left+k+Kstart;                       // Return with Kstart
        
    }
};