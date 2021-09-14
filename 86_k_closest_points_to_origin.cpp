/*

Harshit Gupta | 22nd May, 2021
---------------------------------

C++ program for "Given an array of points where points[i] = [xi, yi] represents a point on the 
    X-Y plane and an integer k, return the k closest points to the origin (0, 0)."

https://leetcode.com/problems/k-closest-points-to-origin

    Input: points = [[1,3],[-2,2]], k = 1
    Output: [[-2,2]]
    Explanation:
    The distance between (1, 3) and the origin is sqrt(10).
    The distance between (-2, 2) and the origin is sqrt(8).
    Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
    We only want the closest k = 1 points from the origin, so the answer is just [[-2,2]].
------

Solution: 
    1. Calculate the distance of all points from origin and then sort them to find the minimum K points.

Time Complexity: O(nlogn)
Space Complexity: O(n)

    2. Insert Points in a MAX HEAP (Priority Queue) of size K. After processing 
        all elements, the remaining elemnts in the queue are the K closest points.
        - To maintain the size, we must pop the elements when the queue size becomes > k

Time Complexity: O(nlogk)
Space Complexity: O(n)
---
  NOTE: 

*/


// Approach 1: SORTING THE PAIR SOLUTION : O(nlogn)
class Solution {
public:
    
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        int n = points.size();
        if (n == k){
            return points;
        }
        
        // [ {dist1, {x1,y1}}, {dist2, {x2,y2}}]
        vector<pair<int, pair<int, int>>> dist_point;  
        
        // Keep the distance from origin and the coordinates in our data structure
        for(int i=0;i<n;i++){
            int dist = (points[i][0]*points[i][0] + points[i][1]*points[i][1]);
            dist_point.push_back(make_pair(dist, make_pair(points[i][0], points[i][1])));
        }
        
        // Keep the DS on the basis of the 'distance' and we automatically have the coordinates stick to them
        sort(dist_point.begin(), dist_point.end());
        
        vector<vector<int>> ans;
        for(int i=0; i<k; i++){
            vector<int> t;
            t.push_back(dist_point[i].second.first);  // accessing 'x1'
            t.push_back(dist_point[i].second.second); // accessing 'y1'
            ans.push_back(t);
        }
        return ans;
    }
    
};


// Approach 2: PRIORITY QUEUE SOLUTION: O(nlogk)
class Solution {
public:
    
    // Since the size of the queue is k and we always have to maintain a max heap of size K
    // MAX HEAP coz the element greater would be evicted and K min elements are stored
    struct comp {
        bool operator() (pair<int, int>& p1, pair<int, int>& p2) {
            int x1 = p1.first;
            int y1 = p1.second;
            int d1 = x1*x1 + y1*y1;
            
            int x2 = p2.first;
            int y2 = p2.second;
            int d2 = x2*x2 + y2*y2;
            
            return d1 < d2;
        }
    };
    
    vector<vector<int>> kClosest(vector<vector<int>>& points, int k) {
        
        priority_queue<pair<int,int>, vector<pair<int, int>>, comp> pq;
        
        for(auto p: points){
            // Push the point in the PQ
            pq.push({p[0], p[1]});
            // If the size of the PQ becomes > k, then pop one of them
            if (pq.size()>k){
                pq.pop();
            }
        }
        
        vector<vector<int>> res;
        while(!pq.empty()){
            res.push_back({pq.top().first, pq.top().second});
            pq.pop();
        }
        
        return res;
    }
    
};