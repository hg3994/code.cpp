/* 
Harshit Gupta | 12th October, 2018

https://www.geeksforgeeks.org/coin-change-dp-7/
https://www.youtube.com/watch?v=jaNZ83Q3QGc
https://leetcode.com/problems/coin-change-2/

C++ program to print the number of ways in which we can make a specific sum from 
from infinite supplies of some specific coins.

Solution:
* Take a combination[] array of size 'sum'. Each number of this array stores the number of ways in which we can make sum as 'index'. 
    So, combination[3] will store the number of ways in which a sum of 3 can be formed from all the coins.

* Iterate over all the coins one by one and try to fill the array. In the first loop, it will be like: I have infinite supply of coins[0]
    so, each of combination[j] would be the number of ways in which the sum 'j' can be made from infinite supplies of 
    only coins[0] denomination of coins. In the second iteration, it will mean that we have infinite amt. of coins[0] and coins[1] and 
    so we will add the answer to this in the prev. array itself.
    
* A coin of value 5 won't make any difference to the number of ways in which a sum of 2 or 3 is formed. So, we take the condition as: j>=coins[i]

* Also, there is always one way of making sum=0 which is to not select anything!

*/

#include <bits/stdc++.h>
using namespace std; 

void coinChanging(int *coins, int n, int sum){

    // This array will store the result of the combination of coins we have to make a specific sum 'i'.
    int combination[sum+1]; 
    
    // Set the array to value 0.
    memset(combination,0, sizeof(combination));
    
    // In how many ways can we make the sum 0 from these coins? You're right. In 1 way. By choosing nothing.
    combination[0] = 1;
    
    // Iterate over all the coins in the array
    for(int i=0;i<n;i++){
        
        // Iterate over the all the sum from j=1 to j=sum
        for(int j=1;j<=sum;j++){
            
            // Only if the value j-coins[i] exist, then the result would be combination[j]+combination[j-coins[i]];
            if(j>= coins[i]){
                combination[j] += combination[j-coins[i]];
            }
        }
        
        // Uncomment to print the combination array to see how it varies.
        // for(int j=0;j<=sum;j++){
        //     cout<<combination[j]<<" ";
        // }
        // cout<<endl;
    }
    cout<<combination[sum]<<endl;
}

// Driver program to test above functions 
int main() 
{ 
    // - | 0  1  2  3  4  5  6  7  8  9  10  11  12
    // -------------------------------------------
    // 0 | 1  0  0  0  0  0  0  0  0  0   0   0  0 
    // 1 | 1  1  1  1  1  1  1  1  1  1   1   1  1 
    // 2 | 1  1  2  2  3  3  4  4  5  5   6   6  7 
    // 5 | 1  1  2  2  3  4  5  6  7  8  10  11 13

    int coins[3] = {1,2,5};
    int num_of_coins = sizeof(coins)/sizeof(coins[0]);
    int sum = 12;
    coinChanging(coins, num_of_coins, sum);
	return 0; 
} 


// Solution with 2D array:

class Solution {
public:
    int change(long long int sum, vector<int>& coins) {
        int n= coins.size();
        long long int dp[n+1][sum+1];
        
        for(int i=0;i<sum+1; i++)
            dp[0][i] = 0;
        
        for(int i=0;i<n+1; i++)
            dp[i][0] = 1;
        
        for(long int i=1; i<n+1; i++){
            for(long int j=1; j<sum+1; j++){
                if(j>=coins[i-1]){
                    dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
                }
                else {
                    dp[i][j] = dp[i-1][j];
                }
            }
            
        }
        return dp[n][sum];
    }
};