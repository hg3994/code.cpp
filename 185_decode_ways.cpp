
/*

Harshit Gupta | 18th August, 2021
---------------------------------

Problem Statement:
A message containing letters from A-Z can be encoded into numbers using the following mapping:
	'A' -> "1"
	'B' -> "2"
	...
	'Z' -> "26"
To decode an encoded message, all the digits must be grouped then mapped back into 
letters using the reverse of the mapping above (there may be multiple ways). 
For example, "11106" can be mapped into:
	"AAJF" with the grouping (1 1 10 6)
	"KJF" with the grouping (11 10 6)

Note that the grouping (1 11 06) is invalid because "06" cannot be mapped into 'F' 
since "6" is different from "06".

Given a string s containing only digits, return the number of ways to decode it.
The answer is guaranteed to fit in a 32-bit integer.


Example 1:
	Input: s = "12"
	Output: 2
	Explanation: "12" could be decoded as "AB" (1 2) or "L" (12).

Example 2:
	Input: s = "226"
	Output: 3
	Explanation: "226" could be decoded as "BZ" (2 26), "VF" (22 6), or "BBF" (2 2 6).

Example 3:
	Input: s = "0"
	Output: 0
	Explanation: There is no character that is mapped to a number starting with 0.
	The only valid mappings with 0 are 'J' -> "10" and 'T' -> "20", neither of which start with 0.
	Hence, there are no valid ways to decode this since all digits need to be mapped.

Example 4:
	Input: s = "06"
	Output: 0
	Explanation: "06" cannot be mapped to "F" because of the leading zero ("6" is 
		different from "06").

Example 5: 

        2125
        /   \
    'B'125   'U'25
       /\       /  \           
  'A'25 'L'5   'B'5 'Y'
    /  \    \    \ 
  'B'5  'Y'  'E'  'E'
    |
   'E'

Answers: [BABE, BAY, BLE, UBE, UY]            

https://leetcode.com/problems/decode-ways/
------

Solution: 

    TC: 
    SC:

Paradigm: DP
---
    NOTE: 

    Similar Questions:
        1. Climbing Staircase, Fibonacci
        2. https://leetcode.com/problems/decode-ways-ii/
        	- TODO

*/


/*
Approach 1: Recursive Solution
TC: O(n) (for each index, it is called only once), SC: O(n)
Runtime: 812ms, Mem: 357MB
*/
class Solution {
public:
    unordered_map<int, int> memo;
    
    int recurse(int index, string s){
        if(memo[index])
            return memo[index];
        if(index == s.size())
            return 1;
        if(s[index] == '0')
            return 0;
        if(index == s.size()-1)
            return 1;
        int ans = recurse(index+1, s);
        if(stoi(s.substr(index, 2)) <= 26)
            ans += recurse(index+2, s);
        memo[index] = ans;
        return ans;
    }
    
    int numDecodings(string s) {
        return recurse(0, s);
    }
};

/*
Appraoch : DP Solution

Assume dp[i] tells us the "number of ways to decode the string till s[i]"
If for example my s[i] is 2, then I know I can add 'B' to all previous encodings 
and still the answer would be the same as dp[i-1] (since we are cal the number of ways).
But.. we have to consider the number behind me as well, for example, 
s[i-1] was 1, then I have to consider 12->'L'. How to do that? So basically we want to
add 'L' to all the previous answers prior to THAT (dp[i-1]) which is dp[i-2] ways. 

So basically, 
dp[i] = dp[i-1]+dp[i-2] (if s[i] & s[i-1] forms a valid number from 10 to 25)
dp[i] = dp[i-1]         (if s[i] & s[i-1] forms DOES NOT form a valid number from 10 to 25)

s       = [  2 1 2 5]
dp[]    = [1 1 0 0 0]
dp[]    = [1 1 2 0 0]
dp[]    = [1 1 2 3 0]
dp[]    = [1 1 2 3 5]

NOTES:
------
1. An empty string should be considered for cases like "15" where dp[1] = dp[0]+ dp[-1] would go 
	wrong so dp[2] = dp[1]+dp[0] would represent "-15"
2. Zeroes must be handled. If s[i]==0, we will only check for 2 behind dp[i-2] since then we can 
	only make 10, 20 but 0 singularly doesnt map to any character
3. This looks so much like the Climbing Staircase Problem but with some extra 'ifs'
4. We can do more optimizations since we only look 2 behind and we dont need the whole dp array.

TC: O(n), SC: O(n)
Runtime: 0ms, Mem: 6MB
*/
class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0'){
            return 0;
        }
        int n = s.size();
        vector<int> dp(n+1);
        dp[0] = 1;
        dp[1] = 1;
        
        for(int i=1; i<n; i++){
            if(s[i] != '0'){
                dp[i+1] = dp[i];
            }
            if(stoi(s.substr(i-1, 2))>= 10 && stoi(s.substr(i-1, 2)) <= 26 ){
                dp[i+1] += dp[i-1];
            }
        }
        return dp[n];
    }
};