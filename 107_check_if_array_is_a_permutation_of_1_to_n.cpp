
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for "Given an array arr containing N positive integers, the task is to check if the 
	given array arr represents a permutation or not."

	Input: arr[] = {1, 2, 5, 3, 2} 
	Output: No 
	Explanation: The given array is not a permutation of numbers from 1 to N, because it contains 2 twice, and 4 is missing for the array to represent a permutation of length 5. 

	Input: arr[] = {1, 2, 5, 3, 4} 
	Output: Yes 
	Explanation: 
	Given array contains all integers from 1 to 5 exactly once. Hence, it represents a permutation of length 5. 

https://www.geeksforgeeks.org/check-if-an-array-is-a-permutation-of-numbers-from-1-to-n/
------

Solution: 
	1. Can be done in O(nlon) time if we sort.
	2. Can be done in O(n) extra space by pushing everything in a set and then 
		checking the max of it should be n & the size of set should be n
	3. [EFFICIENT]: Can be done in O(n) time and O(1) space like below:
		Iterate over index 0 to n-1 and change the sign of the numbers in those indexes to negative when accessed. 
			Ex: i=0 [ 1, 3, 0, 4, 2] 
				i=1 [ 1,-3, 0, 4, 2] 
				i=2 [ 1,-3, 0,-4, 2] 
				i=3 [-1,-3, 0,-4, 2] 
				i=4 [-1,-3, 0,-4,-2] 
				i=5 [-1,-3,-0,-4,-2] 
				


Time Complexity: 
Space Complexity:

Paradigm:
---
  NOTE: 

*/

#include <bits/stdc++.h>
using namespace std;


bool checkPermutations(vector<int> v){
	int n= v.size();
	for(int i=0;i<n;i++){
		if(v[i]>=n || v[i]<0)
			return false;
	}
	
	for(int i=0;i<n;i++){
		int abs_vi = abs(v[i]);
		v[abs_vi] = -v[abs_vi];
	}
	
	for(int i=0;i<n;i++){
		if(v[i] > 0)
		return false;
	}
	
	return true;
}

int main() {
	vector<int> v = {1,3,0,4,2};
	if(checkPermutations(v))
		cout<<"Array is a permutation of N"<<endl;
	else
		cout<<"Array is NOT a permutation of N"<<endl;
	return 0;
}