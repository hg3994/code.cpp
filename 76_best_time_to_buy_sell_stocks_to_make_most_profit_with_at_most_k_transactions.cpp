
/*

Harshit Gupta | 20th October, 2020
---------------------------------

C++ program for "Best Time to Buy and Sell Stocks with at most k transactions"
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

You are given an integer array prices where prices[i] is the price of a given 
    stock on the ith day, and an integer k.
Find the maximum profit you can achieve. You may complete at most k transactions.

Note: You may not engage in multiple transactions simultaneously (i.e., you must 
    sell the stock before you buy again).

Example 1:
    Input: k = 2, prices = [2,4,1]
    Output: 2
    Explanation: Buy on day 1 (price = 2) and sell on day 2 (price = 4), profit = 4-2 = 2.

Example 2:
    Input: k = 2, prices = [3,2,6,5,0,3]
    Output: 7
    Explanation: Buy on day 2 (price = 2) and sell on day 3 (price = 6), profit = 6-2 = 4. 
        Then buy on day 5 (price = 0) and sell on day 6 (price = 3), profit = 3-0 = 3.

------
Solution: We will use DP to solve this:

    k = 2, prices= [3,2,6,5,0,3]
    Creating dp[k+1][prices.size()]

          0 1 2 3 4 5  <-index
          3 2 6 5 0 3  <-prices
        0 0 0 0 0 0 0
        1 0 0 4 4 4 4
        2 0 0 4 4 4 7

    dp[i][j] represents the max profit one can make with at most i transactions in j days

    dp[i][j] = max( 
            1. Not transacting on jth day = dp[i][j-1]
            2. Selling on jth day and buying on m=0..(j-1) th day + 
                profit made till mth day with i-1 transactions
                    =(price[j]-price[m]+dp[i-1][m])
                    =(dp[i-1][m]-price[m]+price[j])
            )

If we do this, it will be O(n3) and we want to reduce it so we optimize the 2nd condition above
    from O(n) to O(1) like this:

If you notice, for all m=0..j-1, the term price[j] is constant and never changes
so basically we need to maximize the term = dp[i-1][m]-price[m] and that will increase
my profit by selling on jth day and buying on some mth day.

So basically for m=1..j-1,we maximize (dp[i-1][m]-price[m])
    maximize(   dp[i-1][1]-price[1],
                dp[i-1][2]-price[2],
                ...,
                dp[i-1][j-1]-price[j-1]
            )

Lets say we have this for a particular j, now we increase j=j+1 and then again we need 
to maximize the same term except that now there will be one more term 
    
    maximize(   dp[i-1][1]-price[1],
                dp[i-1][2]-price[2],
                ...,
                dp[i-1][j-1]-price[j-1]
                dp[i-1][j]-price[j]
            )

If we had calculated the max till dp[i-1][j-1]-price[j-1], then we just need to check 
for previoud max and dp[i-1][j]-price[j]. Isn't it?
It's like saying I know the max(1,5,2,6,3) is 6, so for calculating the max(1,5,2,6,3,7)
we only need to check max(6,7) and not the whole array again.

We call this term which we need to maximize as max_diff and for every j, we just need to 
update max_diff with max(max_diff, dp[i-1][j]-price[j])

Also, when we start, the max_diff is just one term = profit[0][0]-prices[0];
--
Also for example, when j completes and we go on for the next i=i+1 which means we have one more transaction
then also we need to calculate the max_diff again for that i, so for every i, we need to have:
    max_diff = profit[i][0]-prices[0];

---

max_diff is going to take care of the term "dp[i-1][m]-price[m]" but what about the remaining "prices[j]"".
We still need it in our calculations, so
    max_diff = max(max_diff, dp[i-1][j] - prices[j]);
    dp[i][j] = max(dp[i][j-1], max_diff + prices[j]);

    Notice max_diff + prices[j] in the statement.
    dp[i][j-1] says about condition #1 which is not transacting on jth day
    max_diff + prices[j] says about buying on some mth day and selling on jth day.


Time Complexity: O(n2).
Space Complexity: O(n2)

Resources:
    1. Amazing Video https://www.youtube.com/watch?v=oDhu5uGq_ic

Similar Questions:
    1. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
        - Same question but k=2 so at max 2 transactions.
        - This can also be done without DP and that si mentioned here: 
            - https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/solution/
        - TODO the other solutions
---
  NOTE: 

*/



class Solution {
public:
    int maxProfit(int k, vector<int>& prices) {
        long int d = prices.size();
        if(d == 0 || d == 1 || k == 0)
            return 0;

        // If k>d/2, then we can consider that we have infinite transactions
        if (k>d/2){
            int ans = 0;
            for (int i=1; i<d; ++i){
                ans += max(prices[i] - prices[i-1],0);
            }
            return ans;
        }
        long int dp[k+1][d];
        
        // In 1st day only, we will have 0 profit by buying-selling same day (irrepective of k)
        for(long int i=0;i<d;i++)
            dp[0][i] = 0;
        
        // For 0 transactions, we can never buy-sell so 0 profit.
        for(long int i=0;i<k+1;i++)
            dp[i][0] = 0;
        
        // Calculating max profit which can be made with i transactions in d days
        // dp[i][j] = max( 
        //         1. Not transacting on jth day = dp[i][j-1]
        //         2. Selling on jth day and buying on m=0..(j-1) th day + 
        //             profit made till mth day with i-1 transactions
        //                 =(price[j]-price[m]+dp[i-1][m])
        //                 =(dp[i-1][m]-price[m]+price[j])
        //         )
        for(long int i=1;i<k+1;i++){
            long int max_diff = dp[i][0] - prices[0];
            for(long int j=1; j<d; j++){
                max_diff = max(max_diff, dp[i-1][j]-prices[j]);
                dp[i][j] = max(dp[i][j-1], max_diff+prices[j]);
            }
            
        }
        
         // for(int i=0;i<k+1;i++){
         //     for(int j=0; j<d; j++){
         //         cout<<dp[i][j]<<" ";
         //     }
         //     cout<<endl;
         // }

        return dp[k][d-1];
    }
};


int main(){
	Solution s;
	vector<int> p = {3,2,6,5,0,3};
    int k = 2;
	cout<<s.maxProfit(k,p)<<endl;
	return 0;
}


// ------------------------------------------------------
// Solution of Similar Problem #1 (at max 2 transactions)
// ------------------------------------------------------

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int d = prices.size();
        if(d <= 1)
            return 0;
        
        vector<int> tmp(d, 0);
        vector<vector<int>> dp(3, tmp);
        
        for(int i=0; i<3; i++)
            dp[i][0] = 0;
        for(int i=0; i<d; i++)
            dp[0][i] = 0;
        for(int i=1; i<3; i++){
            int max_diff = dp[i][0] - prices[0];
            for(int j=1; j<d; j++){
                max_diff = max(max_diff, dp[i-1][j] - prices[j]);
                dp[i][j] = max(dp[i][j-1], max_diff + prices[j]);
            }
        }
        
        return dp[2][d-1];
    }
};