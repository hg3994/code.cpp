
/*

Harshit Gupta | 13th June, 2021
---------------------------------

C++ program for "Text Justification"
https://leetcode.com/problems/text-justification/
https://www.youtube.com/watch?v=GqXlEbFVTXY&ab_channel=MichaelMuinos

Example 1:
    Input: words = ["This", "is", "an", "example", "of", "text", "justification."], maxWidth = 16
    Output:
    [
       "This    is    an",
       "example  of text",
       "justification.  "
    ]

Example 2:
    Input: words = ["What","must","be","acknowledgment","shall","be"], maxWidth = 16
    Output:
    [
      "What   must   be",
      "acknowledgment  ",
      "shall be        "
    ]

Example 3:
    Input: words = ["Science","is","what","we","understand","well","enough","to","explain","to","a",
                    "computer.","Art","is","everything","else","we","do"], maxWidth = 20
    Output:
    [
      "Science  is  what we",
      "understand      well",
      "enough to explain to",
      "a  computer.  Art is",
      "everything  else  we",
      "do                  "
    ]

------

Solution: 
          1. We take two pointers i and j where we will start from words[i] and keep on adding words[j] to the line.
          2. If there is just 1 word OR it is the last line we are dealing with(j==n), then we left justify, otherwise middle justify
          3. LeftJustify:
                - In case of only 1 word, we just need to add all spaces to right
                - In case of last line, we need to add 1 space between the words and remaining all spaces on the right
          4. Middle Justify:
                - Keep adding spaces in between the words distributing equally
                - If there are extra spaces, then we give them to the left space group first and go on to the right

        TC: O(lines*maxWidth)
        SC: O(lines*maxWidth) to store the result

Paradigm: String
---
  NOTE: 

*/

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> result;
        int i=0, n = words.size();
        // starting with two pointer i and j where we will start from words[i] and keep on adding words[j]
        // After adding words[j] and 1 space between each set of words and lineLength, if it still is less than maxWidth
        // then keep growing the lineLength and increase j to add more words ...
        while(i<n){
            int j = i+1;
            int lineLength = words[i].size(); // this contains the len of words only without the spaces.
            
            // till the list is not exhaused && line length already + len of new word[j] and 1 space for set of words in btw.
            // j-i is number of words , j-i-1 is the number of spaces required in between those words
            while (j<n && (lineLength+words[j].size()+(j-i-1) < maxWidth)) {
                lineLength += words[j].size();
                j++;
            }
            
            // After we are done adding max words to the line, we try to left/middle justify them and add it in result
            int diff = maxWidth - lineLength; // also total number of spaces required in the line
            int numberOfWords = j-i;
            // if there is just 1 word or it is the last line we are dealing with(j==n), then we left justify, otherwise middle justify
            if(numberOfWords == 1 || j>=n)
                result.push_back(leftJustify(words, diff, i, j));
            else
                result.push_back(middleJustify(words, diff, i, j));
            
            // after adding to the result, we move i to j and then do the same thing for the next line... till we reach the end
            i = j;
        }
        return result;
    }
    
    // In case of only 1 word, we just need to add all spaces to right
    // In case of last line, we need to add 1 space between the words and remaining all spaces on the right
    string leftJustify(vector<string> words, int diff, int i, int j){
        // diff : total number of spaces required in the line
        // j-i-1: number of spaces required in between the words..
        int spacesOnRight = diff-(j-i-1);
        string result = words[i];

        // Applying the spaces in between the words
        for(int k=i+1; k<j; k++){
            result = result + " " + words[k]; 
        }
        
        // Applying spaces on the right of the string.
        while(spacesOnRight--)
            result += " ";
        
        return result;
    }
    
    // In case of a line with >1 words and not the last line
    string middleJustify(vector<string> words, int diff, int i, int j){
        int spacesNeeded = j-i-1; // in between the words..
        int spaces = diff/spacesNeeded; // spaces in between the words
        int extraSpaces = diff%spacesNeeded; // spaces which will be fed extra starting from the left till they are remaining
        string result = words[i];
        for(int k=i+1; k<j; k++) {
            int spacesToApply = spaces + (extraSpaces-- > 0 ? 1: 0); // adding up spaces and extraspaces (if needed)
            while(spacesToApply--)
                result = result + " ";
            result += words[k];
        }
        return result;
    }
};