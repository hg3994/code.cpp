
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for "Merge Intervals"


Given an array of intervals where intervals[i] = [starti, endi], merge all overlapping intervals, 
    and return an array of the non-overlapping intervals that cover all the intervals in the input.

Example 1:
    Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
    Output: [[1,6],[8,10],[15,18]]
    Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
    Input: intervals = [[1,4],[4,5]]
    Output: [[1,5]]
    Explanation: Intervals [1,4] and [4,5] are considered overlapping.

https://leetcode.com/problems/merge-intervals/
------

Solution: 
    1. Sort the intervals on start time.
    2. For every interval, we can only have two cases:
        a. If they dont overlap (merged.back()[1] < interval[0]), then we push the interval as a separate thing.
            [ ]  {    }
        b. If they overlap ,then we update the back of the last merged to the max of this interval's end and the already existing one.
            [ { ]     }
            [ {}   ]

Time Complexity: O(nlogn)
Space Complexity: O(n)

Paradigm: Merge, Intervals
---
  NOTE: 

*/

class Solution {
public:
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int m = intervals.size();
        vector<vector<int>> merged;
        
        // sort the intervals on start time.
        sort(intervals.begin(), intervals.end());
        
        for(auto interval : intervals){
            // if the list of merged intervals is empty or if the current interval does not overlap with the previous, simply append it.
            if(merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            // otherwise, there is overlap, so we merge the current and previous intervals in the merged vector
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }        
        return merged;
    }
};