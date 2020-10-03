/*

Harshit Gupta | 29th September, 2020
-------------------------------------

C++ program for "You are given an array of positive integers nums.
Count and print the number of (contiguous) subarrays where the product of all the elements in the subarray is less than k."

https://leetcode.com/problems/subarray-product-less-than-k/


Input: nums = [10, 5, 2, 6], k = 100
Output: 8
Explanation: The 8 subarrays that have product less than 100 are: [10], [5], [2], [6], [10, 5], [5, 2], [2, 6], [5, 2, 6].
Note that [10, 5, 2] is not included as the product of 100 is not strictly less than k.
------

Solution: We solve this using sliding window algorithm.
  - Take the starting and ending of the window and loop till end of window reaches the end of arr.
  - You keep trying to add arr[end] into the window.
  - At each step, there are two possibilities:
    - If including arr[end] in window can cause product in window to overflow k,
        Then start eliminating characters from the start till the window has only product<k
        Now calculate the num of subarrays and add it in result.
    - If including arr[end] in window can cause product in window to NOT overflow k,
        Then calculate the num of subarrays and add it in result.

https://ideone.com/4nmy3I

Time Complexity: O(n)
Space Complexity: O(1)

*/
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int numSubarrayProductLessThanK(vector<int>& nums, int k) {
    int result = 0;
    int start = 0;
    int end = 0;
    int n = nums.size();
    int product = 1;
    
    // Till the end of the window reaches the end of the array
    while(end<n){
      
      // Get the next item into the window
      product *= nums[end];
      
      // If product >= k, then we need to correct the starting of window till we have product < k
      // We remove the character from the window starting by moving the start++ and 
      // re-calculate the 'product'.
      // // [10,5,2] and start=0, end=2, k=100, product = 100, so we shift start, start=1 now, product=10
      while (start < end && product >= k)  
          product /= nums[start++];
      
      // Now that we have the product less than k, get the subarrays count.
      // We increase the subarray count by "end-start+1" (length of the window now)
      // If we add index 'n' in the window, we have 'n' subarrays which would add up in the solution
      //    a[0...n], a[1...n], .. a[n]
      if (product < k)   // This condition is actually not needed since it will reach here only when product < k
        result += (end-start)+1;
        
      // We must write the while condition above the if condition because after sliding the window from the front till product<k, we still need to calculate the subarrays for that subarray.
      // [10,5,2] and start=0, end=2, k=100, product = 100, so we shift start, start=1 now.
      // Now we need to add (end-start+1) = (2-1+1) = 2 for the subarrays [2], [5,2].
      end++;
    }
    return result;
  }
};


int main(){
  s = Solution.new()
  int r = s.numSubarrayProductLessThanK();
  cout<<r<<endl;
}