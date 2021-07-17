/* 
Harshit Gupta | 10th February, 2019

https://www.geeksforgeeks.org/trapping-rain-water/
https://ide.geeksforgeeks.org/Laz3IOrHaD
https://leetcode.com/problems/trapping-rain-water/

C++ program for Trapping Rain Water Problem

	Given n non-negative integers representing an elevation map where the width of each bar is 1, 
	compute how much water it is able to trap after raining.

Solution: 

	An element of array can store water if there are higher bars on left and right. We can find amount of water 
		to be stored in every element by finding the heights of bars on left and right sides. The idea is to compute 
		amount of water that can be stored in every element of array.

	Input: arr[]   = {3, 0, 0, 2, 0, 4}
	Output: 10
	Structure is like below
	     |
	|    |
	|  | |
	|__|_| 
	We can trap "3*2 units" of water between 3 an 2,
	"1 unit" on top of bar 2 and "3 units" between 2 and 4.

	An Efficient Solution is to pre-compute highest bar on left and right of every bar in O(n) time. 
		Then use these pre-computed values to find the amount of water in every array element. 

	arr[]   = {3, 0, 0, 2, 0, 4}
	left[]  = {3, 3, 3, 3, 3, 4} -> max(left[i-1], arr[i])
	right[] = {4, 4, 4, 4, 4, 4} -> max(right[i+1], arr[i])

	water[] = min(left[i], right[i]) - arr[i]
						{3-3, 3-0, 3-0, 3-2, 3-0, 4-4}
						{0, 3, 3, 1, 3, 0}

	sum of water = 10

Time Complexity: O(n)
Space Complexity: O(n)


	Space Optimization:
		Instead of maintaing two arrays of size n for storing left and right max of each element, 
		we will just maintain two variables to store the maximum till that point. Since water trapped 
		at any element = min( max_left, max_right) – arr[i] we will calculate water trapped on smaller element 
		out of A[lo] and A[hi] first and move the pointers till lo doesn’t cross hi.


Paradigm: Arrays

*/

#include <bits/stdc++.h>
using namespace std; 

int findWater(vector<int> arr){
    int n = arr.size();
	vector<int> left(n), right(n);
	int water = 0;
	
	left[0] = arr[0];
	for(int i=1;i<n;i++)
		left[i] = max({arr[i], left[i-1]});

	right[n-1] = arr[n-1];
	for(int i=n-2;i>=0;i--)
		right[i] = max(right[i+1], arr[i]);
    
	for(int i=0;i<n;i++)
		water += (min({left[i],right[i]}) - arr[i]);

	return water;
}

int main() 
{
  vector<int> arr = {0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}; 
  cout << "Maximum water that can be accumulated is: "<< findWater(arr);  
  return 0; 
} 

// -----------------------------------------
// LEETCODE SOLUTION WITH SPACE OPTIMIZATION
// -----------------------------------------
// TC: O(n), SC: O(1)
class Solution {
public:
    int trap(vector<int>& height) {
        int water = 0;
        if(height.size()==0) 
            return water;
        
        //find the peak
        int peak = 0;
        for (int i = 1; i < height.size();i++){
            if(height[peak]< height[i]) 
                peak = i;
        }
        
        // calc water on the left side of peak
        // Water filling up at index i would be Ht of Max in Left - My height
        int left_max = 0;
        for (int i = 0; i < peak; i++){
            if(height[left_max]<= height[i])
                left_max = i;
            else
                water+= height[left_max]-height[i];
        }
        
        //calc water on the right side of peak
        // Water filling up at index i would be Ht of Max in Right - My height
        int right_max = height.size()-1;
        for (int i = right_max; i >peak; i--){
            if(height[right_max]<= height[i])
                right_max = i;
            else
                water+= height[right_max]-height[i];
        }
        return water;
    }
};