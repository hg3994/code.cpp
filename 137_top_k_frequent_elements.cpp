/*

Harshit Gupta | 6th July, 2021
---------------------------------

Given an integer array nums and an integer k, return the k most frequent elements. 
You may return the answer in any order.

https://leetcode.com/problems/top-k-frequent-elements/

Example 1:
	Input: nums = [1,1,1,2,2,3], k = 2
	Output: [1,2]

Example 2:
	Input: nums = [1], k = 1
	Output: [1]

Similar Question: 
	1. https://leetcode.com/problems/reduce-array-size-to-the-half/
		- Reduce the size of array to AT LEAST half by removing min elements.
		- If you remove an element, you must remove all occurances of it.
		- Exact Same solution
------

Solution: 
	1. Create a map of frequencies.
	2. Create a PQ with frequncy,elements.
	3. Pop out K frequent letters.

		[1,1,1,2,2,3] , k=2

		MAP: {
		    1=>3,
		    2=>2,
		    3=>1
		}
		PQ: [{3,1}, {2,2}, {1,3}


TC: O(n)
SC: O(n) for PQ and MAP

Paradigm: Priority Queue
---
  NOTE: 

*/


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> pq;
        unordered_map<int, int> map;
        vector<int> ans;
        
        for(int i=0;i<nums.size(); i++){
            if(map.count(nums[i]))
                map[nums[i]]++;
            else
                map[nums[i]] = 1;
        }
        
        for(auto k: map){
            pq.push({k.second, k.first}); //freq, element
        }
        
        while(k--){
            pair<int, int> front = pq.top();
            ans.push_back(front.second);
            pq.pop();
        }
        return ans;
    }
};