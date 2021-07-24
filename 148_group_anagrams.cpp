
/*

Harshit Gupta | 20th July, 2021
---------------------------------

Problem Statement:

Given an array of strings strs, group the anagrams together. You can return the answer in any order.

Example 1:
    Input: strs = ["eat","tea","tan","ate","nat","bat"]
    Output: [["bat"],["nat","tan"],["ate","eat","tea"]]
Example 2:
    Input: strs = [""]
    Output: [[""]]
Example 3:
    Input: strs = ["a"]
    Output: [["a"]]

------

Solution: 
    1. Create a hashmap of string to vector<strings>
    2. Sort the string and insert the sorted string as the key and the actual string as the value in a hashmap
    3. Just return all the value vectors.
  TC: O(N*KlogK) for N strings having length K
  SC:

Paradigm: HashMaps
---
  NOTE: 

*/




// SOLUTION 1 : O(N KlogK)
// ----------
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& s) {

        vector<vector<string>> ans;
        unordered_map<string, vector<string>> M;
        
        for(int  i = 0; i < s.size(); i++) {
            string str = s[i];
            sort(s[i].begin(), s[i].end()); // Sorting the string
            M[s[i]].push_back(str);  // Sorted string is the key and the value is the initial string
        }
        for(auto i : M)
            ans.push_back(i.second);  // Traversing the map and adding the vectors of string to ans
        return ans;

    }
};



// SOLUTION 2: O(N*K*M) N: length of string arr, K: length of maximum string, M: no. of comparisons in all maps (M = X square)
// Bad solution but gets accepted
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& s) {  
        vector< pair< map<char,int>, vector<string>> > ans;
          
        for(int i=0;i<s.size(); i++){
            string a = s[i];
            map<char, int> mp;
            bool found = false;
            
            for(int j=0; j<a.size(); j++){
                mp[a[j]]++;
            }
            
            for(int k=0;k<ans.size(); k++){
                if (ans[k].first == mp){
                    ans[k].second.push_back(a);
                    found=true;
                    break;
                }
            }
            if(found == false){
                vector<string> v; v.push_back(a);
                ans.push_back(make_pair(mp, v));
            }
        }

        vector<vector<string>> result;
        for(int k=0;k<ans.size(); k++){
            result.push_back(ans[k].second);
        }

        return result;
    }
};

