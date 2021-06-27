
/*

Harshit Gupta | 4th June, 2021
---------------------------------

C++ program for "Letter Combinations of a Phone Number"
	
	Given a string containing digits from 2-9 inclusive, return all possible letter combinations 
	that the number could represent. Return the answer in any order.
	A mapping of digit to letters (just like on the telephone buttons) is given below. 
	Note that 1 does not map to any letters.

https://leetcode.com/problems/letter-combinations-of-a-phone-number/

------

Solution: 
	Iterate over all the digits and get the string for that number.
	Take the current answer set and then multiply it with the set of characters 
		to get the new answer set

Time Complexity: O(4^N)
Space Complexity:

Paradigm:
---
  NOTE: 

*/


class Solution {
public:
    vector<string> letterCombinations(string digits) {
        int n = digits.size();
        unordered_map<char, string> map = {{'2',"abc"}, {'3', "def"}, {'4', "ghi"}, {'5', "jkl"}, {'6', "mno"}, {'7', "pqrs"}, {'8', "tuv"}, {'9',"wxyz"}};
        vector<string> ans;
        
        // For all the letters in the number "2345.."
        for(int i=0;i<n;i++){
            // Get the string from the map ..
            string letters = map[digits[i]];
            // If the ans vector is empty
            if(ans.empty()) {
                // Get all the characters and put it into the ans vector as a STRING(since we would be appending more there..) and NOT a char.
                for(int j=0;j<letters.size();j++){
                    string s; s += letters[j];
                    ans.push_back(s);
                }
            }
            // If ans already has some element
            else {
                // Iterate over all the letters into the string and then add all letters of ans into each one of them. 
                // new_ans would have (n*m) elements.
                vector<string> new_ans;
                for(int j=0;j<letters.size();j++)
                    for(int k=0;k<ans.size(); k++)
                        new_ans.push_back(ans[k]+letters[j]);
                
                // update the ans to new_ans which has all the latest elements ..
                ans = new_ans;
            }
        }
        return ans;
    }
};