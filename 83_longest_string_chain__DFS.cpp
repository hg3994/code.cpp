
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

1. Initialize a map (wordsPresent) and add all the words in the list to the map. 
	This map will be used to check if a word is present in the listin O(1) time.
2. Initialize a map (memo) having key type as String and value type as Integer. 
	This map will store the length of the longest possible word sequence 
	"where the key is the last word in the sequence".
3. Iterate over the list. For each word in the list perform a depth-first search.
4. In the DFS, consider the current word (currentWord) as the last word in the word sequence.
5. If currentWord was encountered previously we just return its corresponding value in the map memo.
6. Initialize maxLength to 1.

7. Iterate over the entire length of the currentWord.
	- Create all possible words (newWord) by taking out one character at a time.
	- If newWord is present in the map perform a DFS with this word 
		and store the intermediate result in a variable currentLength.
	- Update the maxLength so that it contains the length of the longest sequence 
		possible where the currentWord is the end word.

8. Set the maxLength as the value for currentWord (key) in the map.
9. Return maxLength.

#DFS

Let N be the number of words in the list and L be the maximum possible length of a word.

Time Complexity: O(L2*N). Initially, we iterate over the list to store all the given words in a set (adds N to the 
    complexity). Next, we perform a DFS for each word O(N). For each word, we iterate over its lengthO(L). At each 
    index (i) we create a new word by deleting the character at position i from the original word O(L). Therefore, 
    the overall time complexity is O(N + L2.N) because the N term is insignificant relative to the L2*N term. 
    Note that because of memoization we can be sure that each word in the list is traversed only once.

Space Complexity: O(N). The extra space is used by the recursion call stack. In worst case all the words are a part 
    of the longest word sequence which requires a recursion stack size of N. Also, we use a set to store all 
    distinct words (size N) and a map to store intermediate results (size N). Since the maximum number of distinct 
    words will be NN (when there is no repetition) the overall space complexity is O(2⋅N).
---
  NOTE: 

*/

// ["a","b","ba","bca","bda","bdca"]
// word: "a",       maxLength = 1, memo { "a" -> 1}
// word: "b",       maxLength = 1, memo { "a" -> 1, "b" -> 1}
// word: "ba",      maxLength = 2, memo { "a" -> 1, "b" -> 1, "ba"-> 2}
// word: "bca",     maxLength = 3, memo { "a" -> 1, "b" -> 1, "ba"-> 2, "bca" -> 3}
// word: "bda",     maxLength = 3, memo { "a" -> 1, "b" -> 1, "ba"-> 2, "bca" -> 3, "bda" -> 3}
// word: "bdca",    maxLength = 4, memo { "a" -> 1, "b" -> 1, "ba"-> 2, "bca" -> 3, "bda" -> 3, "bdca" -> 4}

// dfs: a
//   memo: 
// dfs: b
//   memo: a -> 1 
// dfs: ba
//   memo: b -> 1 a -> 1 
// dfs: a
//   memo: b -> 1 a -> 1 
// dfs: b
//   memo: b -> 1 a -> 1 
// dfs: bca
//   memo: b -> 1 ba -> 2 a -> 1 
// dfs: ba
//   memo: b -> 1 ba -> 2 a -> 1 
// dfs: bda
//   memo: bca -> 3 b -> 1 ba -> 2 a -> 1 
// dfs: ba
//   memo: bca -> 3 b -> 1 ba -> 2 a -> 1 
// dfs: bdca
//   memo: bda -> 3 bca -> 3 b -> 1 ba -> 2 a -> 1 
// dfs: bca
//   memo: bda -> 3 bca -> 3 b -> 1 ba -> 2 a -> 1 
// dfs: bda
//   memo: bda -> 3 bca -> 3 b -> 1 ba -> 2 a -> 1 

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
        
        // Map to access the words present in O(1) time.
        unordered_map<string, bool> wordsPresent;
        // Map to store the word -> maxLength with this word
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
