
/*

Harshit Gupta | 30th July, 2021
---------------------------------

Problem Statement: Count the number of prime numbers less than a non-negative number, n.

Example 1:
    Input: n = 10
    Output: 4
    Explanation: There are 4 prime numbers less than 10, they are 2, 3, 5, 7.

Example 2:
    Input: n = 0
    Output: 0

https://leetcode.com/problems/count-primes/submissions/
------

Solution: Sieve of Eratosthenes

TC: 
    Each time we hit a prime, we have to launch a search through the rest of the array to 
    "cross out" the multiples of that prime because we know they aren't prime (The Sieve 
    of Erothostanes). But how many "cross outs" do we have to do for each prime?

    Well,
    For 2, we have to cross out n/2 numbers.
    For 3, we have to cross out n/3 numbers.
    For 5, we have to cross out n/5 numbers.
    ...etc for each prime less than n.

    This means that the time complexity of "crossing out" is 
        O(n/2 + n/3 + n/5 + ... + n/(last prime before n)).

    What can this sum be simplified to in terms of n?

    Well, for starters, we can factor out the n:

    O(n/2 + n/3 + n/5 + ... + n/(last prime before n))
    = O(n) * O(1/2 + 1/3 + 1/5 + ... + 1/(last prime before n))

    What can O(1/2 + 1/3 + 1/5 + ... + 1/(last prime before n)) be simplified to in terms of n?

    I won't go into detail here but the answer is essentially bounded by log(log(n)). 
    The proof for this is summed up well here for those interested: 
        http://www.cs.umd.edu/~gasarch/BLOGPAPERS/sump.pdf

    So now we have that the time complexity of "crossing out" is:

    O(sqrtn) * O(1/2 + 1/3 + 1/5 + ... + 1/(last prime before n))
    = O(sqrtn) * O(log(log(n)))
    = O(sqrt(n) * log(log(n)))

SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


class Solution {
public:
    int countPrimes(int n) {
        if (n <= 2) {
            return 0;
        }
        int ans = 0;
        vector<bool> prime(n+1, true);
        for(int i=2; i*i<=n; i++){
            if(prime[i] == true){
                for(int j=2*i; j<=n; j+=i){
                    prime[j] = false;
                }
            }
        }
        
        for(int i=2; i<n; i++){
            if(prime[i] == true){
                ans++;
            }
        }
        
        return ans;
    }
};