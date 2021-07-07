
/*

Harshit Gupta | 2nd July, 2021
---------------------------------

Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. 
The result should also be sorted in ascending order.

An integer a is closer to x than an integer b if:
    |a - x| < |b - x|, or
    |a - x| == |b - x| and a < b

Example 1:
    Input: arr = [1,2,3,4,5], k = 4, x = 3
    Output: [1,2,3,4]
Example 2:
    Input: arr = [1,2,3,4,5], k = 4, x = -1
    Output: [1,2,3,4]

------

Paradigm: Binary Search
---
  NOTE: 

*/

// Approach 1: TC: O(nlogn)
// Check every number in arr for its distance from x and sort the numbers by this criterion. Then, the answer will be the first k elements of our new sorted array.
// arr = [1,2,3,4,5], k = 4, x = 3
// After sorting: [3,2,4,1,5]
// Choose 1st K elements: [3,2,4,1]
// Sort them since questions asks so: [1,2,3,4]

vector<int> findClosestElements(vector<int>& arr, int k, int x) {

    vector<int> sorted;

    for(auto e: arr)
        sorted.push_back(e);

    // stable_sort() retains the relative order of objects considered equivalent. 
    stable_sort(sorted.begin(), sorted.end(), [&x](int num1, int num2) { return abs(num1-x) < abs(num2-x); });

    sorted.resize(k);
    sort(sorted.begin(), sorted.end());

    return sorted;
}


// Approach: 2 (Two Pointers)
// TC: O(n), SC: O(1)
// We can initialize two pointers L=0 and R=n-1. Now our window size is n and contains excess elements. 
// We will keep reducing the [L, R] window size till it becomes exactly equal to k. We can do this based on the condition x - arr[L] <= arr[R] - x. 
// If it is true, then it means arr[R] is farther away from x than arr[L] and thus we will eliminate arr[R]. Otherwise, we will eliminate arr[L].
vector<int> findClosestElements(vector<int>& arr, int k, int x) {
    int L=0, R=arr.size()-1;
    while(R-L >= k){
        if(x-arr[L] <= arr[R]-x)
            R--;
        else
            L++;
    }
    return vector(arr.begin()+L, arr.begin()+R+1);
}


// Approach 3: Binary Search and Expand from Center TC: O(logN + k)
// In the above approaches, we are not taking any advantage of the fact that input array given to us is already sorted. 
// We can use binary search to find the smallest element in arr which is greater or equal to x. Let's mark this index as R. 
// Let's mark the index preceding to R as L and element at this index will be smaller than x
// Now, [L, R] forms our window of elements closest to x. We have to expand this window to fit k elements. We will keep picking 
// either arr[L] or arr[R] based on whichever's closer to x and expand our window till it contains k elements.
class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n= arr.size();
        int R = lower_bound(arr.begin(), arr.end(), x) - arr.begin(); // LB returns an iterator but we need the index so iterator - begin() gives us the index
        int L =R-1;
        
        while(k--){
            if(R>=n || L>=0 && x-arr[L] <= arr[R]-x ) L--;
            else R++;
        }
        
        return vector(arr.begin()+L+1, arr.begin()+R); // L, R would remain just outside the window so taking L+1, R (since index starts from 0)
    }
};