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