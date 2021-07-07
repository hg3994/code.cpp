
/*

Harshit Gupta | 30th June, 2021
---------------------------------

C++ program for 

You are given a string s and an integer k. You can choose any character of the string and change 
    it to any other uppercase English character. You can perform this operation at most k times.
Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:
    Input: s = "ABAB", k = 2
    Output: 4
    Explanation: Replace the two 'A's with two 'B's or vice versa.

Example 2:
    Input: s = "AABABBA", k = 1
    Output: 4
    Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
    The substring "BBBB" has the longest repeating letters, which is 4.

https://leetcode.com/problems/longest-repeating-character-replacement/
------

Solution: 
    Forget about k for a while, how will you find the length of the longest substring containing the same letter?
    X = (length of the string - freq of maximum occuring character in the string)
    This will give us the number of characters which are "NOT" the maximum freq character, we can replace all of them 
    so that the string becomes the same char which is the max occuring character.
    
    Now, how to do the same thing given that we can't change all of X chars but only K chars at max
    We iterate over the string like sliding window and for all possible substrings we check for the condition:
        (length of substring - freq of maximum occuring character in THIS substring) <= k 
    If this condition holds true, then we can replace the OTHER characters to max freq characterto get the same character in the substring,
    Then, we increase the window by 1 size and check if this condition still holds true, if yes, then increase the max same character result.
    After some time, the condition will not hold true since the number of OTHER chars > k and then we cant replace all of them to max freq since they are > k
    Then, we shorten the window from the start and keep checking if the cond. holds true now?
    
    OTHER chars = characters which are not the max freq character.

TC: O(n)
SC: O(1)

Paradigm: Sliding Window
---
  NOTE: 

*/


class Solution {
public:
    
    int characterReplacement(string s, int k) {
        if (s.size() == 0) return 0;
        
        int i=0; // start of sliding window (i.. j-1)
        int j=0; // next char of the window
        int maxCharCount=0, result=0;
        unordered_map<char, int> freq;
        
        // Till we reach the end of the string
        while(j!=s.size()){
            // increase the freq and hold the freq of the maxchar in maxCharCount
            freq[s[j]]++;
            maxCharCount = max(maxCharCount, freq[s[j]]);
            
            // If the number of OTHER chars > k, then we need to reduce this window and keep updating the maxCharCount till the OTHER characters <=k
            // If the OTHER chars <= k, then we can replace all of them into the max Freq character and then all of them will be same.
            while(j-i-maxCharCount+1 > k){
                freq[s[i]]--;
                i++;
                for(auto m: freq)
                    maxCharCount = max(maxCharCount, m.second);
            }
            
            // After the character is adjusted in the window, check if this is the largest window?
            result = max(result, j-i+1);
            j++;
        }
        return result;
    }
};