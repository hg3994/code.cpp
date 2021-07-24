/*

Harshit Gupta | 26th September, 2020
-------------------------------------

Ruby program for "Given n non negative integers, each representing a bar, 
  choose 2 lines so that if water is poured, then it contains the maximum water in the container "

https://leetcode.com/problems/container-with-most-water/

Input: [1,8,6,2,5,4,8,3,7]
Output: 49
------

Solution: 
  There's obviously the naive way of doing such thing in O(n2) time by 
    - comparing each bar to one another
    - get the minimum of the two bars and the distance between them
    - the water stored = min (two bars)*distance btw them

  But then there's an optimal solution to this problem in faster time 
  Idea is to keep maximizing the water by reducing the width but by choosing a larger bar
  We start with the widest container but will achieve one with max water by making bars closer
  Algo:
    - Have a left pointer which would be the left side of the vessel
    - Have a right pointer which would be the right side of the vessel
    - Get the amount of water it can store
    - To maximize the water, compare the bars
    - Move the left pointer + 1 if that is smaller
    - Move the right pointer to - 1 if that is smaller

Time Complexity: O(n)
Space Complexity: O(1)

https://repl.it/repls/SilentFamousCodegeneration

*/


class Solution {
public:
    int maxArea(vector<int>& arr) {
        int n = arr.size();
        int left=0, right=n-1;
        int maxWater=0;
        while(left<right){
            int area = min(arr[left], arr[right])*(right-left);
            maxWater = max(area, maxWater);
            if(arr[left] < arr[right])
                left++;
            else
                right--;
        }
        return maxWater;
    }
};