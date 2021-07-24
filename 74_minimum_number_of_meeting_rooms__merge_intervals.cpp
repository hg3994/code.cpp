
/*

Harshit Gupta | 17th October, 2020
----------------------------------

C++ program for "Given an array of meeting time intervals consisting of start and end times 
  [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required."

https://leetcode.com/problems/meeting-rooms-ii/


  Input: intervals = [[0,30],[5,10],[15,20]]
  Output: 2

  Input: intervals = [[7,10],[2,4]]
  Output: 1


------
Very well written solution: https://leetcode.com/problems/meeting-rooms-ii/solution/

Solution 1: 
  1. Sort the intervals on start time so that we can know the requirement of meeting room allocation.
  2. We keep a vector where we store the 'end' time of each meeting room. This will tell us when this meeting room would be vacated.
  3. For each interval, we want to allocate a meeting room for it. We check whether an existing meeting room 
    is vacant (based on their end times) with the start time of the meeting interval[i][0] by iterating over the rooms vector.
    - If there is any such room, we update the meeting room timings to end at interval[i][1]
    - If there is no such room, we create another room for this interval[i] in rooms vector (push its own end-time).

Time Complexity: O(nlogn)+O(n2) = O(n2)
Space Complexity: O(n) to keep the rooms.
---

Solution 2: 
    In the previous solution, we iterate over all the present rooms to check whether a room is vacant or not.
    However, we can do better than this by making use of Priority Queues or the Min-Heap data structure.
    Instead of manually iterating on every room that's been allocated and checking if the room is available or not, 
    we can keep all the rooms in a min heap where the key for the min heap would be the ending time of meeting.
    
    So, every time we want to check if any room is free or not, simply check the topmost element of the min heap as that 
    would be the room that would get free the earliest out of all the other rooms currently occupied.
    (A meeting completing at 10 would be vacated before any meeting which completes at 11 or 12)
    If the room we extracted from the top of the min heap isn't free, then no other room is. 
    So, we can save time here and simply allocate a new room.

    1. Sort the intervals on start time so that we can know the requirement of meeting room allocation.
    2. We keep a PQ where we store the 'end' time of each meeting room. This will tell us when this meeting room would be vacated.
    3. For each interval, we want to allocate a meeting room for it. We check whether the top of the queue (latest end time)
        and the start time of the meeting interval[i][0].
        - If our meeting time is later than the latest meeting completing time, we remove that meeting from the 
            list & push ours. We would be able to accomodate this meeting in the older room.
        - If our meeting time overlaps with the latest meeting completion time, we add out meeting in the queue 
            since it would require a room of its own.
    5. Return the size of the PQ since it would contain the rooms required with their end times.  


x=(0,6),(1,4),(2,5),(3,8),(7,9)

0----1---2----3----4----5---6---7---8---9
-----------------------------                   6
     ---------------                            4,6
         ----------------                       4,5,6
              -----------------------           4,5,6,8
                                ---------       5,6,8,9


x=(0,6),(1,2),(3,4),(3,8),(5,6),(7,9),(7,9),(7,9),(7,9),(7,9)

0----1---2----3----4----5---6---7---8---9       PQ
-----------------------------                   6
     ----------                                 3,6
              ------                            3,4,6
              -----------------------           3,4,6,8
                        -----                   4,6,6,8
                        -----                   6,6,6,8
                        -----                   6,6,6,6,8
                                ---------       6,6,6,8,9
                                ---------       6,6,8,9,9
                                ---------       6,8,9,9,9
                                ---------       8,9,9,9,9
                                ---------       8,9,9,9,9,9
1   2    2    4    3    5   5   6   6   5       Numbers of meetings in the rooms
   

Time Complexity: O(nlogn)
Space Complexity: O(n) to keep the rooms.

Paradigm: Merge Interval, Priority Queue


Similar Questions:
  1.  Given there is a 1D plane with line segments as [[s1,e1],[s2,e2],...] (si < ei). Calculate max 
        number of overlapping lines.
        - The max number of overlapping lines is the minimum number of meeting rooms required.
        - This was asked in GRAB
  2. https://leetcode.com/problems/meeting-rooms/
        - Given an array of meeting time intervals, determine if a person could attend all meetings.
        - If they are overlapping, one can not attend the meetings, otherwise he can

---
  NOTE: 
    FollowUp: How would you know which meeting room is busiest of all?

*/


#include<bits/stdc++.h>
using namespace std;


class Solution1 {
public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    // If <=1 intervals, then interval size is min num of meeting rooms.
    if(intervals.size() <= 1)
      return intervals.size();

    // Sort the intervals on their starting time
    sort(intervals.begin(), intervals.end());
    
    // We track the end time of each meeting room to know when the meeting would be over.
    // This vector would store the end time of each meeting room required. Insert the first one.
    vector<int> rooms;
    rooms.push_back(intervals[0][1]);

    // Go through all the intervals from 1 to n.
    for(int i=1;i<intervals.size();i++){
      // This flag would tell us whether we would require a now meeting room for interval[i] or update an existing one.
      int flag = 0;

      // Iterate over all the meeting rooms looking for a room where the meeting completed and 
      // meeting interval[i] can happen there. 
      // If there is any such room, we update the meeting room timings to end at interval[i][1] and break.
      // If there is no such room, we insert interval[i][1] to rooms list since a new meeting room is required now.

      for(int j=0;j<rooms.size();j++){
        if(intervals[i][0] >= rooms[j]){
          rooms[j] = intervals[i][1];
          flag = 1;
          break;
        }
      }
      if (flag == 0)
        rooms.push_back(intervals[i][1]);
    }
    
    // Return the size of rooms as this would tell us the no. of meeting rooms required.
    return rooms.size();
  }
};

class Solution2 {
public:
  int minMeetingRooms(vector<vector<int>>& intervals) {
    // If <=1 intervals, then interval size is min num of meeting rooms.
    if (intervals.size() <=1)
      return intervals.size();

    // Sort the intervals on their starting time
    sort(intervals.begin(), intervals.end());

    // We track the end time of each meeting room to know when the meeting would be over.
    // This PQ would store the end time of each meeting room required. Insert the first one. 
    // PQ would help us search for a vacant meeting room in O(logN) time instead of a vector in O(n) time.
    priority_queue<int, vector<int>, std::greater<int>> pq;

    pq.push(intervals[0][1]);
    
    // Go through all the intervals from 1 to n.
    for(int i=1;i<intervals.size();i++){

      // If our meeting time is later than the latest meeting completing time, we remove that meeting from the list since the new one will be pushed anyway below.
      if(intervals[i][0] >= pq.top())
            pq.pop();

      // We push the new meeting in the PQ (so it's removing+inserting when above cond satified or just inserting since a new meeting room is reqd.) 
      pq.push(intervals[i][1]);

    }
    // Returning pq.size() will be fine instead of counting the max everytime since it remains the max size till the end.
    // We only pop iff there is a meeting room required in next interval, otherwise even vacant rooms lies in the queue which will happen in the end.
    return pq.size(); 
  }
};


int main() {
  Solution1 s;
  Solution2 s2;
  vector<vector<int>> v = {{0, 30},{5, 10},{15, 20}};
  cout<<s.minMeetingRooms(v)<<endl;
  cout<<s2.minMeetingRooms(v)<<endl;
}


// -----------------
// LEETCODE SOLUTION
// -----------------


class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        if (intervals.size() <=1)
            return intervals.size();

        sort(intervals.begin(), intervals.end());

        // min heap
        priority_queue<int, vector<int>, std::greater<int>> pq;
        pq.push(intervals[0][1]);

        for(int i=1;i<intervals.size();i++){
            if(intervals[i][0] >= pq.top())
                pq.pop();
            pq.push(intervals[i][1]);
        }
        return pq.size();
    }
};