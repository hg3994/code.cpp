
/*

Harshit Gupta | 16th August, 2021
---------------------------------

Problem Statement:
Given an array of characters chars, compress it using the following algorithm:

Begin with an empty string s. For each group of consecutive repeating characters in chars:

If the group's length is 1, append the character to s.
Otherwise, append the character followed by the group's length.
The compressed string s should not be returned separately, but instead be stored in the input character array chars. Note that group lengths that are 10 or longer will be split into multiple characters in chars.

After you are done modifying the input array, return the new length of the array.

You must write an algorithm that uses only constant extra space.
 

Example 1:
    Input: chars = ["a","a","b","b","c","c","c"]
    Output: Return 6, and the first 6 characters of the input array should be: ["a","2","b","2","c","3"]
    Explanation: The groups are "aa", "bb", and "ccc". This compresses to "a2b2c3".

Example 2:
    Input: chars = ["a"]
    Output: Return 1, and the first character of the input array should be: ["a"]
    Explanation: The only group is "a", which remains uncompressed since it's a single character.

Example 3:
    Input: chars = ["a","b","b","b","b","b","b","b","b","b","b","b","b"]
    Output: Return 4, and the first 4 characters of the input array should be: ["a","b","1","2"].
    Explanation: The groups are "a" and "bbbbbbbbbbbb". This compresses to "ab12".

Example 4:
    Input: chars = ["a","a","a","b","b","a","a"]
    Output: Return 6, and the first 6 characters of the input array should be: ["a","3","b","2","a","2"].
    Explanation: The groups are "aaa", "bb", and "aa". This compresses to "a3b2a2". Note that each group is independent even if two groups have the same character.


https://leetcode.com/problems/string-compression/
------

Solution: 

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


class Solution {
public:
    int compress(vector<char>& chars) {
    if(chars.size() < 2){
        return chars.size();
    }
    // i is a pointer which will keep updating the chars array
    // j is a pointer which will keep going ahead and keep matching its prev element to see if there is a change
    // count will keep counting the difference between j and the last different character
    int i=0;
    for(int j = 1, count = 1; j <= chars.size(); j++, count++) {
        // if j reached the end or is different from the last character
        //      we copy the character of j-1 to i and move i ahead to write its frequency
        //      if the count is more or equal to two, we count the number of digits in the count variable and update the array with the number in each index with help of 'i'
        // Reset count variable so that we can start again from j index and ahead ... till we reach the end.
		if(j == chars.size() || chars[j] != chars[j - 1]) {
			chars[i] = chars[j - 1];  
            i++;
			if(count >= 2) {
				for(char digit : to_string(count)) {
					chars[i] = digit;
                    i++;
                }
            }
			count = 0;
		}
	}
	return i;
    }
};