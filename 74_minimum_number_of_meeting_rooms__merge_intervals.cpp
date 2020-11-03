
/*

Harshit Gupta | 17th October, 2020
----------------------------------

C++ program for "Given an array of meeting time intervals consisting of start and end times 
  [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms required."

https://leetcode.com/problems/meeting-rooms-ii/

------
Very well written solution: https://leetcode.com/problems/meeting-rooms-ii/solution/
https://ideone.com/eMZSll


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

Solution 2: In the previous solution, we iterate over all the present rooms to check whether a room is vacant or not.
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
  3.  For each interval, we want to allocate a meeting room for it. We check whether the top of the queue (latest end time)
    and the start time of the meeting interval[i][0].
    - If our meeting time is later than the latest meeting completing time, we remove that meeting from the list.
  4. We push the new meeting in the PQ and check if this is the maximum.

Time Complexity: O(nlogn)
Space Complexity: O(n) to keep the rooms.

---
  NOTE: 

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

    int max_cnt = 0;

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

      // Check for the maximum num of rooms required.
      max_cnt = max(max_cnt, (int)pq.size());
    }
    return max_cnt;
  }
};


int main() {
  Solution1 s;
  Solution2 s2;
  vector<vector<int>> v = {{0, 30},{5, 10},{15, 20}};
  cout<<s.minMeetingRooms(v)<<endl;
  cout<<s2.minMeetingRooms(v)<<endl;
}