
/*

Harshit Gupta | 30th July, 2021
---------------------------------

Problem Statement:

Given two integers a and b, return the sum of the two integers without using the operators + and -.

Example 1:
	Input: a = 1, b = 2
	Output: 3
Example 2:
	Input: a = 2, b = 3
	Output: 5
	 
------

Solution: First of all, there are too many use cases here: both aa and bb could be positive or negative, 
	abs(a) could be greater or less than abs(b). In total, that results = 2×2×2=8 use cases.
	Let's start by reducing the problem down to two simple cases:
		Sum of two positive integers: x + y, where x > y.
		Difference of two positive integers: x - y, where x > y.

Addition:

	XOR is a key as well because it's a sum of two integers in the binary form without taking carry into account. 
	In other words, XOR is a sum of bits of x and y where at least one of the bits is not set.

	The next step is to find the carry. It contains the common set bits of x and y, shifted one bit to the left. 
	i.e. it's logical AND of two input numbers, shifted one bit to the left: carry = (x & y) << 1
	
	Technically, it's the same problem: to sum two numbers, and hence one could solve it in a loop with the 
		condition statement "while carry is not equal to zero".

Substraction:

	XOR is a difference of two integers without taking borrow into account.
	The next step is to find the borrow. It contains common set bits of y and unset bits of x, 
	i.e. borrow = ((∼x)&y)<<1.

	The problem is reduced down to the subtraction of the borrow from the answer without borrow. As for the sum, 
	it could be solved recursively or in a loop with the condition statement "while borrow is not equal to zero".


    TC: O(1) because each integer contains 3232 bits.
    SC: O(1)

---

Solution: We know that

	log10(10^a) = a
	log10((10^a)*(10^b)) = a+b

	This is also right but log is a very expensive operation.

	
Paradigm: Bit Manipulation.

---
    NOTE: 
    	1. MUST READ FOR BIT MANIPULATION: https://leetcode.com/problems/sum-of-two-integers/discuss/84278/A-summary%3A-how-to-use-bit-manipulation-to-solve-problems-easily-and-efficiently
		2. A few Bi Maipulation Tricks:
			Set union A | B
			Set intersection A & B
			Set subtraction A & ~B
			Set negation ALL_BITS ^ A or ~A
			Set bit A |= 1 << bit
			Clear bit A &= ~(1 << bit)
			Test bit (A & 1 << bit) != 0
			Extract last bit A&-A or A&~(A-1) or x^(x&(x-1))
			Remove last bit A&(A-1)
			Get all 1-bits ~0
	
    Similar Questions: TODO
        1. https://leetcode.com/articles/single-number-ii/
        2. https://leetcode.com/articles/single-number-iii/
        3. https://leetcode.com/articles/maximum-xor-of-two-numbers-in-an-array/
        4. https://leetcode.com/articles/repeated-dna-sequences/
        5. https://leetcode.com/articles/maximum-product-of-word-lengths/

*/


class Solution {
public:
    int getSum(int a, int b) {
        int x = abs(a);
        int y = abs(b);
        
         // ensure that abs(a) >= abs(b)
        if(x<y)
            return getSum(b, a);
        
        // abs(a) >= abs(b) . This means 'a' determines the sign
        // 1. a > 0 && b > 0 => Both are positive so normal sum = (a+b)
        // 2. a > 0 && b < 0 => sum = (a-b) [Since a>b, so a determines the sign. This is the reason why we took a  below in sign]
        // 3. a < 0 && b < 0 => Both negative so sum = -(a+b)
        // 4. a < 0 && b > 0 => Won't happen since a > b
        
        int sign = a > 0 ? 1: -1;
        // Case 1 and 3
        if (a*b >= 0){
            // sum of two positive integers x + y where x > y
            while(y != 0) {
                int answer = x^y;
                int carry = (x&y) << 1;
                x = answer;
                y = carry;
            }
        }
        // Case 2
        else {
            // difference of two positive integers x - y where x > y
            while(y != 0) {
                int answer = x^y;
                int borrow = ((~x)&y) << 1;
                x = answer;
                y = borrow;
            }
        }
        return x * sign;
    }
};

// Recursive Implementation:
int getSum(int a, int b) {
    return b==0? a:getSum(a^b, (a&b)<<1); //be careful about the terminating condition;
}