
/*

Harshit Gupta | 18th June, 2021
---------------------------------

C++ program for "Strobogrammatic Number"

A strobogrammatic number is a number that looks the same when rotated 180 degrees (looked at upside down).

1. Given a string num which represents an integer, return true if num is a strobogrammatic number.
	https://leetcode.com/problems/strobogrammatic-number/

	Input: num = "69"
	Output: true
	Input: num = "88"
	Output: true

2. Given an integer n, return all the strobogrammatic numbers that are of length n. 
	You may return the answer in any order.
	https://leetcode.com/problems/strobogrammatic-number-ii/

	Input: n = 2
	Output: ["11","69","88","96"]
	Input: n = 1
	Output: ["0","1","8"]


------

Solution: 
	Q1:	
		1. Create the rotated String and if it matches the original string, return true.
		2. If at any point of time, we see a "non-strobogrammatic" number, return false.
		3. We save the rotated digits in a map
		4. Since we are saving it reverse fashion, we need not worry about 
			reversing the rotated string. It is already reversed.

	Q2:
		1. .....

TC: 
SC:

Paradigm:
---
  NOTE: 

*/

class Solution {
public:
    bool isStrobogrammatic(string nums) {
        string rotatedString="";
        unordered_map<char, char> map = {{'1','1'},{'0','0'},{'8','8'},{'6','9'},{'9','6'}};
        for(int i=0; i<nums.size(); i++){
            if(nums[i] == 2 || nums[i] == 3 || nums[i] == 4 || nums[i] == 5 || nums[i] == 7 )
                return false;
            rotatedString = map[nums[i]] + rotatedString;
        }
        if(rotatedString == nums)
            return true;
        else
            return false;
    }
};