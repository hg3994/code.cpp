
/*

Harshit Gupta | 12th June, 2021
---------------------------------

C++ program for "Add two binary numbers"
https://leetcode.com/problems/add-binary/
https://leetcode.com/problems/adding-two-negabinary-numbers/
https://leetcode.com/problems/convert-to-base-2/

https://www.youtube.com/watch?v=qq64FrA2UXQ&ab_channel=BackToBackSWE

Example 1:
    Input: a = "11", b = "1"
    Output: "100"

Example 2:
    Input: a = "1010", b = "1011"
    Output: "10101"
------

Solution: 
    1. Adding with basic rules of binary addition and carry
        TC: O(n)
        SC: O(1)
    2. Bitmanipulation
        - AND operation tells me the positions where carry is required. (11 -> 1)
        - Carry is actually required one position to the left of the where it ws discovered
        - XOR operator is helpful for simulating the addition operator
    3. Bit Manipulation 2
        - Traverse the binary representation of both numbers from the right
        - Add both the ith and jth digit into an integer carry
        - (carry & 1) would tell you the result so push it in
        - (carry >> 1) if there is a carry over we need for the next time.
        - Reverse the result.

Paradigm: Bitmanipulation
---
  NOTE: An interesting problem mentioned in converting to base -2. Please read that article. 
    It has a very small change. Just carry = (carry >> 1) becomes: carry = -(carry >> 1)

*/

class Solution {
public:
    string addBinary(string a, string b) {

        if (a.size() < b.size())
            return addBinary(b, a);     // a is longer and b is smaller

        // Padding the smaller string with 0s ahead to make both have same size
        while(a.size()!=b.size())
            b = '0'+b;

        int i = a.size()-1, carry=0;
        string ans;

        for(int i=a.size()-1; i>=0; i--) {
            if (a[i]=='1' && b[i]=='1') {
                if (carry)
                    ans = ans + '1';
                else
                    ans = ans + '0', carry = 1;
            }
            else if ((a[i]=='1' && b[i] == '0') || (a[i]=='0' && b[i] == '1')) {
                if(carry)
                    ans = ans +'0', carry = 1;
                else
                    ans = ans + '1';
            }
            else {
                if(carry)
                    ans = ans +'1', carry=0;
                else
                    ans = ans + '0';
            }
        }
        if(carry)
            ans = ans+'1';
        reverse(ans.begin(), ans.end());
        return ans;
    }
};


// Approach 2: 
// sum without carry = a^b (xor)
// carry = (a & b) << 1
// just sum up carry and "sum without carry"
// Difficult to do using C++.
// Java solution: 
// 
//    import java.math.BigInteger;
//    class Solution {
//      public String addBinary(String a, String b) {
//        BigInteger x = new BigInteger(a, 2);
//        BigInteger y = new BigInteger(b, 2);
//        BigInteger zero = new BigInteger("0", 2);
//        BigInteger carry, answer;
//        while (y.compareTo(zero) != 0) {
//          answer = x.xor(y);
//          carry = x.and(y).shiftLeft(1);
//          x = answer;
//          y = carry;
//        }
//        return x.toString(2);
//      }
//    }

// Approach 3: Here the numbers are in vectors
vector<int> addBinary(vector<int>& A, vector<int>& B) {
    vector<int> res;
    int carry = 0, i = A.size() - 1, j = B.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        if (i >= 0) 
             carry += A[i--];
        if (j >= 0) 
             carry += B[j--];
        res.push_back(carry & 1);
        carry = (carry >> 1);
    }
    reverse(res.begin(), res.end());
    return res;
}