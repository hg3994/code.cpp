
/*

Harshit Gupta | 17th May, 2021
---------------------------------

C++ program for "Longest String Chain"

https://leetcode.com/problems/longest-string-chain/

Given a list of words, each word consists of English lowercase letters.
Let's say word1 is a predecessor of word2 if and only if we can add exactly 
	one letter anywhere in word1 to make it equal to word2. For example, "abc" is a predecessor of "abac".
A word chain is a sequence of words [word_1, word_2, ..., word_k] with k >= 1, 
	where word_1 is a predecessor of word_2, word_2 is a predecessor of word_3, and so on.
Return the longest possible length of a word chain with words chosen from the given list of words.

Example 1:

Input: words = ["a","b","ba","bca","bda","bdca"]
Output: 4
Explanation: One of the longest word chain is "a","ba","bda","bdca".
Example 2:

Input: words = ["xbc","pcxbcf","xb","cxbc","pcxbc"]
Output: 5

------

Solution: https://leetcode.com/problems/longest-string-chain/solution/

1. Initialize a set (wordsPresent) and add all the words in the list to the set. 
	This set will be used to check if a word is present in the list.
2. Initialize a map (memo) having key type as String and value type as Integer. 
	This map will store the length of the longest possible word sequence 
	where the key is the last word in the sequence.
3. Iterate over the list. For each word in the list perform a depth-first search.
4. In the DFS, consider the current word (currentWord) as the last word in the word sequence.
5. If currentWord was encountered previously we just return its corresponding value in the map memo.
6. Initialize maxLength to 1.

7. Iterate over the entire length of the currentWord.
	- Create all possible words (newWord) by taking out one character at a time.
	- If newWord is present in the set perform a DFS with this word 
		and store the intermediate result in a variable currentLength.
	- Update the maxLength so that it contains the length of the longest sequence 
		possible where the currentWord is the end word.

8. Set the maxLength as the value for currentWord (key) in the map.
9. Return maxLength.

#DFS

Time Complexity: 
Space Complexity: 
---
  NOTE: 

*/

class Solution {
    
    int dfs(unordered_map<string, bool>& wordsPresent, unordered_map<string, int>& memo, string currentWord){
        // If the word is encountered previously we just return its value present in the map (memoization).
        if (memo.find(currentWord) != memo.end()){
            return memo[currentWord];
        }
        
        int n = currentWord.size();
        // This stores the maximum length of word sequence possible with the 'currentWord' 
        int maxLength=1;
        
        // creating all possible strings taking out one character at a time from the `currentWord`
        for(int i=0; i<n; i++) {
            string newWord = currentWord.substr(0, i) + currentWord.substr(i+1, n);
            
            // If the new word formed is present in the list, we do a dfs search with this newWord.
            if (wordsPresent.find(newWord) != wordsPresent.end()) {
                int len = dfs(wordsPresent, memo, newWord)+1;
                maxLength = max(len, maxLength);
            }
        }
        
        memo[currentWord] = maxLength;
        return maxLength;
    }
    
public:
    int longestStrChain(vector<string>& words) {
        
        unordered_map<string, bool> wordsPresent;
        unordered_map<string, int> memo;
        int ans = 0;
        
        for(auto i: words){
            wordsPresent[i] = true;
        }
        
        for(int i=0; i<words.size(); i++){
            ans = max(ans, dfs(wordsPresent, memo, words[i]));
        }
        return ans;
    }
};
