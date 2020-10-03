=begin 

Harshit Gupta | 26th September, 2020
-------------------------------------

Ruby program for "Given n non negative integers, each representing a bar, 
  choose 2 lines so that if water is poured, then it contains the maximum water in the container "

https://leetcode.com/problems/container-with-most-water/

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
------

Solution: 
  There's obviously the naive way of doing such thing in O(n2) time by 
    - comparing each bar to one another
    - get the minimum of the two bars and the distance between them
    - the water stored = min (two bars)*distance btw them

  But then there's an optimal solution to this problem in faster time 
  Idea is to keep maximizing the water by reducing the width but by choosing a larger bar
  We start with the widest container but will achieve one with max water by making bars closer
  Algo:
    - Have a left pointer which would be the left side of the vessel
    - Have a right pointer which would be the right side of the vessel
    - Get the amount of water it can store
    - To maximize the water, compare the bars
    - Move the left pointer + 1 if that is smaller
    - Move the right pointer to - 1 if that is smaller

Time Complexity: O(n)
Space Complexity: O(1)

https://repl.it/repls/SilentFamousCodegeneration

=end


def max_area(height)
  res = 0
  l = 0
  r = height.length-1
    
  while(l!=r)
    minimum_height_of_two_lines = [height[l], height[r]].min
    
    water_in_vessel = minimum_height_of_two_lines * (r-l)
    res = [res, water_in_vessel].max
    
    if minimum_height_of_two_lines == height[l]
      l+=1
    else
      r-=1
    end
  end
  res
end

puts max_area [1,8,6,2,5,4,8,3,7]