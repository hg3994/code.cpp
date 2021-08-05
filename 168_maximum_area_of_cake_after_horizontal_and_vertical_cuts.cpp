/*

Harshit Gupta | 5th August, 2021
---------------------------------

Problem Statement:
You are given a rectangular cake of size h x w and two arrays of integers horizontalCuts and verticalCuts where:
	horizontalCuts[i] is the distance from the top of the rectangular cake to the ith horizontal cut and similarly,
	verticalCuts[j] is the distance from the left of the rectangular cake to the jth vertical cut.
	Return the maximum area of a piece of cake after you cut at each horizontal and vertical position provided in the 
	arrays horizontalCuts and verticalCuts. Since the answer can be a large number, return this modulo 10^9 + 7.


------

Solution: 
    Max Area is possible when we choose the max height and max width
    Max Width and Max Height can easily be calculated by sorting the cuts and then finding the difference 
         between this cut and the prior cut and then choosing the max.
    The key observation in this problem is the fact that
    - Max Height is given by the Horizontal Cuts
    - Max Width is given by the Vertical Cuts
    - Max Height and Max Width are independent and chossing both max values will actually give us the max area:
         Max Height is valid for all the vertical cuts. If you move the vertical cuts left and right, the max
         height will be constant & valid & we are just choosing an area from the rectangle Max height X Total Width
         Out of total width, if we choose the max width, we get the max area from the above rectangle which is 
         what we want.

    TC: O(nlogn + mlogm) for sorting
    SC: O(1)

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


class Solution {
    
    
    
public:
    int maxArea(int h, int w, vector<int>& horizontalCuts, vector<int>& verticalCuts) {
        // Sort the vecctors so that we can easily calculate the max width & height
        sort(verticalCuts.begin(), verticalCuts.end());
        sort(horizontalCuts.begin(), horizontalCuts.end());
        
        int max_width = verticalCuts[0];
        int max_height = horizontalCuts[0];
        
        // Calculate the max width and max height
        for(int i=1;i<verticalCuts.size(); i++){
            max_width = max(max_width, verticalCuts[i]-verticalCuts[i-1]);
        }
        // The for loop spares the part of cake which is between last cut & end of cake so considering that as well
        max_width = max(max_width,w-verticalCuts.back());
        max_width = max_width%1000000007;
        
        // Doing the same thing for max_height as well
        for(int i=1;i<horizontalCuts.size(); i++){
            max_height = max(max_height, horizontalCuts[i]-horizontalCuts[i-1]);
        }
        max_height = max(max_height, h- horizontalCuts.back());
        max_height = max_height%1000000007;
        
        // Give the area. Multiplying both variable get out of int bound so type cast them to 'long long' & then mod'ng it.
        return ((long long )max_height*(long long)max_width)%1000000007;
        
    }
};