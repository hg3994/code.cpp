/*

Harshit Gupta | 19th September, 2020
-------------------------------------

Ruby program for "Best Time to Buy and Sell Stock to make most profit"
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.


https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Solution: In formal terms, we need to find max({prices[j]} - {prices[i]}), for every i and j such that j > i.
	We can obviously use Brute Force to get all combinations of price differences and that would give us the max profit. Time Complexity: O(n2)
	---
	A better solution is to loop (for every i from 0:n) and:
	- Keep track of miniumum value of the stock till now (0 to i)
	- Keep track of the maximum profit value of the stock till now (0 to i)
	
	Profit each day would be the difference of the stock value and minimum value till now
	Maximum Profit would be the maximum of all such numbers

	If we keep on calculating this "maximum profit till now", then this number at the end of the array
		would give us "most money one could make"

*/


class Solution {
public:
    int maxProfit(vector<int>& prices) {
        if(prices.size() <=1)
            return 0;
        int minTillNow = prices[0];
        int maxProfit = 0;
        
        for(int i=0; i<prices.size(); i++){
            minTillNow = min(minTillNow, prices[i]);
            maxProfit = max(maxProfit, prices[i]-minTillNow);
        }
        return maxProfit;
    }
};