
/*

Harshit Gupta | 24th July, 2021
---------------------------------

Problem Statement:

This is an interactive problem.
You are given an array of unique strings wordlist where wordlist[i] is 6 letters long, and one word in this list is 
    chosen as secret.
You may call Master.guess(word) to guess a word. The guessed word should have type string and must be from the original 
    list with 6 lowercase letters.
This function returns an integer type, representing the number of exact matches (value and position) of your guess to the 
secret word. Also, if your guess is not in the given wordlist, it will return -1 instead.

For each test case, you have exactly 10 guesses to guess the word. At the end of any number of calls, if you have made 10 or 
    fewer calls to Master.guess and at least one of these guesses was secret, then you pass the test case.


Example 1:
    Input: secret = "acckzz", wordlist = ["acckzz","ccbazz","eiowzz","abcczz"], numguesses = 10
    Output: You guessed the secret word correctly.
    Explanation:
        master.guess("aaaaaa") returns -1, because "aaaaaa" is not in wordlist.
        master.guess("acckzz") returns 6, because "acckzz" is secret and has all 6 matches.
        master.guess("ccbazz") returns 3, because "ccbazz" has 3 matches.
        master.guess("eiowzz") returns 2, because "eiowzz" has 2 matches.
        master.guess("abcczz") returns 4, because "abcczz" has 4 matches.
        We made 5 calls to master.guess and one of them was the secret, so we pass the test case.

Example 2:
    Input: secret = "hamada", wordlist = ["hamada","khaled"], numguesses = 10
    Output: You guessed the secret word correctly.

------

Solution: 



Approach 1: Randomly pick a word from the wordlist and pass it to the guess function
    Fails when the total words are >10
    
Approach 2: 
    1. Randomly pick a word from the wordlist
    2. Pass it to the guess function and get the number of matches from secret word => X
    3. Iterate over wordlist and eliminate all the words from the wordlist which does not have the same match dist => X
        - We know that the the match dist between this word and secret word is X so basically we are removing all 
            the words from the list which are 100% not the secret word (match dist other than X). 
        - We can find the distance between two words by checking how many letters are same in between them.
        - We have limited calls to the guess API but our own distance function is something which we can call N number of times.
        - Only keep words which are at match dist X from the chosen word. One of those is for sure the secret word.
        - This is done so that we remove the unwanted words and shorten our sample space so we find the secret word quicker.
    4. Now we have a smaller wordlist so repeat it again.
    
    => The probability of passing a random num into guess and getting 0 as match dist in he output is 80% here since it is highly unlikely 
        that there will be any matches between this random word and the secret word.
    => Obviously then, we will not be able to eliminate most of the words of wordlist (80%) since they will also be having 0 matches
        (Remember, we only remove the words which does NOT have the same match dist.)
    => We would only be able to remove 20% of the words from wordlist till an iteration comes which gives us a word which has 
        non-zero match with secret  and then we would be able to remove 80% of the words which will have 0 matches. 
    => And if that iteration comes up after 10 chances, we are gone. For very huge wordlist size, this may happen.

Approach 3 (MiniMax):
    1. Go through the wordlist and pick a pair of words which has the least number of 0 matches.
        - This means that the match distance between the chosen word and the secret word is highly unlikely to be 0.
        - This was the probability of passing that num and getting the output from guess funtion as non 0 (e.g. 1) becomes more.
    3. This way we eliminate 80% of the wordlist which has 0 matches and some other (in this e.g. matches 2,3,4,5,6 will also be removed 
        only 1 matches words will be there)
    4. Pass it to the guess function
    5. Iterate over wordlist and eliminate all the words from the wordlist which does not have the same match dist.
    6. Now we have a smaller wordlist so repeat it again.
    
    => This is the fastest way of decreasing the sample space and finding the secret word very quickly.

  
    What are the chances of 2 strings of length 6 would match each other completely?
    >> 1/26 for each letter and for 6 letters it becomes (1/26)^6

    What are the chances of 2 strings of length 6 would NOT match each other completely?
    >> 25/26 for each letter and (25/26)^6 for 6 letters.

    Why checking 0 match instead of 1,2,3...6 matches, please take a look at this comment. The probability of two words with 0 match is 
    (25/26)^6 = 80%. That is to say, for a candidate word, we have 80% chance to see 0 match with the secret word. In this case, we had 
    80% chance to eliminate the candidate word and its "family" words which have at least 1 match. Additionally, in order to delete a max part 
    of words, we select a candidate who has a big "family" (fewest 0 match with other words).

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.
*/


class Solution {
public:
    
    // This is the distance between two strings. The similarity value.
    // The return value means that these two strings have 'x' letters in common.
    int distance(string w1, string w2){
        int matched = 0;
        for(int i=0;i<w1.size(); i++){
            if(w1[i] == w2[i])
                matched++;
        }
        return matched;
    }
    
    void findSecretWord(vector<string>& wordlist, Master& master) {
        
        for(int i=0, match=0; i< 10 && match<6; i++){
            unordered_map<string, int> count; // count number of zero matches with other words
            
            for(auto w1: wordlist) {
                for(auto w2: wordlist){
                    if(distance(w1,w2) == 0)
                        count[w1]++;
                }   
            }
            // We are interested in the word which has least number of 0s.
            pair<string, int>minimum = {wordlist[0], INT_MAX};
            for(auto w: wordlist){
                if(count[w] <= minimum.second){
                    minimum = {w, count[w]};
                }
            }

            int mastermatch = master.guess(minimum.first);
            
            vector<string> candidates = {};
            
            // Now we want to remove all the words from wordlist which doesn't have the same match distance 
            // that the minimum word has with the secret word.
            // Hence, we only keep the words that has the same matchdistance with 'minimum' as secret word
            for(string w: wordlist){
                if(distance(w, minimum.first) == mastermatch){
                    candidates.push_back(w);
                }
            }
            wordlist = candidates;
        }
        
    }
};


/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */