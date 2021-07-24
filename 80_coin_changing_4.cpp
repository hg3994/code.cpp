
/*

Harshit Gupta | 9th May, 2021
---------------------------------

C++ program for
	You are given an integer array coins representing coins of different 
	denominations (infinite) and an integer amount representing a total amount of money.
	Return the "fewest number of coins that you need to make up that amount" .
	If that amount of money cannot be made up by any combination of the coins, return -1.

	https://leetcode.com/problems/coin-change/

	Input: coins = [1,2,5], amount = 11
	Output: 3
	Explanation: 11 = 5 + 5 + 1

    //   | 0 1 2 3 4 5 6 7 8 9 10 11 (amount)
    // ------------------------------
    // 1 | 0 1 2 3 4 5 6 7 8 9 10 11
    // 2 | 0 1 1 2 2 3 3 4 4 5  5  6
    // 5 | 0 1 1 2 2 1 2 2 3 3  2  3

    //   | 0 1 2 3 4 5 6 7 8 9 10 11 (amount)
    // -----------------------------
    // 2 | 0 0 1 0 2 0 3 0 4 0  5  0
    // 5 | 0 0 1 0 2 1 3 2 4 3  2  4
------

Solution: DP.

	1. To get to an amount X with coin C, we can get number of ways to reach to reach X by
		"Number of ways to reach (X-C)" + 1 way.
		- 1 id added since another coin of C denomination can be added to reach X.
	2. Another way to reach amount X with coin C would be to not select the coin C 
		and use only the coins before C. This means "Number of ways to reach (X) without C"
	3. Minimum of these two would be the way in which we require fewest coins to reach X.
		dp[i][j] = min(dp[i][j-coins[i]]+1, dp[i-1][j]);


Time Complexity: O(n2)
Space Complexity: O(n2)
---
  NOTE: 

*/


// LC Solution below using 1D array only:
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        vector<long long int> dp(amount+1, INT_MAX);
        dp[0] = 0;
        
        for(long long int i=0; i<coins.size(); i++){
            for(long long int j=0; j<amount+1; j++){
                if(j>=coins[i])
                    dp[j] = min(dp[j], dp[j-coins[i]]+1);
            }
        }
        return dp[amount] == INT_MAX ? -1 : dp[amount];
    }
};


// class Solution {  
// public:
//     int coinChange(vector<int>& coins, int amount) {
//         // Get coins in sorted order
//         sort(coins.begin(), coins.end());
//         if(amount == 0)
//             return 0;
//         int n = coins.size();
//         int dp[n][amount+1];
//         // If amount is 0, there are 0 ways to reach it.
//         for(int i=0;i<n;i++){
//             dp[i][0] = 0;
//         }
        
//         for(int i=0; i<n; i++){
//             for(int j=1;j<amount+1; j++){
//             	// If amount < coin value, then this coin can not be used for this amount
//             	// so taking the value from above.
//                 if (j < coins[i]){
//                     if(i==0)
//                         dp[i][j] = 0;
//                     else
//                         dp[i][j] = dp[i-1][j];
//                 }
//                 // If an amount is a multiple of a coin, then X coins of that specific coin is 
// 				// the shortest way to reach that amount.
//                 else if(j%coins[i] == 0){
//                     dp[i][j] = j/coins[i];
//                 }
//                 else {
//                     if (i == 0){
//                         if (dp[i][j-coins[i]] == 0)
//                             dp[i][j] = dp[i][j-coins[i]];
//                         else
//                             dp[i][j] = dp[i][j-coins[i]]+1;
//                     }
//                     else{

//                         if(dp[i][j-coins[i]] == 0){
//                             dp[i][j] = dp[i-1][j];
//                         }
//                         else if (dp[i-1][j] == 0){
//                             dp[i][j] = dp[i][j-coins[i]]+1;
//                         }
//                         else{
//                         	// MAIN DP FORMULAE 
//                         	// (everything else is for either 0th row or if there are 0 ways to 
//                         	// reach then we can not use that value and min func can not catch that)
//                             dp[i][j] = min(dp[i][j-coins[i]]+1, dp[i-1][j]);
//                         }
//                     }
//                 }
                
//             }
//         }
        
//         // PRINT THE DP[][] array.
//         // for(int i=0; i<n; i++){
//         //     for(int j=0;j<amount+1; j++){
//         //         cout<<dp[i][j]<<" ";
//         //     }
//         //     cout<<endl;
//         // }

//         if (dp[n-1][amount] == 0)
//             return -1;
//         else
//             return dp[n-1][amount];
//     }
// };

