=begin 

Harshit Gupta | 28th September, 2020
-------------------------------------

Ruby program for "Given a collection of intervals, merge all overlapping intervals."

https://leetcode.com/problems/merge-intervals/
https://leetcode.com/problems/merge-intervals/discuss/21452/Share-my-interval-tree-solution-no-sorting

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

------

Solution: We solve this using a stack.
  - Sort the array on the start time.
  - Insert the first element into the stack.
  - From element 2 to n, ..
      If the new interval's start is earlier than the last interval's end 
      AND
      If the new interval's end is later than the last interval's end
        MERGE THEM

      If the new interval's start is earlier than the last interval's end
      AND
      If the new interval's end is also earlier than the last interval's end 
        New Interval is already within the last interval

      ELSE
        Push it in the stack since it can not be merged with the last interval. 
        However, there are can be more intervals which can be merged to this one.


Time Complexity: O(n)
Space Complexity: O(n) for stack


=end


def merge(intervals)
  
  return [] if intervals.size == 0
  return [intervals[0]] if intervals.size == 1
  
  # Custom comparator like this:
  # intervals.sort! do |a,b| 
  #   a[0] <=> b[0]
  # end
  # Sort them on starting time of each interval
  intervals.sort!
  
  # Array can be used as a stack. Insert the first element into it.
  s = Array.new
  s.push (intervals[0])
  
  
  intervals.each_with_index do |interval, i|
    next if i==0
    
    # If the new interval's start is earlier than the last interval's end .. AND
    # If the new interval's end is later than the last interval's end .. Merge them
    # [1,4], [2,6] => [1,6]
    if interval[0] <= s.last[1] && interval[1] > s.last[1]
      last_interval = s.pop
      merged_interval = [last_interval[0], interval[1]]
      s.push merged_interval
      
    # If the new interval's start is earlier than the last interval's end .. AND
    # If the new interval's end is also earlier than the last interval's end .. New Interval is already within the last interval
    # [1,4], [2,3] => [1,4]    (Do Nothing)
    elsif  interval[0] <= s.last[1] && interval[1] <= s.last[1]
    
    # Intervals don't interfare with each other, so push it into the stack
    else
      s.push (interval)
    end
  end
  s
end

p merge [[1,3], [2,4], [5,7], [8,10], [11,14], [12,13]]