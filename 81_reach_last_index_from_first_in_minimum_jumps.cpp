
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


------

Solution: This can be solved by BFS or DP

    1. Greedy: Imagine that you are at index i in the array, the element in your current position 
        defines the maximum distance that you can jump. Therefore, your next step will fall somewhere 
        in the range [start, end], where start is the place right next to you and end is i + nums[i]. 
        Then the question is, where to jump?
        Our next move will fall somewhere between [start : end] and to find the minimum number of jumps 
        to reach the end of the array, we must determine which place will take us the farthest in the next jump.
        - We use a variable currEnd which tells us about the end of the current Jump
        - We use a variable currFarthest which tells us about the farthest jump I can make till now.
        - Iterate over the array & keep keep calculating the farthest jump you can make
            - Once you reach the currEnd, it means that this was all you can travel without any jumps
                but you know that you can take a jump and reach till the currFarthest point.
            - So if you reach the currEnd, you take that jump (so jump++) and now your currEnd will
                become your currentFarthest since you can travel till that point without any jumps
            - You keep calculating the new currentFarthest now and once reach the currEnd again
                you take another jump till the new currentFarthest and this goes on till you reach the end
        - We see that we take a greedy approach to always delay the jump and know the max we can reach without
            any jumps by using currentFarthest

    If the questions says that you can always assume that we can reach the last index.
    If this was not said, then have to introduce another condition in the for loop which would be:
         i < n-1 && i <= currentFarthest
    This would check if our i goes beyond the currFarthest then it means that the last index can never
    be reached


    Time Complexity: O(n)
    Space Complexity: O(1)  

	2. BFS: Since we want to get to the last index in MINIMUM number fo steps, BFS comes to mind.
		- Save the index and value in a queue and keep on inserting the pair<i, arr[i]> which are reachable.
		- Check if it is the last index then return num of moves
		- Have a visited[] array so that you do not traverse a node more than once.

    Time Complexity: O(n)
    Space Complexity: O(n)

	3. DP: Create a DP array and fill it with a large number (n+1 if n is the last index, we will save indexes so n+1 is a safe large index!)
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

Similar Questions:
    1. https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/
        - Similar question but the ranges given can go to negative and so we need to recontruct the array
            and then it will a the similar problem
        - Here the we may/maynot reach the asnwer, so need the extra condition i <= currFarthest

    2. https://leetcode.com/problems/video-stitching/
        - Similar question. Again the input format is a bit different so we need to reconstruct it
            in the form of jumps and then apply the same thing.
        - Here the we may/maynot reach the asnwer, so need the extra condition i <= currFarthest


---
  NOTE: 
*/

// ------------------
// Approach 1: Greedy
// ------------------
class Solution {
public:
    int jump(vector<int>& nums) {
        int n=nums.size(), currEnd=0, currFarthest=0, jumps=0;
        // NOTE that the loop runs for i<n-1 because we have to use at max n-1 jumps to reach nth index
        for(int i=0; i<n-1;i++) {
            currFarthest = max(currFarthest, i+nums[i]);
            if (i == currEnd){
                jumps++;
                currEnd = currFarthest;
                if(currEnd >= n-1)
                    break;
            }
        }
        return jumps;
    }
};

// ------------------------
// Approach 2: BFS SOLUTION
// ------------------------
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n==1)
            return 0;
        int jump = 0;
        
        queue<pair<int,int>> q;
        vector<int>visited(n, 0);
        q.push(make_pair(0,nums[0]));
        visited[0] =1;

        while(!q.empty()){
            int size=q.size();

            for(int i=0;i<size;i++){
                pair<int, int> f = q.front();
                q.pop();
                for(int i=f.first+1;i<=f.first+f.second; i++){
                    if(i==n-1)
                        return jump+1;
                    if (visited[i] == 0){
                        q.push(make_pair(i, nums[i]));
                        visited[i] = 1;
                    }
                }
            }
            jump++;
        }
        return jump;
    }
};




// ------------------------
// Approach 3: DP SOLUTION
// ------------------------
class Solution {
public:
    int jump(vector<int>& nums) {
        int n = nums.size();
        if (n==1)
            return 0;
        int jump = 0;

        int len = nums.size();
        int dp[len];
        dp[0] = 0;

        // Initialize it to len+1
        for (int i = 1; i < len; i++) {
            dp[i] =len+1;
        }
        
        for (int i = 0; i < len; i++) {
            int start = i;
            int end = min(i + nums[i], len - 1);
            
            for (int j = start; j <= end; j++) {
                dp[j] = min(dp[j], dp[start] + 1); // jump from start till here so dp[start]+1
            }
        }

        return dp[len - 1] == len + 1 ? -1 : dp[len - 1];
        
    }
};

// ------------------
// SIMILAR QUESTION 1
// ------------------

// The question can be converted into the form of Jump Game II.

// 1. The range each tap covers is: max(0, i-ranges[i]) (say l) to min(n, i+ranges[i]) (say r). 
//      Think of this range as a jump starting from the index max(0,i-ranges[i]) with maximum 
//      reach till min(n, i+ranges[i]) - max(0, i-ranges[i]).
// 2. To do this, we define a new array jumps where jumps[l] = max(jumps[l], r-l). 
//      Now our problem boils down to calculating the minimum number of jumps required to reach 
//      the end of array.
// 3. The main idea is based on greedy. Let's say the range of the current jump is [curBegin, curEnd], 
//      curFarthest is the farthest point that all points in [curBegin, curEnd] can reach. Once the 
//      current point reaches curEnd, then trigger another jump, and set the new curEnd with curFarthest, 
//      then keep the above steps.

// Time complexity: O(n)
// Space complexity: O(n)

// 5, arr: [3,4,1,1,0,0]
// jump[l]: 0 r-l: 3
// jump[l]: 3 r-l: 5
// jump[l]: 0 r-l: 2
// jump[l]: 0 r-l: 2
// jump[l]: 0 r-l: 0
// jump[l]: 0 r-l: 0
// jump: 5 2 2 0 0 0 
// If you do not understand this, read the first point again!!

int minTaps(int n, vector<int>& ranges) {
    vector<int> jumps(n+1, 0);
    
    for (int i=0; i<ranges.size(); i++) {
        int l = max(0, i-ranges[i]);
        int r = min(n, i+ranges[i]);
        // jump can be made from l to r-l distance
        jumps[l] = max(jumps[l], r-l);
    }
    
    // for (auto i : jumps)
    //     cout<<i<<" ";
    // cout<<endl;
    
    // See Jump Game II
    int count = 0, curEnd = 0, curFarthest = 0;
    for (int i = 0; i<jumps.size()-1; i++) {
        if (i>curFarthest)
            return -1;
        
        curFarthest = max(curFarthest, i + jumps[i]);
        
        if (i == curEnd) {
            count++;
            curEnd = curFarthest;
        }
    }
    
    return curFarthest >= n ? count : -1;
}


// Approach 2: DP
// TC: O(n2)
// SC: O(n2)
class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        //dp[i] is minimum number of taps required for the range [0,i]
        int dp[n+1]; 
        for(int i=0;i<n+1; i++){
            dp[i] = n+2;
        }
        dp[0] = 0;
        
        for(int i=0;i<n+1;i++){
            int start = max(0, i-ranges[i]);
            int end = min(n, i+ranges[i]);
            for(int j=start; j<=end; j++){
                dp[j] = min(dp[j], dp[start]+1);
            }
        }
        
        // for(int i=0;i<n+1; i++){
        //     cout<<dp[i]<<" ";
        // }
        // cout<<endl;
        
        return dp[n] == n+2 ? -1 : dp[n];
    }
};


//------------------------------------
// SIMILAR QUESTION 2: VIDEO STITCHING
//------------------------------------

class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T) {
        vector<int> arr(T+1, 0);
        // Convert the clips in the form which tells the length of the clip from posn i
        // Then we just need to select minimum clips to reach T+1
        for(auto c: clips){
            if(c[0] < T+1)
                arr[c[0]] = max(arr[c[0]], c[1]-c[0]);
        }
        
        // for(auto j: arr)
        //     cout<<j<<" ";
        // cout<<endl;
        
        int currEnd=0, currFarthest=0, jumps=0;
        for(int i=0; i<T && i<=currFarthest; i++){
            currFarthest = max(currFarthest, i+arr[i]);
            if(i == currEnd){
                jumps++;
                currEnd = currFarthest;
                if(currEnd >= T)
                    break;
            }
        }
        return currFarthest<T ? -1 : jumps;
    }
};
