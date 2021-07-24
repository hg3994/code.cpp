
/*

Harshit Gupta | 13th June, 2021
---------------------------------

C++ program for "Longest Happy String"

A string is called happy if it does not have any of the strings 'aaa', 'bbb' or 'ccc' as a substring.

Given three integers a, b and c, return any string s, which satisfies following conditions:
    - s is happy and longest possible.
    - s contains at most a occurrences of the letter 'a', at most b occurrences of the letter 'b' 
        and at most c occurrences of the letter 'c'.
    - s will only contain 'a', 'b' and 'c' letters.

If there is no such string s return the empty string "".

Example 1:
    Input: a = 1, b = 1, c = 7
    Output: "ccaccbcc"
    Explanation: "ccbccacc" would also be a correct answer.

Example 2:
    Input: a = 2, b = 2, c = 1
    Output: "aabbc"

Example 3:
    Input: a = 7, b = 1, c = 0
    Output: "aabaa"
    Explanation: It's the only correct answer in this case.

https://leetcode.com/problems/longest-happy-string/

------

Solution: 
    1. Create a max heap of the form pair<int,char> to store the count of each character.
    2. while (pq.size()>1)Pop out the first 2 pair who have the max frequency.
    3. Add greedily the occurances of the first pair to the ans and update it's count.
    4. For the second pair, compare it's occurances with the first pair and add accordingly (either 1 or 2)
    5. Finally add the pairs to the Max Heap if their count>0.
    6. If pq.empty() return ans, else add the leftover character 
        to the ans according to the remaining counts and return the ans.

TC: O(n)
SC:

Similar Questions:
    1. https://leetcode.com/problems/string-without-aaa-or-bbb/
        - Given two integers a and b, return any string s such that:
            - s has length a + b and contains exactly a 'a' letters, and exactly b 'b' letters,
            - The substring 'aaa' does not occur in s, and
            - The substring 'bbb' does not occur in s.
        - It is guarenteed that an answer would exist. No input like a=1, b=10) would be given.

Paradigm:
---
  NOTE: 

*/



class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        
        priority_queue<pair<int,char>>pq; // using max heap
        if(a) pq.push({a,'a'});
        if(b) pq.push({b,'b'});
        if(c) pq.push({c,'c'});
        
        string ans="";
    
        while(pq.size()>1){
            pair<int,char>one = pq.top();pq.pop();
            pair<int,char>two = pq.top();pq.pop();

            if(one.first>=2){
                ans+=one.second;
                ans+=one.second;
                one.first-=2;
            }
            else{
                ans+=one.second;
                one.first-=1;
            }
            // This is the most important condition:  two.first>=one.first
            // Try this test case a=0,b=2,c=7
            // c=7,b=2 result = cc 
            // c=5,b=2 result = ccb (if you did not add the two.first>=one.first here, 
            //                          you will get ccbb and then next round you get ccbbcc and return)
            // c=5,b=1 result = ccbcc 
            // c=3,b=1 result = ccbccb 
            // c=3,b=0 result = ccbccbcc
            if(two.first>=2 && two.first>=one.first){
                ans+=two.second;
                ans+=two.second;
                two.first-=2;
            }
            else{
                ans+=two.second;
                two.first-=1;
            }
            if(one.first>0)
                pq.push(one);
            if(two.first>0)
                pq.push(two);
        }
        // Only one element will remain in the queue and it will exit. So, add 1/2 elements of that as well.
        if(pq.empty())
            return ans;
        if(pq.top().first>=2){
            ans+=pq.top().second;
            ans+=pq.top().second;
        }
        else{
            ans+=pq.top().second;
        }
        return ans;
        
    }
};



// ------------------
// SIMILAR QUESTION 1
// ------------------

class Solution {
public:
    string strWithout3a3b(int a, int b) {
        priority_queue<pair<int, char>> pq;
        if(a) pq.push({a,'a'});
        if(b) pq.push({b,'b'});
        string ans = "";
        while(pq.size()>1){
            pair<int, char> one = pq.top(); pq.pop();
            pair<int, char> two = pq.top(); pq.pop();
            
            if(one.first >= 2){
                ans+= one.second;
                ans+= one.second;
                one.first -=2;
            }
            else{
                ans+= one.second;
                one.first -=1;
            }
            
            if(two.first >= 2 && two.first >= one.first){
                ans+= two.second;
                ans+= two.second;
                two.first -=2;
            }
            else{
                ans+= two.second;
                two.first -=1;
            }
            if(one.first > 0)
                pq.push(one);
            if(two.first > 0)
                pq.push(two);
        } 
        if(pq.empty())
            return ans;
        if(pq.top().first >= 2){
            ans += pq.top().second;
            ans += pq.top().second;
        }
        else{
            ans += pq.top().second;
        }
        return ans;
        
    }
};