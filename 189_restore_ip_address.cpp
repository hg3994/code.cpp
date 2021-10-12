/*

Harshit Gupta | 28th Sept, 2021
---------------------------------

Problem Statement: Restore IP Addresses

Given a string s containing only digits, return all possible valid IP addresses that 
	can be obtained from s. You can return them in any order.

A valid IP address consists of exactly four integers, each integer is between 
0 and 255, separated by single dots and cannot have leading zeros. 

For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and 
"0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses. 

Example 1:
	Input: s = "25525511135"
	Output: ["255.255.11.135","255.255.111.35"]

Example 2:
	Input: s = "0000"
	Output: ["0.0.0.0"]

Example 3:
	Input: s = "1111"
	Output: ["1.1.1.1"]

Example 4:
	Input: s = "010010"
	Output: ["0.10.0.10","0.100.1.0"]

https://leetcode.com/problems/restore-ip-addresses/
------

Solution: Backtracking. TODO understanding.

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


// Since no one talks about time complexity, here is my thoughts. What we are 
// trying to do here is to partition the input string into 4 parts with 3 cuts. 
// There are C(n, 3) ways to cut the string into 4 parts. In that sense, the time 
// complexity is O(n^3). On second thought, however, because we are doing backtracking 
// and removing lots of unnecessary checking, we are only checking three possibilities 
// for each part (it has to be [0,255]), it becomes 3^4, which is just a constant, 
// so it becomes O(1). This is why solution like this exists:
class Solution {
public:
    
    void generateIPAddresses(string ip, vector<string>& solutions, string restored, int idx, int count){
        int n = ip.size();
        // We can also use if(count > 4) but this condition would be faster.
        // We know that when input string's length is larger than 12, there will be no way to restore it.
        // We can check whether the left string's length is larger than (3 multiply left sections).
        if (n - idx > 3 * (4 - count)) // or just if (count > 4)
            return;

        if(count == 4 && idx == ip.size()){
            solutions.push_back(restored);   
            return;
        }

        for(int i=1; i<4; i++){
            if(idx+i > ip.size()) 
                break;
            string s = ip.substr(idx, i);
            if (s[0] == '0' && s.size()>1 || (i==3 && stoi(s)>=256 ))
                continue; 
            string dot = (count == 3)?"":".";
            string newRestored = restored+s+dot;
            generateIPAddresses(ip, solutions, newRestored, idx+i, count+1);
        }
    }
    
    vector<string> restoreIpAddresses(string s) {
        vector<string> solutions;
        generateIPAddresses(s, solutions, "", 0, 0);
        return solutions;
    }
};