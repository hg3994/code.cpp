
/*

Harshit Gupta | 4th May, 2021
---------------------------------

C++ program for "Word Ladder - Transform word from beginWord to endWord
	using a dictionary where every adjacent word differ by one letter in shortest possible way"

Read full problem here: https://leetcode.com/problems/word-ladder/

Example 1:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]
    Output: 5
    Explanation: One shortest transformation sequence is "hit" -> "hot" -> "dot" -> "dog" -> cog", 
        which is 5 words long.

Example 2:
    Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log"]
    Output: 0
    Explanation: The endWord "cog" is not in wordList, therefore there is no valid transformation sequence.

------
Solution: We can use BFS to solve this problem.
	1. Add the beginWord to the queue.
	2. Try to change all letters of the word (one at a time) and check if that changed word is present
		in the dict.
	3. If it is present, then this word differs by 1 letter and is present in the dict.
		Add it in the queue.
	4. Till we find the endWord, keep popping the words and do the same steps(2,3) with them.
	5. Since it is BFS, it will give you the shortest way to arrive from beginWord to endWord.

Time Complexity: O(M2×N), where M is the length of each word and N is the total number of words in the input word list.
    
    - For each word in the word list, we iterate over its length to find all the intermediate words corresponding 
    to it. Since the length of each word is M and we have N words, the total number of iterations the algorithm 
    takes to create all_combo_dict is M×N. Additionally, forming each of the intermediate word takes O(M) time 
    because of the substring operation used to create the new string. This adds up to a complexity of 
    O(M*M*N)

    - Breadth first search in the worst case might go to each of the NN words. For each word, we need to 
    examine M possible intermediate words/combinations. Notice, we have used the substring operation to 
    find each of the combination. Thus, M combinations take O(M*M) time. As a result, the time complexity 
    of BFS traversal would also be O(M*M*N)

    Combining the above steps, the overall time complexity of this approach is O(M*M*N)


Space Complexity: O(M2*N)
    - Each word in the word list would have MM intermediate combinations. To create the all_combo_dict dictionary 
    we save an intermediate word as the key and its corresponding original words as the value. Note, for each of 
    M intermediate words we save the original word of length M. This simply means, for every word we would need 
    a space of M*M to save all the transformations corresponding to it. Thus, all_combo_dict would need a 
    total space of O(M*M*N).
    - Visited dictionary would need a space of O(M*N) as each word is of length M.
    - Queue for BFS in worst case would need a space for all O(N) words and this would also result in a 
        space complexity of O(M×N).

---

Input: beginWord = "hit", endWord = "cog", wordList = ["hot","dot","dog","lot","log","cog"]

q: [hit], ladder: 1
q: [hot], ladder: 2
q: [dot, lot], ladder: 3
q: [lot,| dog], ladder: 3 (Notice that ladder only changes when all elements of that level are done)
q: [dog, log], ladder: 4
q: [log,| cog], ladder: 4
q: [cog], ladder: 5

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
                
                // Erase the word from dict since it has been accessed 
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