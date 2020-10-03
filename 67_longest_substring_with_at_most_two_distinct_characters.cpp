/*

Harshit Gupta | 30th September, 2020
-------------------------------------

C++ program for "Given a string s , find the length of the longest substring t  that contains at most 2 distinct characters."

https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

Input: "ccaabbb"
Output: 5
Explanation: t is "aabbb" which its length is 5
------

Solution: We will use the Sliding Window Algorithm to get the longest substring without repeating chars.
  - We will have a flexible window and keep on adding unique characters to it.
  - As we get a character which is already present in the window, we increase the frequency of that character.
  - If it not present in the window, then check for the size, if it is 0 or 1, add it.
  - If the size == 2, then we cant add other element and this element is different from the two as well,
      so we start removing the characters from start of the window till we have just one distinct character.
  - We calculate the max substring everytime we increase the frequency or add a new character to the map.


Time Complexity: O(n)
Space Complexity: O(1)

*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  
  int lengthOfLongestSubstringTwoDistinct(string s) {
    
    if (s.length() <= 1)
      return s.length();
    
    // These are the boundaries of our flexi window 'left' and 'right'
    int l = 0;
    int r = 0;
    int result = -1;
    
    // Map to store the elements are their frequencies.
    // As soon we have two distinct elements and we have a third one, we start removing from the front.
    unordered_map<char, int> freq;
    
    while(r < s.length()){
      
      // If the letter exists in map, just increase the frequency
      // Since we are not adding a new element, it is ok to increase just the freq and move the window ahead
      if (freq.find(s[r]) != freq.end()){ 
        freq[s[r]] = freq[s[r]] + 1;
        
        // Check if this is the longest substring with distinct elements.
        result = result > (r-l+1) ?  result : (r-l+1);
      }
      else{
        // Check how many distinct elements we have right now, 
        // if we have 0 or 1, add another distinct element s[r] with frequency 1.
        if(freq.size() == 0 || freq.size() == 1){
          freq[s[r]] = 1;

          // Check if this is the longest substring with distinct elements.
          result = result > (r-l+1) ?  result : (r-l+1);
        }
        else {
          // We already have 2 distinct elements, we need to remove elements from start
          // of the window till we have only 1 distinct element, then we can add the element s[r] with freq 1
          // While removing elements, we keep decreasing their frequencies and when any becomes 0, we simply erase it.
          while (l<r && freq.size() != 1){
            freq[s[l]] = freq[s[l]]-1;
            if(freq[s[l]] == 0)
              freq.erase(s[l]);
            l++;
          }
          
          freq[s[r]] = 1;
          
        } // else if else}
      } // else }
      r++;
    } // while }
    return result;
  }
};

int main(){
  Solution s;
  cout<< s.lengthOfLongestSubstringTwoDistinct("ccaabbb") << endl; // 5 (aabbb)

}