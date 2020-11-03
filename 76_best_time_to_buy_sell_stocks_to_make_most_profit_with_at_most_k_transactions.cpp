
/*

Harshit Gupta | 20th October, 2020
---------------------------------

C++ program for "Best Time to Buy and Sell Stocks with at most k transactions"
https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/

------
Solution: 


https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iv/solution/

Time Complexity: 
Space Complexity:
---
  NOTE: 

*/


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
  int maxProfit(int k, vector<int>& prices) {
    long int d = prices.size();
    if(d == 0 || d == 1 || k == 0)
      return 0;
    if (k>d/2){ // simple case
        int ans = 0;
        for (int i=1; i<d; ++i){
            ans += max(prices[i] - prices[i-1],0);
        }
        return ans;
    }
    long int x = k+1;
    long int profit[x][d];
    for(long int i=0;i<d;i++){
      profit[0][i] = 0;
    }
    for(long int i=0;i<k+1;i++){
      profit[i][0] = 0;
    }
    for(long int i=1;i<k+1;i++){
      long int max_diff = profit[i][0]-prices[0];
      for(long int j=1; j<d; j++){
        // int max_by_selling_on_j = 0;
        // for(int m=0; m <j; m++){
        //   max_by_selling_on_j = max(prices[j]-prices[m]+profit[i-1][m], max_by_selling_on_j);
        // }
        // profit[i][j] = max(profit[i][j-1], max_by_selling_on_j);

        max_diff = max(max_diff, profit[i-1][j]-prices[j]);
        profit[i][j] = max(profit[i][j-1], max_diff + prices[j]);
          
      }
    }
    
    // for(int i=0;i<k+1;i++){
    //   for(int j=0; j<d; j++){
    //     cout<<profit[i][j]<<" ";
    //   }
    //   cout<<endl;
    // }
    
    return profit[k][d-1];
    
  }
};


int main(){
	Solution s;
	vector<int> p = {3,2,6,5,0,3};
  int k = 2;
	cout<<s.maxProfit(k,p)<<endl;
	return 0;
}