/* 
Harshit Gupta | 10th January, 2019

https://www.geeksforgeeks.org/window-sliding-technique/
https://ide.geeksforgeeks.org/7udmhL4VRH

Find maximum sum of a subarray out of all subarrays of size 'k' of an array.
OR,
Given an array of integers of size 'n'. Calculate the maximum sum of ‘k’ consecutive elements in the array.

Sliding Window Algorithm
    
Solution: 
    1. We compute the sum of first k elements out of n terms using a linear loop 
        and store the sum in variable window_sum.
    2. Then we will graze linearly over the array till it reaches the end 
        and simultaneously keep track of maximum sum.
    3. To get the current sum of block of k elements just subtract the first element 
        from the previous block and add the last element of the current block .

Time Complexity: O(n)

How is Sliding Window Algorithm different from Kadane's Algorithm?

>> Sliding Window Algorithm calculates the maximum sum subarray for a specific window of size 'k'.
    Kadane's Algorithm calculates the maximum sum subarray for all the subarrays of all possible lengths (1 to n).

*/

#include <bits/stdc++.h>
using namespace std; 


int sliding_window_maximum_subarray(vector<int> arr, int k){
    
    // array size must be greater than the subarray size
    if (arr.size() < k) 
    { 
       cout << "Invalid"; 
       return -1; 
    } 
    
    int window_sum=0, max_sum;
    
    // Compute sum of first window of size k
    for(int i=0;i<k;i++){
        window_sum+=arr[i];
    }
    
    // The max_sum till now is 'sum'
    max_sum=window_sum;
    
    // Calculate it for other windows/subarrays by 
    // subtracting the last element of previous window 
    // and adding the next element (of the current window)
    for(int i=k;i<arr.size();i++){
        window_sum = window_sum + arr[i] - arr[i-k];
        max_sum = max({window_sum, max_sum});
    }
    
    return max_sum;
    
}

int main(){
    vector<int> array = {1, 4, 2, 10, 23, 3, 1, 0, 20};
    int subarray_size = 4;
    int max_subarray_sum = sliding_window_maximum_subarray(array, subarray_size);
    
    cout<<max_subarray_sum<<endl;
}

// Another implementation of the same algo
// ---------------------------------------

int sliding_window_maximum_subarray2 (vector<int> arr, int k){
    if (arr.size() < k){
        return -1;
    }

    int currentSum = 0;
    int maxSum = INT_MIN;
    int startingIndex = 0;

    for(int i=0; i<arr.size() ; i++){
        currentSum += arr[i];
        int lengthOfWindow = i-startingIndex+1;
        if(lengthOfWindow == k){
            maxSum = max(maxSum, currentSum);
            currentSum -= arr[startingIndex++];
        }
    }
    return maxSum;
}
