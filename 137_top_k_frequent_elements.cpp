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


TC: O(nlogn)
SC: O(n) for PQ and MAP

Paradigm: Priority Queue


Similar Question: 
	1. https://leetcode.com/problems/reduce-array-size-to-the-half/
		- Reduce the size of array to AT LEAST half by removing min elements.
		- If you remove an element, you must remove all occurances of it.
		- Exact Same solution

    2. https://leetcode.com/problems/sort-characters-by-frequency/
        - Given a string s, sort it in decreasing order based on the frequency 
            of characters, and return the sorted string.

    3. https://leetcode.com/problems/sort-array-by-increasing-frequency/
        - Sort the array in increasing order based on the frequency of the values. 
        - If multiple values have the same frequency, sort them in decreasing order.
        - The second point is the trick which requires a custom comparator function since by default
            it is in increasing order (I guess)
---
NOTE: 
    1. Asked in Google.

*/


class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        priority_queue<pair<int, int>> pq;
        unordered_map<int, int> freq;
        vector<int> ans;
        
        for(int i=0;i<nums.size(); i++)
            freq[nums[i]]++;
        
        for(auto k: freq){
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

// ----------------------------
// Similar Question 1: Solution
// ----------------------------

class Solution {
public:
    int minSetSize(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, int> freq;
        priority_queue<pair<int,int>> pq;
        int ans=0;
        
        for(int i=0; i<arr.size(); i++){
            freq[arr[i]]++;
        }
        for(auto e: freq){
            pq.push({e.second,e.first});
        }
        int pq_elements = arr.size();
        while(pq_elements > arr.size()/2){
            pair<int, int> f = pq.top();
            pq.pop();
            pq_elements -= f.first;
            ans+=1;
        }
        return ans;
    }
};

// ----------------------------
// Similar Question 2: Solution
// ----------------------------

// Approach 1: Using above STLs
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char, int> freq;
        priority_queue<pair<int, int> > pq;
        string ans;
        
        for(int i=0; i<s.size(); i++)
            freq[s[i]]++;
        
        for(auto m: freq)
            pq.push({m.second, m.first});
        
        while(!pq.empty()){
            pair<int, int> f = pq.top();
            pq.pop();
            for(int i=0; i<f.first; i++)
                ans+= f.second;
        }
        return ans;
    }
};

// Approach 2: Solution using sort - Slower than the PQ solution
class Solution {
public:
    string frequencySort(string s) {
        int counts[256] = {0};
        for (char ch : s)
            ++counts[ch];
        sort(s.begin(), s.end(), [&](char a, char b) { 
            return counts[a] > counts[b] || (counts[a] == counts[b] && a < b); 
        });
        return s;
    }
};


// ----------------------------
// Similar Question 3: Solution
// ----------------------------

class Solution {
public:
    
    // static bool myCmp (pair<int, int>&a, pair<int, int>&b){
    //     // if freq are equal then consider the letter itself
    //     return (a.second == b.second) ? a.first > b.first : a.second < b.second;
    // }
    
    vector<int> frequencySort(vector<int>& nums) {
        
        map<int, int> freq;
        vector<pair<int,int>> val_freq;
        vector<int> ans;
        
        for(int i=0; i<nums.size(); i++)
            freq[nums[i]]++;
        
        for(auto m: freq){
            val_freq.push_back(m);
        }
        
        // sort(val_freq.begin(), val_freq.end(), myCmp);
        sort(val_freq.begin(), val_freq.end(), [&](pair<int, int> a, pair<int, int> b){
            return (a.second == b.second) ? a.first > b.first : a.second < b.second;
        });
        
        for(auto val: val_freq){
            // push the 'val' freq number of times.
            for(int i=0;i<val.second; i++){
                ans.push_back(val.first);
            }
        }
        
        return ans;
    }
};