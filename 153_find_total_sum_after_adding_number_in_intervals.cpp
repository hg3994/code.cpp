
/*

Harshit Gupta | 24th June, 2021
---------------------------------

Problem Statement:

There are n flights that are labeled from 1 to n.
You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi] represents a booking 
	for flights firsti through lasti (inclusive) with seatsi seats reserved for each flight in the range.

Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.


Example 1:
	Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
	Output: [10,55,45,25,25]
	Explanation:
		Flight labels:        1   2   3   4   5
		Booking 1 reserved:  10  10
		Booking 2 reserved:      20  20
		Booking 3 reserved:      25  25  25  25
		Total seats:         10  55  45  25  25
		Hence, answer = [10,55,45,25,25]

Example 2:
	Input: bookings = [[1,2,10],[2,2,15]], n = 2
	Output: [10,25]
	Explanation:
		Flight labels:        1   2
		Booking 1 reserved:  10  10
		Booking 2 reserved:      15
		Total seats:         10  25
		Hence, answer = [10,25]

https://leetcode.com/problems/corporate-flight-bookings/

------

Solution: Sweep Line

	Set the change of seats for each day.
	If booking = [i, j, k], then it needs k more seat on ith day and we don't need those seats on (j+1)th day.
	We accumulate these changes then we have the result that we want.

    TC: O(n)
    SC: O(n)

Paradigm: Sweep Line
---
    NOTE: 

    Similar Questions:
        1. https://leetcode.com/problems/describe-the-painting/
        	- Read the question, very difficult to explain here.

*/


// Approach : Sweep Line
// [[1,2,10],[2,3,20],[3,5,25]]
// Flights:     1   2   3   4   5
// index  :     0   1   2   3   4
//              10    -10
//                 20     -20
//                     25           -25 (no need to add this)
// res:         10 30  45  25  25

class Solution {
public:
    vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
        vector<int> res(n, 0);
        for (auto &v : bookings) {
            res[v[0] - 1] += v[2];
            if (v[1] < n) // This is just to prevent the last one since our array is of len n
                res[v[1]] -= v[2];
        }
        for (auto i = 1; i < n; ++i) 
            res[i] += res[i - 1];
        return res;
    }
};

// Solution 2:
vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
    vector<int> res(n + 1, 0);
    for (auto & v : bookings) {
        res[v[0] - 1] += v[2];
        res[v[1]] -= v[2];
    }
    for (int i = 1; i < n; ++i)
        res[i] += res[i - 1];
    return {res.begin(), res.end() - 1};
}


// ------------------
// SIMILAR QUESTION 1
// ------------------

// [[1,4,5],[4,7,7],[1,7,9]]
// 0 1  2 3 4 5 6   7
// 0 14 0 0 2 0 0 -16 
// 0 0  0 0 1 0 0   1
// [[1,4,14],[4,7,16]]


// [[1,7,9],[6,8,15],[8,10,7]]
// 0 1 2 3 4 5  6  7  8 9 10
// 0 9 0 0 0 0 15 -9 -8 0 -7 
// 0 0 0 0 0 0  0  1  1 0  1 
// [[1,6,9],[6,7,24],[7,8,15],[8,10,7]]

// [[1,4,5],[1,4,7],[4,7,1],[4,7,11]]
// 0  1 2 3 4 5 6   7
// 0 12 0 0 0 0 0 -12
// 0  0 0 0 1 0 0   1
// [[1,4,12],[4,7,12]]

// Why do we need mix[i] != mix[last_i] ?
//     [[1,7,9],[6,8,15]
//     For cases like 
//     ------9-------
//               --15--

//     ends are marked at 7 and 8 only but what about 6 ? 
//     1-6 is a different mix so we need to report that by checking if mix[i] != mix[i-1]

// Why do we need ends[i] ?
//      It is given that if the sum is same but mixed color sets are different, then we must report them as different sets in the ans.
//      mix[i] would remain same if it is 7+5=12 or 1+11=12 and hence we wouldn't be able to check that, so we need to mark each end and identify it.
// Example: last one


class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        vector<vector<long long>> res;
        vector<long long> mix(100001, 0);
        vector<bool> ends(100001, 0);
        int last_i = 0;
        for(auto &v: segments){
            mix[v[0]] += v[2];
            mix[v[1]] -= v[2];
            ends[v[1]] = true;
        }
        
        // for(int i=0; i<20; i++)
        //     cout<<mix[i]<<" ";
        // cout<<endl;
        // for(int i=0; i<20; i++)
        //     cout<<ends[i]<<" ";
        
        // Keep adding mix[i-1] into mix[i] (Prefix Sum)till we see that this mix[i] != mix[last_i] OR 
        for(int i=1; i<100001; i++){
            mix[i] += mix[i-1];
            if(mix[i] != mix[last_i] || ends[i]){
                if(mix[last_i] != 0)
                    res.push_back({last_i, i, mix[last_i]});
                last_i = i;
            }
        }
        return res;
    }
};

// Approach 2: Enhancement over the last solution to select specific MAX sized array
class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        int minIdx = INT_MAX, maxIdx = INT_MIN;
        for(const auto& seg : segments){
            minIdx = min(minIdx, seg[0]);
            maxIdx = max(maxIdx, seg[1]);
        }
        vector<long long> painting(maxIdx + 1, 0);
        for(const auto& seg : segments){
            painting[seg[0]] += seg[2];
            painting[seg[1]] -= seg[2];
        }
        vector<vector<long long>> ans;
        long long curColor = painting[minIdx];
        int prev = minIdx;
        for(int i = minIdx + 1; i <= maxIdx; i++){
            if(painting[i] != 0){
                if(curColor != 0){
                    ans.push_back({prev, i, curColor});
                }
                curColor += painting[i];
                prev = i;
            }
        }
        return ans;
    }
};