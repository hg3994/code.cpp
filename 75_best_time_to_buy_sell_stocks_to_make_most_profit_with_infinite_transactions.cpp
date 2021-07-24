
/*

Harshit Gupta | 20th October, 2020
---------------------------------

C++ program for "Best Time to Buy and Sell Stocks with as transactions as you like (INFINITE)"
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

    You are given an array prices where prices[i] is the price of a given stock on the ith day.
    Find the maximum profit you can achieve. You may complete as many transactions as you like 
    (i.e., buy one and sell one share of the stock multiple times. However, you must sell and 
    then buy on the same day).

    Note: You may not engage in multiple transactions simultaneously (i.e., you must sell the 
        stock before you buy again).

Example 1:
    Input: prices = [7,1,5,3,6,4]
    Output: 7
    Explanation: Buy on day 2 (price = 1) and sell on day 3 (price = 5), profit = 5-1 = 4.
    Then buy on day 4 (price = 3) and sell on day 5 (price = 6), profit = 6-3 = 3.

Example 2:
    Input: prices = [1,2,3,4,5]
    Output: 4
    Explanation: Buy on day 1 (price = 1) and sell on day 5 (price = 5), profit = 5-1 = 4.
        Note that you cannot buy on day 1, buy on day 2 and sell them later, as you are engaging multiple 
        transactions at the same time. You must sell before buying again.

Example 3:
    Input: prices = [7,6,4,3,1]
    Output: 0
    Explanation: In this case, no transaction is done, i.e., max profit = 0.


------
Solution: 
    We can simply go on crawling over the slope and keep on adding the profit obtained from every 
    consecutive transaction. We can directly keep on adding the difference between the consecutive 
    numbers of the array if the second number is larger than the first one, and at the total sum we 
    obtain will be the maximum profit. 

    The reason why we are able to do this is because we need the sum & we have 
    infinite transactions. Consider example,
        [10,20,30]
    The answer would say buy on 10, sell on 20, but on 20, sell on 30 => 20 profit
    while if asked to done in min transactions user buys on 10 and sells on 30
    but we have infinite transactions and what we need is the profit, we can buy-sell 
    on any increase in amount, so that we get that profit, remaining profit can be made
    further when the proces increases. But, if the price decreases, we will just add 0
    oin profit meaning we did not buy-sell on those i and (i-1)th day.

Time Complexity: O(n)
Space Complexity: O(1)

Similar Questions:
    1. https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/
        - Same problem which has infinite transactions but the only condition is we can not buy and sell on same day
        - This would require DP and some state transition things.
        - TODO


Resources:
    1. Must Read blog for all types of Stock Problems: 
        - https://leetcode.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/discuss/75924/Most-consistent-ways-of-dealing-with-the-series-of-stock-problems

---
  NOTE: 

*/


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int profit = 0;
        for(int i=1;i<prices.size();i++){
            profit += max(prices[i]-prices[i-1] ,0);
        }
        return profit;
    }
};


int main(){
	Solution s;
	vector<int> p = {7,1,5,3,6,4};
	cout<<s.maxProfit(p)<<endl;
	return 0;
}