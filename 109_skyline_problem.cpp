
/*

Harshit Gupta | 9th June, 2021
---------------------------------

C++ program for "SKYLINE Problem"
https://leetcode.com/problems/the-skyline-problem/

Must Watch: https://www.youtube.com/watch?v=GSBLe8cKu0s&t=861s
------

Solution: 
    1. The input array of buildings [X,Y,Height] is converted points for starting and ending of each building [X, Height, Start] & [Y, Height, End]
    2. The array of building points is sorted so that they are in the expected correct input format.
    3. We use a map for storing the height and the frequency of each building
    4. We iterate over each point in the vector
        - If it is an starting point, then increase its frequency in the map
        - If it is an ending point, then decrease its frequency in the map
        - Check for the maximum height present in the map (which will be the last element since map is always sorted),
        - Compare it with the prevMaxHeight in the map (this will tell us weather adding/deleting the current point's height in the map changed something?)
            - No change in the height will mean that this point is not really important from output perspective
            - Adding a new point and currentHeight increases means a new building is coming in process
            - Removing a point and currentHeight decreases means a new building is done processing now
            - In any case of increase/decrease, the point is important and will be added in output, so add the X, Y in the ans vector


Time Complexity: O(nlogn)
Space Complexity: O(n)

Paradigm: Map
---
  NOTE: 

*/


// This class is for the building points with which we can represent a building
class BuildingPoint {
public:
    int x; // X axis distance
    bool isStart; // Is this the start of a building or the end?
    int height; // Height of the building
    
    bool operator<(const BuildingPoint &b) const
    {
        if (x != b.x) 
            return x < b.x;
        else {
            // Edge cases ...
            // If two starts are compared, higher height building should be picked up first
            // If two ends are compared, lower height building should be picked up first
            // If one start and one end is compared, start should appear before end
            if (isStart && b.isStart) 
                return height > b.height;
            else if (!isStart && !b.isStart)
                return height < b.height;
            else
                return isStart > b.isStart;
        }
    }
};

class Solution {
public:
    
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        // To store the answer
        vector<vector<int>> ans;
        
        // This vector will store the converted points
        // Each building from the inputs is represented by two points: Start and End
        // [X, Y, Height] in input array gets converted to  [X, Height, isStartPoint] and [Y, Height, isEndPoint]
        // [1,3,4] in input array gets converted to [1 4 1][3 4 0]
        vector<BuildingPoint> buildingPointVector;
        
        // Fill up the buildingPointVector of length (buildings.size() * 2)
        // Twice size since for each element of buildings, two elements are inserted (one for start and one for end)
        for(auto building: buildings) {
            BuildingPoint bp1, bp2;
            
            bp1.x = building[0];
            bp1.height = building[2];
            bp1.isStart = true;
            
            bp2.x = building[1];
            bp2.height = building[2];
            bp2.isStart = false;
            
            buildingPointVector.push_back(bp1);
            buildingPointVector.push_back(bp2);
        }
        
        // Sort the vector on the basis of the rules written in the comparator < function
        // This is very important mainly because the solution depends heavily on this sorted output so please read & understand the operator < func.
        sort(buildingPointVector.begin(), buildingPointVector.end());
        
        // for(auto bp: buildingPointVector){
        //     cout<<bp.x<<" "<<bp.height<<" "<<bp.isStart<<endl;
        // }
        
        // Create a map. Using it since it has O(logN) insertion time, O(logN) deletion time, O(1) maximum element time.
        // We will store the height of the building here with the frequency of the height
        map<int, int> mp;
        // Insert the element 0 since that is the max that we have for now.
        mp.insert({0,1});
        
        int prevMaxHeight = 0;
        
        // Iterate over the sorted vector of points
        for(auto bp: buildingPointVector){
            // If this is a 'starting point'
            if(bp.isStart){
                // Increase the frequency count of that height from the map (insert if required)
                if(mp.count(bp.height))
                    mp[bp.height]++;
                else
                    mp[bp.height] = 1;
            }
            // If this is a 'ending point'
            else{
                // Decrease the frequency count of that height from the map (delete if required)
                if(mp[bp.height] == 1)
                    mp.erase(bp.height);
                else
                    mp[bp.height]--;
            }
            
            // Get the maximum height from the map. That would be the last element of the map.
            int currentMaxHeight = prev(mp.end())->first;
            
            // After the insertion/deletion in the map, 
            // if the currentMaxHeight still remains the same as prevMaxHeight then no changes are needed
            // else this currentMaxHeight is an important point and will be seen in the skyline so add it in the ans vector
            if(prevMaxHeight != currentMaxHeight){
                // adding the X axis coordinate and currentMaxHeight which would be the Y coordinate
                ans.push_back({bp.x, currentMaxHeight});
                prevMaxHeight = currentMaxHeight;
            }
        }
        
        return ans;
    }
};






