
/*

Harshit Gupta | 14th May, 2021
---------------------------------

C++ program for "Number of Palindromic Substrings in a String"
https://leetcode.com/problems/palindromic-substrings/

	Input: s = "abc"
	Output: 3
	Explanation: Three palindromic strings: "a", "b", "c".

	Input: s = "aaa"
	Output: 6
	Explanation: Six palindromic strings: "a", "a", "a", "aa", "aa", "aaa".

------

Solution: 
	We iterate from 0 to length of the string and at each index, 
	We get the num of palindromic substring considering the element(s) at that index to be at the middle.
	We call the expand_from_middle twice on i,i and i, i+1 because their may exist
	- a palindrome of odd length where one letter is in middle
	- a palindrome of even length where two letters(i, i+1) are in middle

	expand_from_middle just keeps matching the elements in its extreme 
	and we keep on adding count of the number of palindromes we are getting

Time Complexity: O(n2)
Space Complexity: O(1)
---
  NOTE: This question and solution is very similar to the question 59_longest_palindromic_substring

*/

class Solution {
	// Return the number of palindromes we get keeping left and right in the middle and expanding
    int expand_from_middle (string s, int left, int right){
        int palin = 0;
        while(left>=0 && right < s.length() && s[left] == s[right]){
            palin++;
            left--;
            right++;
        }
        return palin;
    }

public:
    int countSubstrings(string s) {
        int n=s.size();
        int i=0;
        int num_of_palindromes = 0;
        // Iterate from starting index 0 till n
        while(i<n){
        	// Get num of odd lengthed palindromes keeping i in the middle
            int n1 = expand_from_middle(s, i, i);
            // Get num of even lengthed palindromes keeping i and i+1 in the middle
            int n2 = expand_from_middle(s, i, i+1);
            num_of_palindromes += n1+n2;
            i++;
        }
        return num_of_palindromes;
    }
};