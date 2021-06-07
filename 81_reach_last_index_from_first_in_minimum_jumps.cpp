
/*

Harshit Gupta | 11th May, 2021
---------------------------------

C++ program for

Given an array of non-negative integers nums, you are initially positioned at the first index of the array.
Each element in the array represents your maximum jump length at that position.
Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. 
	Jump 1 step from index 0 to 1, then 3 steps to the last index.

https://leetcode.com/problems/jump-game-ii/
https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/submissions/
https://leetcode.com/problems/video-stitching/

------

Solution: This can be solved by BFS or DP

	1. BFS: Since we want to get to the last index in MINIMUM number fo steps, BFS comes to mind.
		- Save the index and value in a queue and lkeep on inserting the pair<i, arr[i]> which are reachable.
		- Check if it is the last index then return num of moves
		- Have a visited[] array so that you do not traverse a node more than once.

Time Complexity: O(n)
Space Complexity: O(n)

	2. DP: Create a DP array and fill it with a large number (n+1 if n is the last index, we will save indexes so n+1 is a safe large index!)
		- dp[i] will store the minimum number of steps to reach dp[i]
		- dp[0] = 0 since you are already standing at 0 index.
		- [GIVEN] For each index the arr[i] will tell you the maximum num of steps you can take
		- Loop for 'i' from 0 till n
			- Loop 'j' from start = i till end = i+arr[i] (These are all jumpable from index i)
			- dp[j] = minimum of 
				however you can reach j till now (dp[j]),
				however you can reach 'start' + 1 step (dp[start] + 1)

Time Complexity: O(n2)
Space Complexity: O(n)
---
  NOTE: 
*/



class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n==1)
            return 0;
        int jump = 0;
        
        // BFS SOLUTION
        // ------------
        // queue<pair<int,int>> q;
        // vector<int>visited(n, 0);
        // q.push(make_pair(0,nums[0]));
        // visited[0] =1;
        // while(!q.empty()){
        //     int size=q.size();
        //     for(int i=0;i<size;i++){
        //         pair<int, int> f = q.front();
        //         q.pop();
        //         for(int i=f.first+1;i<=f.first+f.second; i++){
        //             if(i==n-1)
        //                 return jump+1;
        //             if (visited[i] == 0){
        //                 q.push(make_pair(i, nums[i]));
        //                 visited[i] = 1;
        //             }
        //         }
        //     }
        //     jump++;
        // }
        // return jump;
     

     	// DP SOLUTION
        int len = nums.size();
		int dp[len];
        cout<<len<<endl;
		dp[0] = 0;

		// Initialize it to len+1
        for (int i = 1; i < len; i++) {
            dp[i] =len+1;
        }
        
		for (int i = 0; i < len; i++) {
			int start = i;
			int end = min(i + nums[i], len - 1);
            
			for (int j = start; j <= end; j++) {
				dp[j] = min(dp[j], dp[start] + 1);
			}
            // for (int k = 0; k < len; k++) { cout<<dp[k]<<" ";}
            // cout<<endl;
		}
        
        // for (int k = 0; k < len; k++) { cout<<dp[k]<<" "; }
        // cout<<endl;

		return dp[len - 1] == len + 1 ? -1 : dp[len - 1];
        
    }
};