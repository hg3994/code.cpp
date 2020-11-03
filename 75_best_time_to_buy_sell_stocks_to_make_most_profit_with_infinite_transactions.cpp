
/*

Harshit Gupta | 20th October, 2020
---------------------------------

C++ program for "Best Time to Buy and Sell Stocks with as many transactions as you like"
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/

------
Solution: 


https://leetcode.com/problems/best-time-to-buy-and-sell-stock-ii/solution/

Time Complexity: O(n)
Space Complexity: O(1)
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