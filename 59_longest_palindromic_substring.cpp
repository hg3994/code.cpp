/*

Harshit Gupta | 23rd September, 2020
-------------------------------------

Ruby program for "Given a string s, find the longest palindromic substring/Subarray in s."
https://leetcode.com/problems/longest-palindromic-substring/

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
------

Solution: 

  We iterate from 0 to length of the string and at each index, 
  We get the longest palindromic substring considering the element(s) at that index to be at the middle.
  We call the expand_from_middle twice on i,i and i, i+1 because their may exist
    - a palindrome of odd length where one letter is in middle
    - a palindrome of even length where two letters(i, i+1) are in middle

  expand_from_middle just keeps matching the elements in its extreme 
  and keep expanding it to get a larger substring

Time Complexity: O(n2)
Space Complexity: O(1)

    Similar Questions:
        1. https://leetcode.com/problems/longest-palindromic-subsequence/
            - Here we are asked the "length" of the longest palindromic subsequence (not the subsequence itself)
            - Approach 1: Check if the chars are same or not and apply dp
            - Approach 2: Reverse s. LCP will be LCS of s and reverse s.
*/

class Solution {
public:
    string longestPalindrome(string s) {
        if(s.size()<= 1)
            return s;
        int i = 0;
        string lps = "";
        while(i<s.size()){
            string s1 = expandFromMiddle(s, i, i);
            string s2 = expandFromMiddle(s, i, i+1);
            
            string str = s1.size() > s2.size() ? s1 : s2;
            if(str.size() > lps.size())
                lps = str;
            
            i++;
        }
        return lps;
    }
    
    string expandFromMiddle(string s, int left, int right){
        while(left>=0 && right<s.size() && s[left]==s[right]){
            left--;
            right++;
        }
        return s.substr(left+1, right-left-1); // right-1-(left+1) +1
    }
    
};


// ------------------------------
// LONGEST PALIDROMIC SUBSEQUENCE
// ------------------------------
// Approach 1:

//   b b a b
// b 1 0 0 0 
// b 2 1 0 0 
// a 2 1 1 0 
// b 3 3 1 1 

//   b b b b
// b 1 0 0 0 
// b 2 1 0 0 
// b 3 2 1 0 
// b 4 3 2 1       

// We use only half of the 2D DP matrix
class Solution {
public:
    int longestPalindromeSubseq(string s) {
        int n = s.size();
        // dp[i][j]: the longest palindromic subsequence's length of 
        // substring(i, j), here i, j represent left, right indexes in the string
        vector<vector<int>> dp(n, vector<int>(n));
        
        for(int i=0; i<n; i++){
            dp[i][i] = 1;
            for(int j=i-1; j>=0; j--){
                if(s[i] == s[j]){
                    dp[i][j] = 2 + dp[i-1][j+1];
                }
                else{
                    dp[i][j] = max(dp[i-1][j], dp[i][j+1]);
                }
            }
        }
        
        return dp[n-1][0];
    }
};

// Approach 2: Longest Common Palindromic Subsequence will be Longest Common Subsequence of s and reverse s.
class Solution {
public:
    int LCS(string s, string t){
        int n = s.size();
        vector<vector<int>> dp(n+1, vector<int>(n+1));
        
        for(int i=0; i<n+1; i++){
            for(int j=0; j<n+1; j++){
                if(i == 0 || j==0)
                    dp[i][j] = 0;
                else if(s[i-1] == t[j-1])
                    dp[i][j] = 1+dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        return dp[n][n];
    }
    
    int longestPalindromeSubseq(string s) {
        if(s.size() <= 1)
            return s.size();
        string t = s;
        reverse(t.begin(), t.end());
        
        return LCS(s, t);
    }
};
