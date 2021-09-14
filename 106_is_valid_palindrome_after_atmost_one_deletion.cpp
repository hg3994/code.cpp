
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for "Given a string s, return true if the s can be palindrome after deleting at most one character from it."


Example 1:
    Input: s = "aba"
    Output: true

Example 2:
    Input: s = "abca"
    Output: true
    Explanation: You could delete the character 'c'.

Example 3:
    Input: s = "abc"
    Output: false

------

Solution: 

Time Complexity: O(n)
Space Complexity: O(1)

Paradigm:
---
  NOTE: 

*/

class Solution {
public:
    bool validPalindrome(string s) {
        if(s.size() <= 2)
            return true;
        
        int n = s.size();
        int i=0, j=n-1;
        
        // Traverse with both pointers i & j
        while(i<j){
            // If the characters mismatch, check for the remaining string excluding s[i] and s[j]. (cases like deeee, cbbcc)
            // If any of those substrings is a palindrome, return true, else false
            if(s[i]!=s[j])
                return isPalin(s, i+1, j) || isPalin(s, i, j-1);
            i++; j--;
        }
        return true;
    }
    
    bool isPalin(string s, int l, int r){
        int i=l, j=r;
        while(i<j){
            if(s[i] != s[j])
                return false;
            i++; j--;
        }
        return true;
    }
    
};