
/*

Harshit Gupta | 12th July, 2021
---------------------------------

Given two strings s and t, determine if they are isomorphic.
Two strings s and t are isomorphic if the characters in s can be replaced to get t.

All occurrences of a character must be replaced with another character while preserving the 
order of characters. No two characters may map to the same character, but a character may map 
to itself.
https://leetcode.com/problems/isomorphic-strings/

------

Solution: 
    1. We can map a character only to itself or to one other character.
    2. No two character should map to same character.
    3. Replacing each character in string s with the character it is mapped to results in string t.

    We cant do it with 1 map because consider:
        s = "bad"
        t = "bab"

    "b" is mapped with "b", "a" is mapped with "a" and "d" is not mapped, so we map "d" with "b"
    But this is wrong since no two chars can be mapped to same character. To keep track of what is 
    mapped to, we will need another map and when that map says "This "b" is already mapped to, then 
    it raises a red flag.

TC: O(n)
SC: O(n)

Paradigm:
---
  NOTE: The interesting thing about the problem is that users try to do it with just one dict
     and then get frustrated.

*/

class Solution {
public:
    bool isIsomorphic(string s, string t) {
        vector<int> StoT(256, -1);
        vector<int> TtoS(256, -1);
        for(int i=0; i<s.size(); i++){
            // Case 1: No mapping exists in either of the dictionaries
            if(StoT[s[i]] == -1 && TtoS[t[i]] == -1){
                StoT[s[i]] = t[i];
                TtoS[t[i]] = s[i];
            }
            // Case 2: Ether mapping doesn't exist in one of the dictionaries or Mapping exists and
            // it doesn't match in either of the dictionaries or both 
            else if (StoT[s[i]]!=t[i] || TtoS[t[i]]!=s[i]){
                return false;
            }
        }
        return true;
    }
};

