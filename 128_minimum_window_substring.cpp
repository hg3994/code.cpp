
/*

Harshit Gupta | 1st July, 2021
---------------------------------

C++ program for "Minimum Window Substring"

Given two strings s and t of lengths m and n respectively, return the minimum window 
substring of s such that every character in t (including duplicates) is included in the window. 
If there is no such substring, return the empty string "".

A substring is a contiguous sequence of characters within the string.

Example 1:
	Input: s = "ADOBECODEBANC", t = "ABC"
	Output: "BANC"
	Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
	Input: s = "a", t = "a"
	Output: "a"
	Explanation: The entire string s is the minimum window.

Example 3:
	Input: s = "a", t = "aa"
	Output: ""
	Explanation: Both 'a's from t must be included in the window.
	Since the largest window of s only has one 'a', return empty string.

https://leetcode.com/problems/minimum-window-substring/

------

Solution: Sliding Window
	1. We take a dictionary and store the characters and frequencies of 't' in a map
	2. A variable 'required' would be the size of the dict meaning these many 
		variables with the freq are to be present in the smallest window of 's'
	3. We need to iterate over s with help of two points 'l' and 'r' forming a window. 
		All the characters in this window will be stored in a map called window
	4. We need to keep adding a character s[r] and include it in the window (Expand the window)
	5. After every addition, we need to check if the current window has all chars with necessary 
		freq of all chars of 't'
	6. Once a window has everything, we will try to shrink it by increasing 'l' and 
		check if it still has everything necessary.
	7. The minimum of all such windows in the solution.

  This is a simple & classic Sliding window problem, the tricky part is that the window has to contain
  	X letters with their own freqencies (basically checking if it contains a special string 't')
  	We can easily deal with it by inserting 't' into a dict with their freq and check if the window
  	contains all letters with their freq in it.
  	We do this checking with the help of required and formed variables which check the number 
  	of unique chars in the window, if they are equal and the frequencies are equal, then the string 't'
  	is in the window

TC: O(n)
SC: O(n) for maps

Paradigm: Sliding Window

#Agoda

---

NOTE: 
	Simialar Question: https://leetcode.com/problems/permutation-in-string/
		- We are asked to check if any permutation of s1 is present in s2? Return true if present else false.
			Input: s1 = "ab", s2 = "dbao"
			Output: true
			---
			Input: s1 = "ab", s2 = "dboao"
			Output: false
		
		- It has a simialr ask of checking if a perm of s1 is present at any point of time, so we can use a 
			similar sliding window algo and check if the window contains all the characters of s2 with required
			frequencies? Return true if it is present, else false.


	Another Similar Question: https://leetcode.com/problems/find-all-anagrams-in-a-string/
		- Here we just need to return all the STARTING indexes of all permutations present in the string.
		- Just push the starting indexes instead of returning true from last question
			if(j-i+1 == s1.size()){
                ans.push_back(i);
            }

---

*/
class Solution {
public:
  string minWindow(string s, string t) {
    if (s==t)
      	return s;
    
    if(s.length() == 0  || t.length() == 0 || t.size()> s.size()){
      	return "";
    }
    
    // Dictionary which keeps a count of all the unique characters in t & their freq
    unordered_map<char, int> dictT;
    for(int i=0;i<t.size();i++){
		if (dictT.count(t[i]))
			dictT[t[i]] += 1;
		else
			dictT[t[i]] = 1;
    }
    
    // Number of unique characters in t, which need to be present in the desired window.
    int required = dictT.size();
    
    // Left and Right pointer for the sliding window
    int l = 0, r = 0;
    
    // formed is used to keep track of how many unique characters in t
    // are present in the current window in its desired frequency.
    // e.g. if t is "AABC" then the window must have two A's, one B and one C.
    // Thus formed would be = 3 when all these conditions are met.
    int formed = 0;
    
    // Dictionary which keeps a count of all the unique characters & their freq in the current window.
    unordered_map<char, int> window;
    
    string ans = "";
    
    while(r < s.length()){
		// Trying to add s[r] into the current window
		// Update the frquency of the current character in the window.
		if(window.count(s[r])){
			window[s[r]] = window[s[r]]+1;
		}
		else{
			window[s[r]] = 1;
		}

		// If the frequency of the current character added equals to the
		// desired count in t then increment the formed count by 1.
		if(dictT.count(s[r]) && window[s[r]] == dictT[s[r]])
			formed++;

		// Try and contract the window to get the minimum length ... till the point where it ceases to be 'desirable'.
		while (l<=r && formed == required) {
			  
			// Save the smallest window until now.
			if(ans == "" || (r-l+1) < ans.size() ) {
			    ans = s.substr(l, r-l+1);
			}

			// The character at the position pointed by the
			// `Left` pointer is no longer a part of the window.
			window[s[l]] =  window[s[l]] - 1;

			if(dictT.count(s[l]) && window[s[l]] < dictT[s[l]] ) {
			    formed--;
			}

			l++;
		}
		r++;
    }
    
    return ans;
  }
};



// ----------------------------------------
// LEETCODE 2nd Question: Check if any permutation of s1 is present in s2? Return true if present else false.
// ----------------------------------------

class Solution {
public:
    bool checkInclusion(string s1, string s2) {
        if(s1 == s2)
            return true;
        
        unordered_map<char, int> mapS1;
        for(auto c: s1){
            if(mapS1.count(c))
                mapS1[c]++;
            else
                mapS1[c] = 1;
        }
        
        int required = mapS1.size();
        int i=0, j=0, formed = 0;
        unordered_map<char, int> window;
        
        while(j < s2.size()){
            
            if(window.count(s2[j]))
                window[s2[j]]++;
            else
                window[s2[j]] = 1;
            
            if( mapS1.count(s2[j]) && mapS1[s2[j]] == window[s2[j]] )
                formed++;
            
            while (i<=j && formed == required) {
                
                // If the size of the window == the size of s1 && obviously formed == required from above 
                // check (meaning all letters in s1 are present in window & their freq in s1 are fine)
                // then this must be a perm of s1 without any EXTRA letter in it
                if(j-i+1 == s1.size()) {
                    return true;
                }
                
                window[s2[i]]--;

                if(mapS1.count(s2[i]) && window[s2[i]] < mapS1[s2[i]])
                    formed--;

                i++;
            }
            j++;
        }
        return false;
    }
};