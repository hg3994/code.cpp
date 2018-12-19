/* 
Harshit Gupta | 20th October, 2018

KADANE's ALGORITHM 
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/
https://ide.geeksforgeeks.org/Wb4h6KCvgy

C++ program for finding the largest sum contiguous subarray.

Solution: We have to calculate the max so far now in the array. 
        current_max stores the maximum sum subarray at ith position.
        current_max is the max of arr[i] and current_max+arr[i];
        We update the max_so_far if it is lesser than the current_max.
    
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