
/*

Harshit Gupta | 18th August, 2021
---------------------------------

Problem Statement:
    Given two strings word1 and word2, return the minimum number of operations required to 
        convert word1 to word2.

You have the following three operations permitted on a word:
    Insert a character
    Delete a character
    Replace a character
 

Example 1:
    Input: word1 = "horse", word2 = "ros"
    Output: 3
    Explanation: 
    horse -> rorse (replace 'h' with 'r')
    rorse -> rose (remove 'r')
    rose -> ros (remove 'e')

Example 2:
    Input: word1 = "intention", word2 = "execution"
    Output: 5
    Explanation: 
    intention -> inention (remove 't')
    inention -> enention (replace 'i' with 'e')
    enention -> exention (replace 'n' with 'x')
    exention -> exection (replace 'n' with 'c')
    exection -> execution (insert 'u')
    
https://leetcode.com/problems/edit-distance/
------

Solution: DP
    1. We create a DP[][] array which means dp[i][j] = number of edits needed for word1 till 
        ith index to convert word2 till jth index.
    2. If word1[i] == word2[j], it means that we these letters are equal and we need no additional
        edit distance to be added. It is the same edit distance of dp[i-1][j-1]
    3. If word1[i] != word2[j], it means that they are not same, so have to 
        - delete the char from word1
        - insert into word2 or       
        - replace word2[j] with word1[i]
        - dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
        - 1 is added since we need 1 more edit distance on even if we select min of these three.


    TC: O(nm)
    SC: O(nm)

Paradigm: DP
---
    NOTE: 
        1. Check Tushar Roy video on this Topic, it is amazing!
        2. The edit distance algorithm is very popular among the data scientists. It's one of the basic 
            algorithms used for evaluation of machine translation and speech recognition.
            
    Similar Questions:
        1.

*/


// Converting horse -> ros
//        h o r s e
//      0 1 2 3 4 5 
// r    1 1 2 2 3 4 
// o    2 2 1 2 3 4 
// s    3 3 2 2 2 3 

class Solution {
public:
    int minDistance(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();
        
        vector<vector<int>> dp(m+1, vector<int>(n+1));
        
        for(int i=0; i<m+1; i++)
            dp[i][0] = i;
        
        for(int i=0; i<n+1; i++)
            dp[0][i] = i;
        
        for(int i=1; i<m+1; i++){
            for(int j=1; j<n+1; j++){
                if(word2[i-1] == word1[j-1])
                    dp[i][j] = dp[i-1][j-1];
                else
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1]))+1;
            }
        }
        
        return dp[m][n];
    }
};