
/*

Harshit Gupta | 7th August, 2021
---------------------------------

Problem Statement: Palindrome Partition
	Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

Example 1:
	Input: s = "aab"
	Output: [["a","a","b"],["aa","b"]]

Example 2:
	Input: s = "a"
	Output: [["a"]]

------

Solution: 1. Backtracking.

Time Complexity : O(N⋅2^N), where N is the length of string s. This is the worst-case time 
	complexity when all the possible substrings are palindrome.

	For each character in the string we have 2 choices to create new palindrom substrings, 
	one is to join with previous substring (for(...end++)) and another is to start a new 
	palindrom substring (dfs(..end+1..)). Thus in the worst case there are 2^N palindrom 
	substrings. Each substring will take O(N) time to check if it's palindrom and O(N) time 
	to generate substring from start to end indexes.
		In total we have O(2^N * (N + N)) = O(2^N * 2N) = O(N*2^N)

Space Complexity: O(N), where N is the length of the string s. This space will be used to 
	store the recursion stack.


Paradigm:
---
    NOTE: 
        1. This is very similar to the Permutation Question.

    Similar Questions:
        1. https://leetcode.com/problems/palindrome-partitioning-ii/
	    	- Given a string s, partition s such that every substring of the partition is a palindrome.
	    		Return the minimum cuts needed for a palindrome partitioning of s.
			- 	Input: s = "aab"
				Output: 1
				Explanation: The palindrome partitioning ["aa","b"] could be produced using 1 cut.

        2. https://leetcode.com/problems/palindrome-partitioning-iii/
        	- TODO
        3. https://leetcode.com/problems/palindrome-partitioning-iv/
        	- TODO


*/

// isPalin: a
// isPalin: a
// isPalin: b -> start reaches the s.size(), so put it in result.
// isPalin: ab
// isPalin: aa
// isPalin: b -> start reaches the s.size(), so put it in result.
// isPalin: aab
class Solution {
public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        vector<string> currentList;
        dfs(result, s, 0, currentList);
        return result;
    }
    
    void dfs(vector<vector<string>>& result, string& s, int start, vector<string>& currentList){
        
        if(start >= s.size())
            result.push_back(currentList);
        
        for(int end=start; end<s.size(); end++){
            if(isPalindrome(s, start, end)){
                currentList.push_back(s.substr(start, end-start+1));
                dfs(result, s, end+1, currentList);
                currentList.pop_back();
            }
        }
    }
    
    bool isPalindrome(string& s, int low, int high){
        // cout<<"isPalin: "<<s.substr(low, high-low+1)<<endl;
        while(low < high){
            if(s[low] != s[high])
                return false;
            low++;
            high--;
        }
        return true;
    }  
};


// Approach 2: DP with Backtracking:
// The previous approach performs one extra iteration to determine if a given substring is a 
// palindrome or not. Here, we are repeatedly iterating over the same substring multiple times 
// and the result is always the same.
// The result of substring b for s = aab is calculated twice. For larger substrings, there would 
// be many such substrings for which the results would be unnecessarily computed again and again. 
// In fact, for every repeated computation the results would be always the same.

// We could further optimize the approach by using dynamic programming to determine if a 
// string is a palindrome in constant time
// A given string ss starting at index \text{start}start and ending at index end is a palindrome 
// 	if following conditions are satisfied :
// 		a. The characters at start and end indexes are equal.
// 		b. The substring starting at index start+1 and ending at index end−1 is a palindrome.

// Time Complexity : O(N⋅2^N), where N is the length of string s. In the worst case, there could be 
// 	2^N  possible substrings and it will take O(N) to generate each substring using substr as 
// 	in Approach 1. However, we are eliminating one additional iteration to check if substring 
// 	is a palindrome or not.

// Space COmplexity: O(n2) for the dp array

//   a a b
// a 1 1 0 
// a 0 1 0 
// b 0 0 1 

class Solution {
public:
    vector<vector<string>> partition(string s) {
        int len = s.length();
        vector<vector<bool>> dp (len, vector <bool> (len, false));
        
        vector<vector<string>> result;
        vector<string> currentList;
        dfs(result, s, 0, currentList, dp);
        // for(int i=0; i<len; i++){
        //     for(int j=0; j<len; j++){
        //         cout<<dp[i][j]<<" ";
        //     }
        //     cout<<endl;
        // }
        return result;
    }
    
    void dfs(vector<vector<string>>& result, string& s, int start, vector<string>& currentList, vector<vector<bool>> &dp){
        
        if(start >= s.size())
            result.push_back(currentList);
        
        for(int end=start; end<s.size(); end++){
            if(s[start] == s[end] && (end - start <= 2 || dp[start+1][end-1] == true)){
                dp[start][end] = true;
                currentList.push_back(s.substr(start, end-start+1));
                dfs(result, s, end+1, currentList, dp);
                currentList.pop_back();
            }
        }
    }
    
};


// ---------------------------------------------------------------
// SIMILAR QUESTION 1: MINIMUM CUTS FOR EACH PART TO BE PALINDROME
// ---------------------------------------------------------------

// Approach 1: Similar to the last question, when we have the list of all the palindromic substrings
//  we can select the one with the minimum length and that would be the substring with minimum number
//  of cuts.
// Eg: [aab]=> ['a', 'a', 'b'] & ['aa', 'b']. The min length is 2. So we can do 1 cut minimum and get 
//  both the parts as palindromes.

// GIVES TLE as the TC is O(N.2^N)
class Solution {
public:
    int minCut(string s) {
        return findMinimumCut(s, 0, s.length() - 1, s.length() - 1);
    }

    int findMinimumCut(string &s, int start, int end, int minimumCut) {
        // base condition, no cut needed for an empty substring or palindrome substring.
        if (start == end || isPalindrome(s, start, end)) {
            return 0;
        }
        for (int currentEndIndex = start; currentEndIndex <= end; currentEndIndex++) {
            // find result for substring (start, currentEnd) if it is palindrome
            if (isPalindrome(s, start, currentEndIndex)) {
                minimumCut = min( minimumCut, 1 + findMinimumCut(s, currentEndIndex + 1, end, minimumCut));
            }
        }
        return minimumCut;
    }

    bool isPalindrome(string &s, int start, int end) {
        while (start < end) {
            if (s[start++] != s[end--]) {
                return false;
            }
        }
        return true;
    }
};
// Approach 2: 
// To record the results of computation on every substring, we must store the substring and its result.
// Now, instead of storing the substring, we can just store its start and end index. We will use 
// a 2-dimensional array memoCuts, where the value of memoCuts[start][end] would give the minimum 
// number of cuts for a substring starting at index start and ending at index end.
// Similarly, we need another 2-dimensional array memoPalindrome to store the results for 
// palindrome computations.

// The implementation is the same as in Approach 1 with the following differences:
// 	1. In findMinimumCut, check if memoCuts has the result for the current substring. 
// 		If so, return the result, otherwise, proceed with the next steps to compute the result.
// 	2. After computing the result, store the result in memoCuts[start][end].
// 	3. A similar approach is followed in isPalindrome to store the results of palindrome computations

// Time Complexity: O(N^2⋅N), where N is the length of string s. In the recursive method findMinimumCut, 
// we are calculating the results for any substring only once. We know that a string size N has N^2 
// possible substrings. Thus, the worst-case time complexity of the recursive method findMinimumCut is 
// O(N^2).
// Additionally, within each recursive call, we are also checking if a substring is palindrome or not. 
// he worst-case time complexity for method isPalindrome is O(N/2).
// This gives us total time complexity as, O(N^2⋅N)

// Space Complexity: O(N ^ 2) for both the arrays used for dp.

class Solution {
public:
    vector<vector<int>> memoCuts;
    vector<vector<optional<bool>>> memoPalindrome;

    int minCut(string s) {
        memoCuts.resize(s.length(), vector<int>(s.length(), -1));
        memoPalindrome.resize(s.length(), vector<optional<bool>>(s.length(), nullopt));
        return findMinimumCut(s, 0, s.length() - 1, s.length() - 1);
    }

    int findMinimumCut(string &s, int start, int end, int minimumCut) {
        // base case
        if (start == end || isPalindrome(s, start, end)) {
            return 0;
        }

        // check for results in memoCuts
        if (memoCuts[start][end] != -1) {
            return memoCuts[start][end];
        }

        for (int currentEndIndex = start; currentEndIndex <= end; currentEndIndex++) {
            if (isPalindrome(s, start, currentEndIndex)) {
                minimumCut = min(minimumCut, 1 + findMinimumCut(s, currentEndIndex + 1, end, minimumCut));
            }
        }
        return memoCuts[start][end] = minimumCut;
    }

    bool isPalindrome(string &s, int start, int end) {
        if (start >= end) 
        	return true;

        // check for results in memoPalindrome
        if (memoPalindrome[start][end] != nullopt)
            return (memoPalindrome[start][end] == true);
        
        memoPalindrome[start][end] = (s[start] == s[end]) && isPalindrome(s, start + 1, end - 1);
        
        return (memoPalindrome[start][end] == true);
    }
};


// Approach 3: EXPAND AROUND CENTER WITH DP
// Time Complexity: O(N2)
// Outer Loop iterates N times while the 2 inner loops iterates N/2 times each. Finally, O(N*O(N/2+N/2)) = O(N2)
// Space Complexity: O(N) for dp array.

// We will fix every index in the string as a middle index and find the palindrome around that index.
// We will also take the advantage of pre-calculated results using the dynamic programming technique 
// 1. Build an array cutsDp to store the results of every computation. Initially, the value of cutsDp[i]
// 		would be the maximum possible number of cuts till index i, which is equivalent to i.
// 2. As we progress, after every computation of minimum cuts for a substring ending at index i, 
// 		the value of cutsDp[i] would be updated.
// 3. Start by fixing the middle index mid at every position beginning from index 0 till 
// 		the index length to string s. Expand around the center considering mid and mid-1 as center
// 4. As the expansion stops because s[start!=s[end], we will place a cut after the end index.
// 		Min cuts at end = MIN (Min cuts till now, Min cuts at (start-1)+1)

class Solution {
public:
    int minCut(string s) {
        vector<int> cutsDp(s.size());
        for(int i=0; i<s.size(); i++)
            cutsDp[i] = i;
        
        for(int mid=0; mid<s.size(); mid++){
            expandAroundCenter(mid, mid, cutsDp, s);
            expandAroundCenter(mid-1, mid, cutsDp, s);
        }
        return cutsDp[s.size()-1];
    }
    
    void expandAroundCenter(int startIndex, int endIndex, vector<int>& cutsDp, string s){
        for(int start=startIndex, end=endIndex; start>=0 && end<s.size() && s[start] == s[end]; start--, end++){
            int newCut = start == 0 ? 0 : cutsDp[start-1]+1;
            cutsDp[end] = min(cutsDp[end], newCut);
        }
    }
    
};
