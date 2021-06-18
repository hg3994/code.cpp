
/*

Harshit Gupta | 15th June, 2021
---------------------------------

C++ program for "Power Set of an Array"
https://leetcode.com/problems/subsets/

Given an integer array nums of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
	Input: nums = [1,2,3]
	Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
	Input: nums = [0]
	Output: [[],[0]]

------

Solution: 
	1.	Iterating over all the nums and at each step one takes new integer into consideration 
		and generates new subsets from the existing ones in ans. Then push the new subset into the ans 
		so that the next integer can use it to form new subsets as well
		// 1 2 3
		//      [[]]
		//  n:1 [[],[1]]
		//  n:2 [[],[1],[2],[1,2]]
		//  n:3 [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

	TC: O(Nx2^N) to generate all subsets and then copy them into output list.
	SC: O(Nx2^N) This is exactly the number of solutions for subsets multiplied by the number N of elements to keep for each subset.
	        // For a given number, it could be present or absent (i.e. binary choice) in a subset solution. 
	        // As as result, for NN numbers, we would have in total 2^N choices (solutions).


	2. We map each subset to a bitmask of length n, where 1 on the ith position in bitmask means 
		the presence of nums[i] in the subset, and 0 means its absence.

	TC: O(Nx2^N)
	SC: O(N) to store 'curr'

Paradigm: BitMask
---
  NOTE: 

*/

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        int N = nums.size();
        vector<vector<int>> ans;

        for(int num=0; num<pow(2,N); num++){
            // A 10-bit bitset mask since nums length can be MAX 10

            string bitmask = bitset<10>(num).to_string();
            
            vector<int> curr= {};
            for(int i=10-N;i<10;i++) // Loop for N elements
                if(bitmask[i] == '1')
                    curr.push_back(nums[10-1-i]);
            
            ans.push_back(curr);
        }
        return ans;
    }
};



// Approach 1: Iterating over all the nums and at each step one takes new 
// integer into consideration and generates new subsets from the existing ones. Then push 
// the new subset into the ans so that the next integer can use it to form new subsets as well


vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ans;

    // Insert a blank in the output since this is always true. Very Important!
    ans.push_back({});

    // Iterate over each element of the nums [1,2,3]
    for(int i=0;i<nums.size(); i++){
        // Create a new subset vector eaech time to store the new subsets created with help of nums[i]
        vector<vector<int>> new_subsets;

        // Iterate over all the elements that are already present in the ans array
        for(int j=0; j<ans.size(); j++){
            // Choose each array of the ans and insert the element nums[i] into it. This is an element from our new_subset, 
            // Iterate over all elements of ans and insert nums[i] to create the whole new_subset
            vector<int> x = ans[j];
            x.push_back(nums[i]);
            new_subsets.push_back(x);
        }

        // Iterate over all the elements of new subset and insert it into the ans array
        for(auto subs: new_subsets){
            ans.push_back(subs);
        }
    }
    return ans;
}