
/*

Harshit Gupta | 4th May, 2021
---------------------------------

C++ program for "Word Ladder - Transform word from beginWord to endWord
	using a dictionary where every adjacent word differ by one letter in shortest possible way"

Read full problem here: https://leetcode.com/problems/word-ladder/
------
Solution: We can use BFS to solve this problem.
	1. Add the beginWord to the queue.
	2. Try to change all letters of the word (one at a time) and check if that changed word is present
		in the dict.
	3. If it is present, then this word differs by 1 letter and is present in the dict.
		Add it in the queue.
	4. Till we find the endWord, keep popping the words and do the same steps(2,3) with them.
	5. Since it is BFS, it will give you the shortest way to arrive from beignWord to endWord.

Time Complexity: 
Space Complexity: =
---
  NOTE: 

*/

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
    	// Hash to access the wordList vector in O(1) time instead of searching vector in O(n)
        unordered_set<string> dict(wordList.begin(), wordList.end());

        queue<string> todo;
        todo.push(beginWord);
        // Variable to calculate the shortest distance from beginWord to endWord
        int ladder = 1;
        
        while(!todo.empty()){
            int n = todo.size();
            
            // For the "size" number of elements in the queue..
            for(int i=0; i<n; i++){
            	// Get the front word
                string word = todo.front();
                todo.pop();
                // If it is the end word, then return the shortest distance variable
                if(word == endWord){
                    return ladder;
                }
                
                // Erase the word from dict since it has been accessed (Not really needed but good practice to shorten the map as we move)
                dict.erase(word);

                // For all the letters of the word
                for(int j=0;j<word.size(); j++){
                	// Get the j'th character
                    char c = word[j];
                    // Replace this character with all the 26 letters
                    for(int k=0; k<26; k++){
                        word[j] = 'a' + k;
                        // If this modified word exists in the dictionary, then we push it.
                        if (dict.find(word) != dict.end()){
                            // cout<<"Pushing: "<<word<<endl;
                            todo.push(word);
                        }
                    }
                    // Get the original jth letter in place so that we can start replcing the j+1 th letter.
                    word[j] = c;
                }
            }
            // Increase the distance since all possible words from this level are done.
            // All possible word for next level of processing are added to queue.
            ladder++;
        }
        return 0;
    }
};