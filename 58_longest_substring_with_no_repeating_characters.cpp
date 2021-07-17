/*

Harshit Gupta | 22nd September, 2020
-------------------------------------

Program for "Length of the longest substring with no repeating characters."

https://leetcode.com/problems/longest-substring-without-repeating-characters/


Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
------

Solution: 
  We will use the Sliding Window Algorithm to get the longest substring without repeating chars.
  - We will have a flexible window and keep on adding unique characters to it.
  - As we get a character which is already present in the window, we have to remove it from the window
  - So we loop from the starting of the window and keep eliminating characters till we reach the 'repeated character' and we remove it as well.
  - Do the same thing again
  - The maximum size of the hash at any time would be the "Length of the longest substring with no repeating characters"

NOTE: This type of Sliding Window solution can be used in a lot of these types of problems
  Find the longest substring with "....."

  - Find the longest substring with at max 2 distinct characters.
      https://leetcode.com/problems/fruit-into-baskets/
      https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

  - Find the longest substring with at most K distinct characters
      https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/

  - Find the longest substring with containing the same character but with K replacements allowed:
      Solved in 124_...

*/

class Solution {
public:
    
    // Solved using Sliding Window
    
    int lengthOfLongestSubstring(string s) {
        if (s == "")
            return 0;

        // map to hold the characters which are in the flexi sliding window (i, j-1)
        unordered_map<char, bool> map;
        int i = 0; // i is the starting of the flexi window
        int j = 1; // j is the next element of the flexi window
        int maxLen = 1;
        map[s[0]] = true;
        
        // Till we reach the end of the string
        while(j != s.size()) {

            // If s[j] is not a repeating element since it is not in map
            // then put it in the map and recalculate the maxLen, move ahead j++
            if(map.find(s[j]) == map.end()){
                map[s[j]] = true;
                maxLen = max(maxLen, j-i+1);
                j++;
            }

            // Else if s[j] is a repeating element since it is in map
            // move the start of window till we reach the matching character 
            // and keep removing the letters from map. Once you find the matching char, move ahead
            else {
                while(s[i]!=s[j]){
                    map.erase(s[i]);
                    i++;
                }
                map.erase(s[i]);
                i++;
            }
        }
        return maxLen;
    }
};


// -------------------------------------------------
// https://leetcode.com/problems/fruit-into-baskets/
// At Max 2 distinct Characters
// -------------------------------------------------

class Solution {
public:
    int totalFruit(vector<int>& tree) {
        if(tree.size() <= 1)
            return tree.size();
        
        int i=0;
        int j=1;
        int maxLength = 1;
        unordered_map<int, int> map;
        map[tree[0]] = 1;
        
        while(j!=tree.size()){
            // char is already present in the map
            if(map.find(tree[j]) != map.end()){
                map[tree[j]]++;
                maxLength = max(maxLength, j-i+1);
                j++;
            }
            // char is not present in the map and the size of map is 0(no elements, this is the first char) or 1(one element, this is 2nd char)
            else if (map.size() == 0 || map.size() == 1) {  // map.size() < 2
                map[tree[j]] = 1;
                maxLength = max(maxLength, j-i+1);
                j++;
            }
            // char is not present in map and there are already 2 distinct chars in the map
            else {
                while(i<j){
                    map[tree[i]]--;
                    if(map[tree[i]] == 0){
                        map.erase(tree[i]);
                        i++;
                        break;
                    }
                    i++;
                }
                map[tree[j]] = 1;
                j++;
            }
        }
        return maxLength;
    }
};

// --------------------------------------------------------------------------------
// https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/
// At Max K distinct Characters
// --------------------------------------------------------------------------------

class Solution {
public:
    int lengthOfLongestSubstringKDistinct(string s, int k) {
        if(k == 0)
            return 0;
        unordered_map<char, int> map;
        int i=0, j=1, maxLen=1;
        map[s[i]]=1;
        while(j<s.size()){
            // char is already present in the map, so increase freq
            if(map.count(s[j])){
                map[s[j]]++;
                maxLen = max(maxLen, j-i+1);
                j++;
            }
            // char is not present but our window has space since distinct char <k
            else if(map.size() < k){
                map[s[j]]++;
                maxLen = max(maxLen, j-i+1);
                j++;
            }
            // char is not present and our window have no space since distinct char =k
            // make space for a char by moving from start(i) till any one element freq=0
            else {
                while(i<j) {
                    map[s[i]]--;
                    if(map[s[i]] == 0){
                        map.erase(s[i]);
                        i++;
                        break;
                    }
                    i++;
                }
                // update the jth char with 1 freq
                map[s[j]] = 1;
                j++;
            }
            // MUST NOT update maxLen here since we have increased j++ already 
            // so done in individual cases
        }
        return maxLen;
    }
};