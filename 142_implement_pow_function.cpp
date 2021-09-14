
/*

Harshit Gupta | 13th July, 2021
---------------------------------

Problem Statement: Implement pow(x, n), which calculates x raised to the power n.

Example 1:
    Input: x = 2.00000, n = 10
    Output: 1024.00000

Example 2:
    Input: x = 2.10000, n = 3
    Output: 9.26100

Example 3:
    Input: x = 2.00000, n = -2
    Output: 0.25000
    Explanation: 2-2 = 1/22 = 1/4 = 0.25

------

Solution: 
    Assume we have got the result of x^(n/2) , and now we want to get the result of x^n. 
        Let A be result of x^(n/2)
        We can talk about x^n based on the parity of n respectively. 
            - If n is even, we can use the formula (x^n)^2 = (x^2)^n to get x^n =A*A
            - If n is odd, then A * A = x^n−1
                Intuitively, We need to multiply another x to the result, so x ^ n = A*A*x

    This approach can be easily implemented using recursion. We call this method "Fast Power", 
        because we only need at most O(logn) computations to get x ^ n

    Eg: 
        1. ODD: 2^5 = 2^2 * 2^2 * 2 = so if we know 2^2, we can calculate 2^5.
        2. EVEN: 2^6 = 2^3 * 2^3 = so if we know w^3, we can calc 2^6


  TC: O(logN)
  SC: O(logN) For each computation, we need to store the result of X^(n/2)

Paradigm:
---
  NOTE: 

*/

class Solution {
public:
    
    double fastPow(double x, long long  n){
        if(n==0)
            return 1.0;
        double half = fastPow(x, n/2);
        if(n%2 == 0)
            return half*half;
        else
            return half*half*x;
    }
    
    double myPow(double x, int n) {
        long long N = n;
        if (N < 0) {
            x = 1 / x;
            N = -N;
        }
        return fastPow(x, n);
    }
};