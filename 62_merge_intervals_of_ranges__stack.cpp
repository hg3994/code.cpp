/*

Harshit Gupta | 28th September, 2020
-------------------------------------

Ruby program for "Given a collection of intervals, merge all overlapping intervals."

https://leetcode.com/problems/merge-intervals/

Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

------

Solution: 
    1. We sort the intervals on start time.
    2. iterate over intervals and keep checking if it is merging with the last one.
    3. If it overlapping, then merge it with the last one by updating the "end" time to be max of
        what is already present and the new interval. This covers both the cases of partial overlap
        and total overlap between two intervals since max of the two is used.
    4. If it not overlapping, push it in the merged ans array.

Time Complexity: O(nlogn) for sorting.
Space Complexity: O(1)

Paradigm: Intervals

Follow UP Question:
    1. https://leetcode.com/problems/merge-intervals/discuss/21452/Share-my-interval-tree-solution-no-sorting
        - Question: How do you add intervals and merge them for a large stream of intervals? (Facebook Follow-up Question)
        - Check LC Solution Link.
*/

class Solution {
public:
    
    vector<vector<int>> merge(vector<vector<int>>& intervals) {
        int m = intervals.size();
        vector<vector<int>> merged;
        
        // sort the intervals on start time.
        sort(intervals.begin(), intervals.end());
        
        for(auto interval : intervals){
            // Non Overlapping, then add new
            if(merged.empty() || merged.back()[1] < interval[0]) {
                merged.push_back(interval);
            }
            // Overlapping, then update the end to the max of two intervals
            else {
                merged.back()[1] = max(merged.back()[1], interval[1]);
            }
        }        
        return merged;
    }
};