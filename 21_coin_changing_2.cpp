/* 
Harshit Gupta | 22nd October, 2018

http://www.cpp.sh/6mize
https://www.geeksforgeeks.org/subset-sum-problem-dp-25/
https://leetcode.com/problems/partition-equal-subset-sum/

C++ program for " There a n coins present. We want to make a sum s from these coins. Can we make it?"

Solution: We will use DP to solve this. At every stage, we have two choices:
        a. we are NOT considering the nth coin (dp[i-1][j])
        b. we are considering the nth coin (dp[i-1][j-coins[i-1]])
        NOTE that if sum amount is less than the coin value, then we have the only choice of NOT considering that coin.
        Base cases would be when sum=0 and coins are present(we can always make then) and when coins=0 and sum is present (we can never make)
        We will build the dp[][] table with help of these cases.
        
        This is different from the the coin changing problem because here we DO NOT have infinte supply of coins. 
        The only coins that we have are the ones in the array


Similar Questions: This question can also be framed as 

    1. There is an array of numbers given with a sum. Can you choose some elements from the array 
        which will add up to 'sum'." You can think of these numbers as coins
        and then make 'sum' amount from the coins.

    2. Given a non-empty array nums containing only positive integers, find if the array can be 
        partitioned into two subsets such that the sum of elements in both subsets is equal.
        - The sum for this question would be sum of array / 2 and the rest remains the same.
        - If the sum is odd, we can never do it.
        - If we can choose some numbers and have their sum = sumOfArray/2, then it means that the remaining
            array will have the sum= sumOfArray/2 as well so we just need to check some of the numbers can
            be added to form sumOfArray/2 and the rest would be fine.
        

Time Complexity: O(n2)
Space Complexity: O(n2) but can be reduced to O(n). See, solution for variant #2 below.

Paradigm: Dynamic Programming

*/

#include <bits/stdc++.h>
using namespace std; 

void coinsChanging(int *coins, int n, int sum){
    int dp[n+1][sum+1];
    
    // When the number of coins are 0 and sum is 0, then the number of ways
    // we can make it is 1.
    dp[0][0] = 1;
    
    // When the sum is 0, there is 1 way to get the number of coins.
    for(int i=0;i<n+1; ++i)
        dp[i][0] = 1;
        
    // When the coins are 0, there are 0 ways to make them (except when sum is also 0, then there is 1 way.)
    for(int i=1;i<sum+1;i++)
        dp[0][i] = 0;
        
    // Iterate over to fill the 2D array.
    // A sum is possible only if 
    // a. we are NOT considering the nth coin (dp[i-1][j])
    // b. we are considering the nth coin (dp[i-1][j-coins[i-1]])
    // NOTE that if sum amount is less than the coin value, then we have the only choice of NOT considering that coin.
    for(int i=1;i<n+1;i++){
        for(int j=1;j<sum+1;j++){
            if(j<coins[i-1])
                dp[i][j] = dp[i-1][j];
            else
                // The || here is to say if that specific sum(j) is already made in prev row, 
                // then don't calculate, just say it is already made by placing a 1 as in prev row i-1 and col j.
                // If it is not already made, then calculate if it can be made by dp[i-1][j-coins[i-1]]
                dp[i][j] = dp[i-1][j] || dp[i-1][j-coins[i-1]]; 
        }
    }
    
    // Uncomment to print the 2D matrix
    for (int i = 0; i <= n; i++) 
     { 
      for (int j = 0; j <= sum; j++) 
          printf ("%4d", dp[i][j]); 
      printf("\n"); 
     }
    
    if (dp[n][sum]==1)
        cout<<"It is possible to make a sum of these coins"<<endl;
    else
        cout<<"It is NOT possible to make a sum of these coins"<<endl;
}


int main(){
    int coins[] = {3, 34, 4, 12, 5, 2}; 
    int sum = 9; 
    // int sum = 1; //not possible 
    int n = sizeof(coins)/sizeof(coins[0]); 
    coinsChanging(coins, n, sum);
    return 0;
}

// ------------------------------
// # LEETCODE VARIANT #2 Solution
// ------------------------------

// Solution 3: TC: O(n2), SC: O(n)
class Solution {
public:
    
    bool canPartition(vector<int>& nums) {
        int sum=0, n=nums.size();
        for(auto num: nums)
            sum += num;
        
        if(sum%2 == 1)
            return false;
        sum /= 2;
        
        vector<bool> dp(sum+1, false);
        
        dp[0] = true;
        
        for(auto num: nums){
            // See that we are iterating from sum till 0 so that we do not take get 
            // fake 1s which were 0s in the last iteration (we are accessing backwards: dp[j-num])
            for(int j= sum; j>=0; j--){
                if(j >= num)
                    dp[j] = dp[j] || dp[j-num];
            }
        }
        return dp[sum];
    }
};


// Approach 2: TC: O(n2) SC: O(n2)

class Solution {
public:
    
    bool canPartition(vector<int>& nums) {
        int sum=0, n=nums.size();
        for(auto num: nums)
            sum += num;
        
        if(sum%2 == 1)
            return false;
        sum /= 2;
        
        vector<bool> t(sum+1, false);
        vector<vector<bool>> dp(n+1, t); // dp[n+1][sum+1]
        
        for(int i=0;i<=n;i++)
            dp[i][0] = true;
        
        for(int j=1;j<=sum;j++)
            dp[0][j] = false;
        
        for(int i=1;i<=n; i++){
            for(int j=1; j<=sum; j++){
                if(j < nums[i-1])
                    dp[i][j] = dp[i-1][j];
                else {
                    dp[i][j] = dp[i-1][j] || dp[i-1][j-nums[i-1]];
                }
            }
        }
        return dp[n][sum];
    }
};



// Approach 1: Recursive Solution: Gives TLE.
bool helper(vector<int> nums, int i, int s1, int s2){
    if(i == nums.size()) {
        if(s1 == s2) return true;
        else return false;
    }

    return helper(nums, i+1, s1+nums[i], s2) || helper(nums, i+1, s1, s2+nums[i]);
}

bool canPartition(vector<int>& nums) {
    return helper(nums, 0, 0, 0);
}