
/*

Harshit Gupta | 11th August, 2021
---------------------------------

Problem Statement:
A binary string is monotone increasing if it consists of some number of 0's (possibly none), followed by some number of 1's (also possibly none).
You are given a binary string s. You can flip s[i] changing it from 0 to 1 or from 1 to 0.
Return the minimum number of flips to make s monotone increasing.

Example 1:
    Input: s = "00110"
    Output: 1
    Explanation: We flip the last digit to get 00111.

Example 2:
    Input: s = "010110"
    Output: 2
    Explanation: We flip to get 011111, or alternatively 000111.

Example 3:
    Input: s = "00011000"
    Output: 2
    Explanation: We flip to get 00000000.
    
https://leetcode.com/problems/flip-string-to-monotone-increasing/
------

Solution: 1. Prefix Sum 

    arr[n]:  0, 1, 0, 1, 1, 0
    P[n+1]:  0, 0, 1, 1, 2, 3, 3
    Index:   0, 1, 2, 3, 4, 5, 6

    P[]: represents the number of 1s in the array till now.
    Index represents the number of 1s present till i

    We want to find the best "SWITCHING Index (0s->1s)" on which the number of flips (1->0) in first half
        and number of flips(0->1) in second half are minimum.

    Evidently, it comes down to a question of knowing, for each candidate half: how many ones 
    are in the left half, and how many zeros are in the right half.

    If that switching index = 0, then we have all 1s.
    If that switching index = n, then we have all 0s.
    If that switching index = 1...n-1, then we have 'index' 0s and 'N-index' 1s.

    Eg: Index=3, then there are TOTAL "Index" chars before it and "N-Index" chars after it.
    P[3]=1 means there are 1 1s before index 3 and P[6]-P[3]=2, 2 1s after index 3
    It means there are (N-index)-(P[6]-P[3])=1 FLIPS (1->0) to be done in the later N-x characters.
    It means there are P[index] FLIPS to be done in the first x characters.
    TOTAL FLIPS = P[index] + N-index-(P[N]-P[index])
    We can consider each index to be the switching index from 0s->1s and consider all possibilities

    TC: O(n)
    SC: O(n) for prefix array

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/



class Solution {
public:
    int minFlipsMonoIncr(string s) {
        int n= s.size();
        int ans=INT_MAX;
        vector<int> P(n+1, 0);
        for(int i=0; i<n; i++)
            P[i+1] = P[i]+(s[i]=='1' ? 1: 0);
        
        for(int i=0; i<=n; i++){
            // P[i] -> Flips (1->0) in the first half
            // n-i-(P[n]-P[i]) -> Flips (0->1) in second half
            ans = min(ans, P[i] + (n-i)-(P[n]-P[i]));
        }
        return ans;
    }
};