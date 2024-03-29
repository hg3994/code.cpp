/*

Harshit Gupta | 30th September, 2020
-------------------------------------

C++ program for "Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, 
  determine if s can be segmented into a space-separated sequence of one or more dictionary words."

https://leetcode.com/problems/word-break/
https://www.geeksforgeeks.org/word-break-problem-dp-32/


Input: s = "applepenapple", wordDict = ["apple", "pen"]
Output: true
Explanation: Return true because "applepenapple" can be segmented as "apple pen apple".
             Note that you are allowed to reuse a dictionary word.

Input: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
Output: false
------

Solution: We solve this using Recursion and DP/Memoization.
    - We create a map of words in the dictionary for O(1) answer to "is it in my dict?"
    - We create a memo[] array for not solving the same subproblem>1 time
    - We try to divide the string into two parts with "start"/"end" variable
      s[start..end] | s[end+1..n]
    - We check for "s[start..end]" word in our dictionary and 
        if it is present, we try to solve the same problem for s[end+1..n]
    - If we tried everything and it was not able to satisfy the above condition, return false.

https://ideone.com/5iKdpg

Time Complexity: O(n3) Size of recursion tree can go up to n^2 & substr method taken O(n).
Space Complexity: O(n) for memo array

TC WITHOUT MEMO: Time complexity : O(2^n) Given a string of length n, there are n + 1n+1 ways to split it into two parts. 
    At each step, we have a choice: to split or not to split. In the worse case, when all choices are to be checked, that results in O(2^n).

Similar Problems:
    1. https://leetcode.com/problems/word-break-ii/solution/
        - TODO (Hard)

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  
    // start : Index from which we have to solve the problem in this recursive call
    bool wordBreakHelper(string s,  unordered_map<string, int> dictMap, int start,  vector<int>& memo) {
        int n = s.length();
        
        // We have reached the end
        if (start == n){
            return true;
        }
        
        // If the start of the substring s[start..n] is known already, return that.
        if (memo[start]!= -1)
            return memo[start];
        
        // for each end = start+1 .. n, 
        //   if my dictionary contains s[start..end] and s[end..n] can also be solved, return true
        for(int end=start+1;end<=n;end++){
            if (dictMap.find(s.substr(start,end-start)) != dictMap.end()  && wordBreakHelper(s, dictMap, end, memo)){
                memo[start] = 1;
                return true;
            }
        }
      
        // for all values of end = start+1 .. n, I couldn't segment 's' into dictionary words.
        memo[start] = 0;
        return false;
    }
  
    bool wordBreak(string s, vector<string>& wordDict) {
      
        // "abcde" -> "a" | "bcde"   - "bcde" further solves "b", "cde" which solves "c" and "de"
        //            "ab" | "cde"   - "cde" to be solved again??
        //            "abc" | "de"   - This happens again for "de" - 3 times now.
        // DP table to store results of subroblems and not solve them > 1 time.
        // -1 = unknown
        //  0 = s[start..end] CAN NOT be segmented into dictionary words
        //  1 = s[start..end] CAN be segmented into dictionary words
        vector<int> memo(s.size(), -1);
        
        // Map to store the dictionary for faster retrieval of "My dict contains this?"
        unordered_map<string, int> dictMap;
        for (int i = 0; i < wordDict.size(); ++i){
            dictMap[wordDict[i]] = true;
        }
        
        return wordBreakHelper(s, dictMap, 0, memo);
    }
};


int main(){
    Solution s;
    string s1 = "Iamhere";
    string s2 = "heishere";
    vector<string> wordDict = {"I", "a", "he", "am", "her", "here"};
    cout<< s.wordBreak(s1, wordDict)<<endl;
    cout<< s.wordBreak(s2, wordDict)<<endl;
}

// "abcde" , dict: ["a", "abc", "e", "de"]
// WITHOUT MEMOIZATION
// -------------------
// "abcde"
//    "a" | "bcde"
//          "bcde" (false)
//                 "b" | "cde"
//                       "cde" (false)
//                              "c" | "de"
//                                    "de" (true)
//                                         "d" | "e"
//                                               "e" (true)
//                                         "de" (true)
//                              "cd"| "e"
//                                    "e" (true)
//                              "cde" (false)
//                 "bc"| "de"
//                       "de"
//                            "d" | "e" (true)
//                                  "e" (true)
//                            "de" (true)
//                 "bcd"|"e"
//                       "e" (true)
//                 "bcde" (false)
//    "ab" | "cde"
//           "cde"
//                  "c" | "de"
//                        "de"
//                             "d" | "e"
//                                   "e" (true)
//                             "de" (true)
//                  "cd"| "e"
//                        "e" (true)
//                  "cde" (false)
//    "abc" | "de"                        => This will return TRUE ans
//            "de" (true)
//                 "d" | "e" (true)
//                       "e" (true)
//                 "de" (true)
//    "abcd"| "e"
//            "e" (true)
//    "abcde" (false)


// WITH MEMOIZATION
// ----------------
// "abcde"
//    "a" | "bcde"
//          "bcde" (false)
//                 "b" | "cde"
//                       "cde" (false)
//                              "c" | "de"
//                                    "de" (true)
//                                         "d" | "e"
//                                               "e" (true)
//                                         "de" (true)
//                              "cd"| "e" (true)
//                              "cde" (false)
//                 "bc"| "de" (true)
//                 "bcd"|"e" (true)
//                 "bcde" (false)
//    "ab" | "cde" (false)
//    "abc" | "de" (true)      => This will return TRUE ans
//    "abcd"| "e" (true)
//    "abcde" (false)