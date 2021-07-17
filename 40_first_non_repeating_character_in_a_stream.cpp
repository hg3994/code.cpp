/* 
Harshit Gupta | 30th November, 2018

https://ide.geeksforgeeks.org/LRCUp2jid3
C++ program for getting the first non-repeating character in a stream of numbers.

Solution: Maintain a hash of freqency of characters and a queue which will 
    contain characters that appeared in the stream for the first time. For example, if 
    'a' appeard and then two 'b' appeared, then queue would be [a,b]. This can be easily
    done with the help of the freq hash. The front of the queue would represent 
    the first non-repeating character in the stream.

Paradigm: Queue, Hash

Time Complexity: O(MAX_CHAR)

Note: The time complexity is O(1) or O(MAX_CHAR) even when we have a loop in the queue.
    The reason behind this is the fact that the queue size can at most 'MAX_CHAR', so 
    in the worst case we will loop for 26 times which is constant.

Similar Question:
    1. https://leetcode.com/problems/first-unique-character-in-a-string/
        - First Non Repeating Character in a String

#Agoda

*/

#include <bits/stdc++.h>
using namespace std; 
#define MAX_CHAR 26


void firstNonRepeatingCharacter(string s){
    
    // Take a freq array of size MAX_CHAR to keep freqency of each char in the stream.
    int freq[MAX_CHAR]={0};
    int n = s.size();
    
    // A queue to store the elements which are of freq<=1, 
    // So, for 'MAX_CHAR' letters, the queue size can be at most MAX_CHAR
    queue<char> q;
    
    for(int i=0;i<n;i++){
        // Increase the freq of the character in the hash.
        freq[s[i]-'a']++;
        
        // If its freq is <= 1, this means that this has appeared only once till now,
        // so we insert it in the queue.
        if(freq[s[i]-'a'] <= 1){
            q.push(s[i]);
        }
        
        // Till the queue is empty, we iterate.
        while(!q.empty()){
            
            // Get the front character
            char front_char = q.front();
            
            // If the freq of the first character in the queue is >1, then 
            // it means it appeard now again and is no more the 'first non-repeating' char. Pop it.
            if(freq[front_char-'a'] > 1){
                q.pop();
            }
            
            // If the freq of the front is still <1, then it means
            // that something else appeared in this pass in the stream and changed freq of something else.
            // The front of the queue remains the first-non-repeating-character, so we break.
            else{
                break;
            }
        }
        
        // If the queue became empty, it means that there is no first-non-repeating character.
        if(q.empty()){
            cout<<"-1 ";
        }
        
        // Print front of queue since it is the first non-repeating character.
        else{
            cout<<q.front()<<" ";
        }
    }
    
}

int main() 
{
    string s= "geeksforgeeksandgeeksquizfor";
    firstNonRepeatingCharacter(s);
    return 0; 
} 


// -----------------------------------------
// Find first non-repeating char in a string
// -----------------------------------------

// Approach 1: using Maps
class Solution {
public:
    int firstUniqChar(string s) {
        unordered_map<char, int> map;
        
        for(int i=0; i<s.size(); i++)
            map[s[i]]++;
            
        for(int i=0; i<s.size(); i++)
            if (map[s[i]] == 1)
                return i;
        
        return -1;
    }
};

// Approach 2: Using vector
class Solution {
public:
    int firstUniqChar(string s) {
        vector<int> map(26, 0);
        
        for(int i=0; i<s.size(); i++)
            map[s[i]-'a']++;
        
        for(int i=0; i<s.size(); i++)
            if (map[s[i]-'a'] == 1)
                return i;
        
        return -1;
    }
};