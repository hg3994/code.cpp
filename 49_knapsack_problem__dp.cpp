/* 
Harshit Gupta | 3rd February, 2019


C++ program for 

0-1 Knapsack Problem
====================
"Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum 
total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which 
represent values and weights associated with n items respectively. Also given an integer W which represents 
knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset 
is smaller than or equal to W. You cannot break an item, either pick the complete item, 
or don’t pick it (0-1 property)."

Fractional Knapsack Problem
===========================


Solution: 

Paradigm: 

Time Complexity: 

*/

#include <bits/stdc++.h>
using namespace std; 

int knapsack_01(int W, vector<int> wt, vector<int> val, int n){
	// Recursive Solution

	// if (n == 0 || W==0){
	// 	return 0;
	// }
	// else{
	// 	return max(knapsack_01(W-wt[n-1],wt,val,n-1) + val[n-1], knapsack_01(W,wt,val,n-1));
	// }


	// Dynamic Programming Solution
	int dp[n+1][W+1];
	int i,w;

	// Iterate over all the elements of the array
	for(i=0;i<=n;i++){
		// Iterate over the weights and check for all the weights from 0 to W.
		for(w=0;w<=W;w++){
			// Base condition. Don't think that i=0(1st index of the val[]) array is ignored.
			// Note that we are using i-1 in other places. So, its equal. This is also the reason 
			// of why the i loop itertes till n and not less than.
			if(i==0 || w==0)
				dp[i][w]=0;
			// dp[i][w] is maximum of two things:
				// either we consider the ith weight (dp[i-1][w-wt[i-1]] + val[i-1])
				// or we dont consdier the ith weigth (dp[i-1][w])
			else
				dp[i][w] = max(dp[i-1][w-wt[i-1]] + val[i-1], dp[i-1][w]);
		}
	}
	return dp[n][W];
}

int main() 
{ 
    vector<int>val = {60, 100, 120}; 
    vector<int> wt = {10, 20, 30}; 
    int W = 50;
    int n = val.size();
    cout<<knapsack_01(W, wt, val, n)<<endl;
    return 0; 
} 
