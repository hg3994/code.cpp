/*

Harshit Gupta | 11th October, 2020
-----------------------------------

C++ program for "Some intervals are given. You have to find the minimum number of intervals that will
cover all the intervals."

Better problem statement here: 
https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/

------

Solution: Very good question! Keep minimum number of intervals required in the ans vector.
  Iterate over all other intervals and try to update the ans vector.
  When trying to include a interval in the last interval I saw, there can only be 3 cases:

    Case 1. Interescting overlapping intervals:
        I--------I
              I------I     
    --------------------
    >>        I--I
    We update the ans.back() with intersecting area since an array here would hit them both.


    Case 2. Intersecting included intervals:
        I--------I
           I--I
    ------------------
    >>     I--I
    We update the ans.back() with intersecting area since an array here would hit them both.


    Case 3. Nonintersecting intervals:
        I--------I
                    I--------I
     ------------------------------
    >>  I--------I  I--------I
    We push another interval in ans() since there needs to be 2 arrows now to hit them both.
    
    There will never be a 4th case that the start of j is lesser than ans.back() since they are sorted.

---
  NOTE: 
      - We can also keep a pair<int, int> and keep on updating a variable 'ans' with archived intervals
      since vector<pair> isn't really required. We only need to check for the last pair in the vector.
      - We have implmented a different kind of sort() here with a comparator with lambda function.

---
  Time Complexity: O(NlogN) since we used sort.
  Space Complexity: 

  Paradigm: Intervals

*/

class Solution {
public:
  int findMinArrowShots(vector<vector<int>>& p) {
    
    // 0 arrows for 0 balloon, 1 arrow for 1 balloon.
    if (p.size() <= 1)
      return p.size();
    
    // Sort the intervals on their starting x and then on ending x.
    // sort(p.begin(), p.end());
    // This would also do but my own comparator is faster ;)
    sort(p.begin(), p.end(),
      [](const std::vector<int>& a, const std::vector<int>& b) {
      if(a[0]==b[0]) 
        return a[1] < b[1];
      else
        return a[0] < b[0];
    });
    
    int j=1;
    // This vector of intervals would store the minimum number of intervals which would be hit by an arrow
    vector<pair<int, int>> ans;
    // Start with the pushing the first interval in the vector, we will keep updating as required.
    ans.push_back(make_pair(p[0][0], p[0][1]));
  
    while(j<p.size()){
      
      int ans_back = ans.back().second;
      int j_start = p[j][0];
      int j_end = p[j][1];
      
      // Case 1
      if(j_start <= ans_back && j_end > ans_back){
        ans.pop_back();
        ans.push_back(make_pair(j_start, ans_back));
      }
      // Case 2
      else if (j_start <= ans_back && j_end <= ans_back){
        ans.pop_back();
        ans.push_back(make_pair(j_start, j_end));
      }
      // Case 3
      else {
        ans.push_back(make_pair(j_start, j_end));
      }
      
      j++;
    }
    
    return ans.size();
  }
};