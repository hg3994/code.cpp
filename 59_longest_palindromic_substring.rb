=begin 

Harshit Gupta | 23rd September, 2020
-------------------------------------

Ruby program for "Given a string s, find the longest palindromic substring in s."
https://leetcode.com/problems/longest-palindromic-substring/

Input: "babad"
Output: "bab"
Note: "aba" is also a valid answer.
------

Solution: 

  We iterate from 0 to length of the string and at each index, 
  We get the longest palindromic substring considering the element(s) at that index to be at the middle.
  We call the expand_from_middle twice on i,i and i, i+1 because their may exist
    - a palindrome of odd length where one letter is in middle
    - a palindrome of even length where two letters(i, i+1) are in middle

  expand_from_middle just keeps matching the elements in its extreme 
  and keep expanding it to get a larger substring

Time Complexity: O(n2)
Space Complexity: O(1)

https://repl.it/repls/GrotesqueWellinformedSigns


=end

def longest_palindrome(s)
  return s if s.length < 2
  
  i = 0
  lps = ''

  while i<s.length
    
    # Expand from the middle for the same element (for an odd length palindrome)
    str1 = expand_from_middle s, i, i
    
    # Expand from the middle for the element, element+1 character (for an even length palindrome)
    str2 = expand_from_middle s, i, i+1
    
    # Take the Maximum length one
    str = str1.length > str2.length ? str1 : str2
    
    # Check if we already have a palindrome with a greater length than it and likewise update
    if str.length > lps.length
      lps = str
    end
    i+=1
  end
  
  return lps
end



def expand_from_middle s, left, right
  
  # Till the characters keep on matching or we cross any boundaries, keep expaning from the middle (left-1, right+1)
  # We consider left and right to be initial middle elements (they are same for odd length palin, diff for even length palin)
  while (left >= 0 && right < s.length && s[left] == s[right])
    left -= 1
    right += 1
  end
  
  # return the palindromic substring
  return s[(left+1)..(right-1)]
end