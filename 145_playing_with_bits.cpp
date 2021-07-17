
/*

Harshit Gupta | 16th July, 2021
---------------------------------

Problem Statement:

1. https://leetcode.com/problems/power-of-two/submissions/
	- Check if a number is a pow of 2
	- O(1)

2. https://leetcode.com/problems/number-of-1-bits/
	- Count Number of Set bits in a number
	- This is also called as Hamming Weight

------

Solution: 

  TC: 
  SC:

Paradigm:
---
  NOTE: 

*/


// -------------------------------
// Check if a number is a pow of 2
// -------------------------------

// Approach 1: Number of bits in n is 1 if n is a pow of 2
//      Number of bits in n-1 is all except for that 1 if n is a pow of 2
//      n & n-1 should have 0 bits set
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0)
            return false;
        else
            return (n&(n-1)) == 0;
    }
};


// Approach 2: Log2 of N is a whole number if n is a pow of 2 so the ceil and floor should return the same value
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if(n <= 0)
            return false;
        else
            return (ceil(log2(n)) == floor(log2(n)));
    }
};


// -------------------------------
// Counting the number of set bits
// -------------------------------
class Solution {
public:
    int hammingWeight(uint32_t n) {
        unsigned int count = 0;
        while(n){
            count += n&1;
            n = n>>1;
        }
        return count;
    }
};