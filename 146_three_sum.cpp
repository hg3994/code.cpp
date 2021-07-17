
/*

Harshit Gupta | 16th July, 2021
---------------------------------

Problem Statement:

1. https://leetcode.com/problems/3sum/
	- Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]] 
		such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.
		Notice that the solution set must not contain duplicate triplets.
	- They must Sum to to 0.

2. https://leetcode.com/problems/3sum-smaller/
	- Given an array of n integers nums and an integer target, find the number of index 
		triplets i, j, k with 0 <= i < j < k < n that satisfy the condition 
			nums[i] + nums[j] + nums[k] < target.
	- 	Input: nums = [-2,0,1,3], target = 2
		Output: 2
		Explanation: Because there are two triplets which sums are less than 2: 
			[-2,0,1], [-2,0,3]
	- TODO

3. https://leetcode.com/problems/3sum-closest/
	- Given an array nums of n integers and an integer target, find three integers 
		in nums such that the sum is closest to target. Return the sum of the three integers.
	- 	Input: nums = [-1,2,1,-4], target = 1
		Output: 2
		Explanation: The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
	- TODO

4. https://leetcode.com/problems/4sum/
	- Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
		nums[a] + nums[b] + nums[c] + nums[d] == target
	- This is basically a problem which generalizes Ksum so we will try to implement that
	- TC: O(n3)
------

Paradigm:
---
  NOTE: 

*/


class Solution {
public:
    
    // Search for two elements in sorted nums[i+1..n] such that arr[i]+arr[x]+arr[y]==0
    void twoSum(vector<int>& nums, int i, vector<vector<int>>& ans){
        int low = i+1;
        int high = nums.size()-1;
        while(low < high) {
        	int sum = nums[low]+nums[high]+nums[i];
            if (sum > 0)
                high--;
            else if (sum < 0)
                low++;
            else { // sum == 0
            	// Include it in the answer, update low and high to search for more ans.
                ans.push_back({nums[i], nums[low], nums[high]});
                low++;
                high--;

                // To prevent duplicates, we move ahead if there are similar elements
                // No need to do the same thing for high since it will be taken care by this loop
                // when it reaches duplicate highs
                while(low < high && nums[low-1] == nums[low]) 
                	low++;
            }
        }
    }
    
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() <= 1) {
            return ans;
        }
        sort(nums.begin(), nums.end());
        for(int i=0;i< nums.size()-2; i++) {
            // If you're the first element or you're same as nums[i-1]
            // We do this to prevent duplicate answers.
            if (i == 0 || nums[i] != nums[i-1]) {
                twoSum(nums, i, ans);
            }
        }
        return ans;
    }
};



// -----
// K-SUM
// -----
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        return KSum(nums, target, 0, 4);
    }
    
    // Remember that nums is sorted for this function
    // We will keep increasing start and decreasing k
    vector<vector<int>> KSum(vector<int>& nums, int target, int start, int k){
        vector<vector<int>> res;
        // Check if the sum of k smallest values is greater than target, 
        // OR the sum of k largest values is smaller than target. 
        // Since the array is sorted, smallest value is nums[start], and largest is nums.back()
        if(start == nums.size() || nums[start]*k > target || target > nums.back()*k)
            return res;
        if(k == 2)
            return twoSum(nums, target, start);
        for(int i= start; i<nums.size(); i++){
            if (i == start || nums[i-1]!=nums[i]){
                // Keep reducing the Ksum to ..3sum, 2sum by fixing nums[i] & looking for
                // target-nums[i] in the rest of the arr starting from i+1
                for(auto &set: KSum(nums, target-nums[i], i+1, k-1)){
                    res.push_back({nums[i]});
                    res.back().insert(end(res.back()), begin(set), end(set));
                }
            }
        }
        return res;
    }
    
    // Hashset 2Sum Implementation
    vector<vector<int>> twoSum(vector<int>& nums, int target, int start) {
        vector<vector<int>> res;
        unordered_set<int> s;
        for (auto i = start; i < nums.size(); ++i) {
            if (res.empty() || res.back()[1] != nums[i])
                if (s.count(target - nums[i]))
                    res.push_back({ target - nums[i], nums[i]});
            s.insert(nums[i]);
        }
        return res;
    }
    
    // Iterative Two Sum using sorted list
    // vector<vector<int>> twoSum(vector<int>& nums, int target, int start) {
    //     vector<vector<int>> res;
    //     int lo = start, hi = nums.size() - 1;
    //     while (lo < hi) {
    //         int sum = nums[lo] + nums[hi];
    //         if (sum < target || (lo > start && nums[lo] == nums[lo - 1]))
    //             ++lo;
    //         else if (sum > target || (hi < nums.size() - 1 && nums[hi] == nums[hi + 1]))
    //             --hi;
    //         else
    //             res.push_back({ nums[lo++], nums[hi--]});
    //     }
    //     return res;
    // }
    
};