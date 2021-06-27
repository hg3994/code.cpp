
/*

Harshit Gupta | 19th June, 2021
---------------------------------

C++ program for "Non-overlapping Intervals"
Given an array of intervals intervals where intervals[i] = [starti, endi], 
    return the minimum number of intervals you need to remove to make the rest of the intervals non-overlapping.
https://leetcode.com/problems/non-overlapping-intervals/

Example 1:
    Input: intervals = [[1,2],[2,3],[3,4],[1,3]]
    Output: 1
    Explanation: [1,3] can be removed and the rest of the intervals are non-overlapping.

Example 2:
    Input: intervals = [[1,2],[1,2],[1,2]]
    Output: 2
    Explanation: You need to remove two [1,2] to make the rest of the intervals non-overlapping.

Example 3:
    Input: intervals = [[1,2],[2,3]]
    Output: 0
    Explanation: You don't need to remove any of the intervals since they're already non-overlapping.

------

Solution: 1. Greedy
    2. DP

Paradigm:
---
  NOTE: 

*/



/*
1. Sort the intervals on start time.
2. There can be only 3 cases in a prev interval and the next interval
    a. no overlap: we update the prev and nothing is removed
    b. total overlap: we choose the smaller one since it can accomodate more intervals now. We update prev and since we do not consider the other interval now, we update removedCount.
    c. partial overlap: we choose the prev over current and update the removeCount.
    
    TC: O(nlogn)
    SC: O(1)
*/

class Solution {
public:
    int eraseOverlapIntervals(vector<vector<int>>& intervals) {
        if(intervals.size() <= 1)
            return 0;
        
        sort(intervals.begin(), intervals.end());
        
        int n= intervals.size(), prev=0, removeCount=0;
        
        for(int i=1;i<intervals.size(); i++){
            if(intervals[prev][1] > intervals[i][0]){ // overlapping
                if(intervals[prev][1] > intervals[i][1]){ // total overlap, move ahead & removeCount++
                    prev = i;   
                }
                removeCount++;    // partial overlap, only removeCount++; (no need to move ahead)
            }
            else { // no overlap, just move ahead, no change remove count
                prev = i;
            }
        }
        return removeCount;
    }
};

/*

Solution 1:

1. Sort the intervals on start time.
2. Create a dp[] array such that dp[i] stores the maximum number of valid intervals that can be included in the final list if  the intervals upto the ith interval only are considered, including itself.
3. While finding dp[i+1], we cant consider the valud of dp[i] only because it could be possible that ith or any prev intercal could be overlapping with the i+1th interval.
4. We need o consider the max of all dp[j]s such that j<=i and jth interval and ith dont overlap and can basically be taken together in a sense.
5. dp[i+1] = max(dp[j]+1) j<=i
6. Result = interval.size() - dp[n-1] since those many intervals are not in the consecutive sets of intervals

TC: O(n2)
SC: O(n)

[1,3] [2,5] [4,5] [6,7] [6,8] [7,8]

1--2--3--4--5--6--7--8--9
-----    ----  ---|---
   ----------  -------

By removing below 2,we can get intervals to be non-overlapping.

     [1,3] [2,5] [4,5] [6,7] [6,8] [7,8]
dp[]   1     1     2     3     3     4


*/

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    if(intervals.size() <= 1)
        return 0;

    sort(intervals.begin(), intervals.end());

    int n= intervals.size();
    vector<int>dp(n,1);

    for(int i=1; i<n; i++){
        for(int j=i-1; j>=0; j--){
            if(intervals[j][1] <= intervals[i][0]){ // non-overlapping
                dp[i] = max(dp[i], dp[j]+1);
            }
        }
    }
    return n-dp[n-1];
}

