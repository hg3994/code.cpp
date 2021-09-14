/*

Harshit Gupta | 1st July, 2021
---------------------------------

C++ program for "Largest Moutain"

You may recall that an array arr is a mountain array if and only if:
    1. arr.length >= 3
    2. There exists some index i (0-indexed) with 0 < i < arr.length - 1 such that:
        arr[0] < arr[1] < ... < arr[i - 1] < arr[i]
        arr[i] > arr[i + 1] > ... > arr[arr.length - 1]

Given an integer array arr, return the length of the longest subarray, which is a mountain. 
Return 0 if there is no mountain subarray.

------

Solution: 1. Start with a base and check if you have a mountain ahead of you.
    2. To check for a mountain, you must travel upwards to reach a peak
    3. Then travel downwards.
    4. The length of a montain would be (end-start+1)
    5. Get the largest mountain.

TC: O(n)
SC: O(1)

Paradigm: Two Pointers
---
  NOTE: #Agoda

*/


class Solution {
public:
    int longestMountain(vector<int>& arr) {
        int base=0, N=arr.size();
        int ans=0;
        
        // Till we reach the end of the mountain
        while(base < N) {
            // Start end with the base and try to keep growing it
            end = base;
            
            // we do NOT want the flow to reach the next if loop of travelling 
            // down the mountain without travelling up so we need this condition
            if(end+1 < N && arr[end]<arr[end+1]){
                
                // travelling upwards to reach the peak of the mountain
                while(end+1 < N && arr[end]<arr[end+1])
                    end++;

                // we want to update the ans only when we have travelled to the 
                // end of the mountain, so we need this if condition check
                if(end+1<N && arr[end]>arr[end+1]) {
                    
                    // travelling downwards to reach the end of the mountain
                    while(end+1<N && arr[end]>arr[end+1])
                        end++;
                    
                    // Now we have reached the bottom of the mountain
                    // Check if this is the largest mountain we have?
                    ans = max(ans, end-base+1);
                }
            }
            
            // If there was a mountian, update base to the end of it.. to search for a new mountain
            // Otherwise increase base by 1 and check.
            base = max(end, base+1);
        }
        return ans;
    }
};