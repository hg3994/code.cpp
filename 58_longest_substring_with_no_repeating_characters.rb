=begin 

Harshit Gupta | 22nd September, 2020
-------------------------------------

Program for "Length of the longest substring with no repeating characters."

https://leetcode.com/problems/longest-substring-without-repeating-characters/


Input: s = "pwwkew"
Output: 3
Explanation: The answer is "wke", with the length of 3.
Notice that the answer must be a substring, "pwke" is a subsequence and not a substring.
------

Solution: 
  We will use the Sliding Window Algorithm to get the longest substring without repeating chars.
  - We will have a flexible window and keep on adding unique characters to it.
  - As we get a character which is already present in the window, we have to remove it from the window
  - So we loop from the starting of the window and keep eliminating characters till we reach the 'repeated character' and we remove it as well.
  - Do the same thing again
  - The maximum size of the hash at any time would be the "Length of the longest substring with no repeating characters"

https://repl.it/repls/HelplessGargantuanMass

NOTE: This type of Sliding Window solution can be used in a lot of these types of problems
  Find the longest substring with "....."

  - Find the longest substring with at max 2 distinct characters.
      https://leetcode.com/problems/fruit-into-baskets/
      https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/

  - Find the longest substring with containing the same character but with K replacements allowed:
      Solved in 124_...

=end



def length_of_longest_substring_with_no_repeating_chars(s)
  return s.length if s.length <= 1
  
  res = 0
  
  # hash to keep the characters which are in the flexi sliding window (i, j-1)
  h = {} 
  
  # i is the starting of the flexi sliding window.
  i = 0
  
  # j-1 is the ending of the flexi sliding window. 
  # j would always point to the element next to the window so that it can include j in the window and then move ahead (j++)
  j = 1  
  
  # Get the first character in the window. Now the window is of size 1
  h[s[i]] = true 
  
  # Till the window end reaches the array length
  while (j!=s.length) do
    
    # If the next character is not in the hash (window), 
    # include it in the window and check if this is the maximum size of the window
    # move ahead (j++) to check for more
    if h[s[j]] == nil
      h[s[j]] = true
      if res < (j-i+1)
        res = (j-i+1)
      end
      j+=1
    
    # The next character is in the hash (window),
    # Now we move the starting of the window(i) and eliminate chars till we eliminate the 'repeating character' s[j]
    # After the elimination of the repeating character, we are sure that it does not have any repeating characters.
    else
      while(i!=j) do
        if(s[i]==s[j])
          h.delete(s[i])
          i+=1
          break
        end
        h.delete(s[i])
        i+=1
      end
    end
  end
  
  return res
end

puts length_of_longest_substring_with_no_repeating_chars "pwwkew"



# -----------------
# // C++ Solution 
# -----------------
# class Solution {
# public:
    
#     // Solved using Sliding Window
    
#     int lengthOfLongestSubstring(string s) {
#         if (s == "")
#             return 0;

#         // map to hold the characters which are in the flexi sliding window (i, j-1)
#         unordered_map<char, bool> map;
#         int i = 0; // i is the starting of the flexi window
#         int j = 1; // j is the next element of the flexi window
#         int maxLen = 1;
#         map[s[0]] = true;
        
#         // Till we reach the end of the string
#         while(j != s.size()) {

#             // If s[j] is not a repeating element since it is not in map
#             // then put it in the map and recalculate the maxLen, move ahead j++
#             if(map.find(s[j]) == map.end()){
#                 map[s[j]] = true;
#                 maxLen = max(maxLen, j-i+1);
#                 j++;
#             }

#             // Else if s[j] is a repeating element since it is in map
#             // move the start of window till we reach the matching character 
#             // and keep removing the letters from map. Once you find the matching char, move ahead
#             else {
#                 while(s[i]!=s[j]){
#                     map.erase(s[i]);
#                     i++;
#                 }
#                 map.erase(s[i]);
#                 i++;
#             }
#         }
#         return maxLen;
#     }
# };



# https://leetcode.com/problems/fruit-into-baskets/
# // At Max 2 distinct Characters

# class Solution {
# public:
#     int totalFruit(vector<int>& tree) {
#         if(tree.size() <= 1)
#             return tree.size();
        
#         int i=0;
#         int j=1;
#         int maxLength = 1;
#         unordered_map<int, int> map;
#         map[tree[0]] = 1;
        
#         while(j!=tree.size()){
#             // char is already present in the map
#             if(map.find(tree[j]) != map.end()){
#                 map[tree[j]]++;
#                 maxLength = max(maxLength, j-i+1);
#                 j++;
#             }
#             // char is not present in the map and the size of map is 0(no elements, this is the first char) or 1(one element, this is 2nd char)
#             else if (map.size() == 0 || map.size() == 1) {
#                 map[tree[j]] = 1;
#                 maxLength = max(maxLength, j-i+1);
#                 j++;
#             }
#             // char is not present in map and there are already 2 distinct chars in the map
#             else {
#                 while(i<j){
#                     map[tree[i]]--;
#                     if(map[tree[i]] == 0){
#                         map.erase(tree[i]);
#                         i++;
#                         break;
#                     }
#                     i++;
#                 }
#                 map[tree[j]] = 1;
#                 j++;
#             }
#         }
#         return maxLength;
#     }
# };


# https://leetcode.com/problems/longest-substring-with-at-most-two-distinct-characters/
# // ANOTHER SOLUTION TO THE SAME PROBLEM: 

# class Solution {
# public:
  
#   int lengthOfLongestSubstringTwoDistinct(string s) {
    
#     if (s.length() <= 1)
#       return s.length();
    
#     // These are the boundaries of our flexi window 'left' and 'right'
#     int l = 0;
#     int r = 0;
#     int result = -1;
    
#     // Map to store the elements are their frequencies.
#     // As soon we have two distinct elements and we have a third one, we start removing from the front.
#     unordered_map<char, int> freq;
    
#     while(r < s.length()){
      
#       // If the letter exists in map, just increase the frequency
#       // Since we are not adding a new element, it is ok to increase just the freq and move the window ahead
#       if (freq.find(s[r]) != freq.end()){ 
#         freq[s[r]] = freq[s[r]] + 1;
        
#         // Check if this is the longest substring with distinct elements.
#         result = result > (r-l+1) ?  result : (r-l+1);
#       }
#       else{
#         // Check how many distinct elements we have right now, 
#         // if we have 0 or 1, add another distinct element s[r] with frequency 1.
#         if(freq.size() == 0 || freq.size() == 1){
#           freq[s[r]] = 1;

#           // Check if this is the longest substring with distinct elements.
#           result = result > (r-l+1) ?  result : (r-l+1);
#         }
#         else {
#           // We already have 2 distinct elements, we need to remove elements from start
#           // of the window till we have only 1 distinct element, then we can add the element s[r] with freq 1
#           // While removing elements, we keep decreasing their frequencies and when any becomes 0, we simply erase it.
#           while (l<r && freq.size() != 1){
#             freq[s[l]] = freq[s[l]]-1;
#             if(freq[s[l]] == 0)
#               freq.erase(s[l]);
#             l++;
#           }
          
#           freq[s[r]] = 1;
          
#         }
#       }
#       r++;
#     }
#     return result;
#   }
# };