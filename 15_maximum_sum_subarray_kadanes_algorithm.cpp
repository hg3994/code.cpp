/* 
Harshit Gupta | 20th October, 2018

KADANE's ALGORITHM 
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
https://ide.geeksforgeeks.org/Wb4h6KCvgy
https://leetcode.com/problems/maximum-subarray/

C++ program for finding the largest sum contiguous subarray.

Solution: We have to calculate the max so far now in the array. 
        current_max stores the maximum sum subarray at ith position.
        current_max is the max of arr[i] and current_max+arr[i];
        We update the max_so_far if it is lesser than the current_max.


How is Sliding Window Algorithm different from Kadane's Algorithm?

>> Sliding Window Algorithm calculates the maximum sum subarray for a specific window of size 'k'.
    Kadane's Algorithm calculates the maximum sum subarray for all the subarrays of all possible lengths (1 to n).


// Array:          -2,  -3,  4, -1, -2,  1,  5, -3
// current_max:    -2,  -3,  4,  3,  1,  2,  7,  4
// max_so_far:     -2,  -2,  4,  4,  4,  4,  7,  7 
// Max Subarray:            [4, -1, -2,  1,  5]


Similar Questions:
    1. Similar to this question, it can have "Minimum sum Contiguous Array"
        - Just change the logic from Max to Min

    2. https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray
        - For this, we need both maximum and minimum and the greatest one them is ans
        - Solution below

    3. https://leetcode.com/problems/maximum-product-subarray/
        - This talks about the Maximum Product Subarray, it may not be very simple since 
            0s, -ves play a very important role in the problem.
        - Asked in Mindtickle
*/

#include <bits/stdc++.h>
using namespace std; 

void maxSumSubarray(vector <int> arr){
    int max_so_far = arr[0];
    int current_max = arr[0];
    int start = 0, end = 0;
    for(int i=1;i<arr.size();i++){
        
        // current_max = max(arr[i], current_max+arr[i]);
        
            if(current_max+arr[i] > arr[i]){
                current_max = current_max+arr[i];
            }
            else{
                start = i;
                current_max = arr[i];
            }
        
        // max_so_far = max(current_max, max_so_far);
            if(max_so_far < current_max){
                end = i;
                max_so_far = current_max;
            }
        
        // cout<<"i: "<<i<<" current_max: "<<current_max<<" max_so_far: "<<max_so_far<<" start: "<<start<<" end: "<<end<<endl;
    }
    cout<<max_so_far<<endl;
}

int main(){
    vector <int> arr = {-2, -3, 4, -1, -2, 1, 5, -3};
    maxSumSubarray(arr);
    return 0;
}

// -----------------
// LEETCODE SOLUTION
// -----------------

// KADANES ALGORITHM
class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int n = nums.size();
        int currentMax = nums[0];
        int maxSoFar = nums[0];
        
        for(int i=1;i<n;i++){
            currentMax = max(nums[i], currentMax+nums[i]);
            maxSoFar = max(maxSoFar, currentMax);
        }
        return maxSoFar;
    }
};

// ----------------------------
// Simialar Question 2 Solution
// ----------------------------

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        if(nums.size()==1)
            return abs(nums[0]);
        int maxSoFar = 0;
        int currentMax = 0;
        int currentMin = 0;
        for(int i=0; i<nums.size(); i++){
            currentMax = max(nums[i], nums[i]+currentMax);
            currentMin = min(nums[i], nums[i]+currentMin);
            maxSoFar = max({currentMax, -currentMin, maxSoFar});
        }
        return maxSoFar;
    }
};

// ------------------------------------------------------
// Simialar Question 3 Solution: MAXIMUM PRODUCT SUBARRAY
// ------------------------------------------------------
// 1. While going through numbers in nums, we will have to keep track of the maximum product up to that number 
//     (we will call max_so_far) and minimum product up to that number (we will call min_so_far). 
// 2. The reason behind keeping track of max_so_far is to keep track of the accumulated product of positive numbers. 
// 3. The reason behind keeping track of min_so_far is to properly handle negative numbers.
// 4. max_so_far is updated by taking the maximum value among:
//     - current number: This value will be picked if the accumulated product has been really bad (even compared 
//         to the current number). This can happen when the current number has a preceding zero (e.g. [0,4]) 
//         or is preceded by a single negative number (e.g. [-3,5])
//     - max_so_far * current number: This value will be picked if the accumulated product has been steadily 
//         increasing (all positive numbers).
//     - min_so_far * current number: This value will be picked if the current number is a negative number 
//         and the combo chain has been disrupted by a single negative number before.
// 5. min_so_far is updated in using the same three numbers except that we are taking minimum among the above three numbers.
// 6. result will always be the max of result and maxSoFar.

// [2,3,-2,4,0,2,-3]
// i:0, maxSoFar:  2, minSoFar:   2
// i:1, maxSoFar:  6, minSoFar:   3
// i:2, maxSoFar: -2, minSoFar: -12
// i:3, maxSoFar:  4, minSoFar: -48
// i:4, maxSoFar:  0, minSoFar:   0
// i:5, maxSoFar:  2, minSoFar:   0
// i:6, maxSoFar:  0, minSoFar:  -6
// result: 6
class Solution {
public:
    int maxProduct(vector<int>& nums) {
        int n = nums.size();
        if(n == 0) 
            return 0;
        int maxSoFar=nums[0], minSoFar=nums[0], result=maxSoFar;
        for(int i=1; i<n; i++){
            int temp_maxSoFar   = max(maxSoFar*nums[i], max(minSoFar*nums[i], nums[i]));
            minSoFar            = min(maxSoFar*nums[i], min(minSoFar*nums[i], nums[i]));
            
            maxSoFar = temp_maxSoFar;
            // cout<<maxSoFar<<" "<<minSoFar<<endl;
            result = max(result, maxSoFar);
        }
        return result;
    }
};