
/*

Harshit Gupta | 10th July, 2021
---------------------------------

Sort an array with the order given in another array.

Given two arrays arr1 and arr2, the elements of arr2 are distinct, and all elements in arr2 are also in arr1.
Sort the elements of arr1 such that the relative ordering of items in arr1 are the same as in arr2.  Elements that 
don't appear in arr2 should be placed at the end of arr1 in ascending order.
https://leetcode.com/problems/relative-sort-array/
------

Solution: 
	1. Create a map of frequencies of letters in arr1
	2. Iterate over arr2 and add the letters with their frequencies number of times in the result & erase them from map
	3. Iterate over the remaining map and add the letters with their freq num. of times in the result

	TC: O(max(n,m)) where n is len(arr2) and m is max frequent letter in arr1
	SC: O(n)

Paradigm:
---
  NOTE: 
	Similar Questions:
		1. https://leetcode.com/problems/custom-sort-string/
			- Exact same question for string.
*/

class Solution {
public:
    vector<int> relativeSortArray(vector<int>& arr1, vector<int>& arr2) {
        map<int, int> map;
        vector<int> res;
        
        // Get the frequency of each letter of arr1 in a map
        for(auto a: arr1)
            map[a]++;
        
        // For all the elements in arr2, get the actual freq
        // and add it in the result (freq. number of times) , remove them from the map
        for(auto a: arr2){
            for(int i=0; i<map[a]; i++)
                res.push_back(a);
            map.erase(a);
        }
        
        // Iterate over the map and the remaining append remaining
        // letters in the map into our result (freq. number of times) 
        for(auto a: map){
            for(int i=0; i<a.second; i++)
                res.push_back(a.first);
            map.erase(a.first);
        }
        return res;
    }
};