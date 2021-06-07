
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for 

In an alien language, surprisingly they also use english lowercase letters, but possibly in a different order. 
    The order of the alphabet is some permutation of lowercase letters.
Given a sequence of words written in the alien language, and the order of the alphabet, return true if and 
    only if the given words are sorted lexicographicaly in this alien language.

https://leetcode.com/problems/verifying-an-alien-dictionary/

Example 1:
    Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
    Output: true
    Explanation: As 'h' comes before 'l' in this language, then the sequence is sorted.

Example 2:
    Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
    Output: false
    Explanation: As 'd' comes after 'l' in this language, then words[0] > words[1], hence the sequence is unsorted.

Example 3:
    Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
    Output: false
    Explanation: The first three characters "app" match, and the second string is shorter (in size.) According to lexicographical rules "apple" > "app", because 'l' > '∅', where '∅' is defined as the blank character which is less than any other character (More info).

------

Solution: 
    - We basically convert the new aplhabets order to 1-27
    - Then we iterate over adjacent words and then keep checking them letter by letter
    - If any two words are not lexographically sorted, return false. Else true.


Time Complexity: O(M).
    Storing the letter-order relation of each letter takes O(N) time. 
    For the nested for-loops, we examine each pair of words in the outer-loop and for the inner loop, 
    we check each letter in the current word. Therefore, we will iterate over all of letters in words.
    Taking both into consideration, the time complexity is O(M + N). 
        However, we know that NN is fixed as 2626. Therefore, the time complexity is O(M)O(M).

Space Complexity: O(1)

Paradigm:HashMap

---
  NOTE: 

*/



class Solution {
public:
    
    bool checkLexographic(string a, string b, unordered_map<int, int> map){
        int i=0, j=0;
        while(i!=a.size() && j!=b.size() && a[i]==b[j]){
            i++; j++;
        }
        
        if( (i== a.size()) || (i!=a.size() && j!=b.size() && map[a[i]] < map[b[j]]) ){
            return true;
        }
        else{
            return false;
        }
    }
    
    bool isAlienSorted(vector<string>& words, string order) {
        unordered_map<int, int> map;
        for(int i=0; i<order.size(); i++){
            map[order[i]] = i+1;
        }
        
        for(int i=0;i<words.size()-1; i++){
            if(!checkLexographic(words[i], words[i+1], map))
                return false;
        }
        return true;
    }
};