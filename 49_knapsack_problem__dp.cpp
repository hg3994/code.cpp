/* 
Harshit Gupta | 3rd February, 2019

https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/
https://www.geeksforgeeks.org/fractional-knapsack-problem/
https://ide.geeksforgeeks.org/knFDdW0dyh

MUST SEE: https://leetcode.com/discuss/study-guide/1200320/Thief-with-a-knapsack-a-series-of-crimes.

C++ program

0-1 Knapsack Problem
====================
"Given weights and values of n items, put these items in a knapsack of capacity W to get the maximum 
total value in the knapsack. In other words, given two integer arrays val[0..n-1] and wt[0..n-1] which 
represent values and weights associated with n items respectively. Also given an integer W which represents 
knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset 
is smaller than or equal to W. You cannot break an item, either pick the complete item, 
or don’t pick it (0-1 property)."

> To consider all subsets of items, there can be two cases for every item: 
		(1) the item is included in the optimal subset, 
		(2) not included in the optimal set.
	Therefore, the maximum value that can be obtained from n items is max of following two values.
			1) Maximum value obtained by n-1 items and W weight (excluding nth item).
			2) Value of nth item + maximum value obtained by n-1 items and W minus weight of the nth item (including nth item).

		If weight of nth item is greater than W, then the nth item cannot be included and case 1 is the only possibility.

	// Bottom Up DP
	int dp[W + 1] = {0};
	for (int i=0; i<n; ++i)
	    for (int j=W; j>=weight[i]; --j)
	        dp[j] = max(dp[j], value[i]+ dp[j - weight[i]]);
	return dp[W];


	// Top Bottom DP
	dp[n+1][W+1] = {0};
	for(i=0; i<=n; i++){
		for(j=0; j<=W; j++)
			if(j>=wt[i-1])
				dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i-1][j-wt[i-1]]);
			else
				dp[i][j] = dp[i-1][j];
	return dp[n][W];


Fractional Knapsack Problem
===========================
"Given weights and values of n items, we need to put these items in a knapsack of capacity W to
get the MAXIMUM total value in the knapsack. We can break an item into smaller pieces if we want 
since this is not a constraint for this problem"

>	An efficient solution is to use Greedy approach. The basic idea of the greedy approach is to calculate 
	the ratio value/weight for each item and sort the item on basis of this ratio. Then take the item with 
	the highest ratio and add them until we can’t add the next item as a whole and at the end add the next 
	item as much as we can. Which will always be the optimal solution to this problem.


Paradigm: Dynamic Programming, Greedy


Similar Problems:
	1. https://leetcode.com/problems/partition-equal-subset-sum/
		- Given a non-empty array nums containing only positive integers, find if the array can be partitioned into two 
			subsets such that the sum of elements in both subsets is equal.
			- If sum is odd, it can never be true
			- Similar to knapsack problem with sum/2 as goal
			- More similar to coin changing where question is Can we get a sum from some coins?
	2. https://leetcode.com/problems/coin-change-2/
		- You are given an integer array coins representing coins of different denominations and an integer amount 
			representing a total amount of money. Return the number of combinations that make up that amount. 
			If that amount of money cannot be made up by any combination of the coins, return 0.

*/

#include <bits/stdc++.h>
using namespace std; 

// Structure for an item which stores weight and corresponding value of Item for Fractional Knapsack.
struct Item{
	int value, weight;
	Item(int value, int weight){
		this->value = value;
		this->weight = weight;
	}
};

// Comparison function to sort Item according to val/weight ratio 
bool cmp(struct Item a, struct Item b) 
{ 
    double r1 = (double)a.value / a.weight; 
    double r2 = (double)b.value / b.weight; 
    return r1 > r2; 
} 

int knapsack_01(int W, vector<int> wt, vector<int> val, int n){
	// Recursive Solution

	// if (n == 0 || W==0){
	// 	return 0;
	// }
	// else{
	//  select the nth weight or don't select. Then choose what gives you the maximum out of these two.
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

int fractionalKnapsack(int W, struct Item arr[], int n){
	// sorting Item on basis of ratio 
	sort(arr, arr+n, cmp);

	int curWeight = 0;  // Current weight in knapsack
  	double finalvalue = 0.0; // Result (value in knapsack)

	for (int i = 0; i < n; i++){ 
		// If adding Item won't overflow, add it completely 
		if (curWeight + arr[i].weight <= W){ 
		    curWeight += arr[i].weight;
		    finalvalue += arr[i].value;
		}
		// If we can't add current Item, add fractional part of it 
		else { 
		    int remain = W - curWeight; 
		    finalvalue += arr[i].value * ((double) remain / arr[i].weight); 
		    break; 
		}
	}
	// Returning final value 
	return finalvalue;
}

int main() 
{ 
    vector<int>val = {60, 100, 120}; 
    vector<int> wt = {10, 20, 30}; 
    int W = 50;
    int n = val.size();
    cout<<knapsack_01(W, wt, val, n)<<endl;

    Item arr[] = {{60, 10}, {100, 20}, {120, 30}}; 
    cout<<fractionalKnapsack(W, arr, n)<<endl;

    return 0; 
} 


// ---------------------------
// LEETCODE SIMILAR QUESTION 1
// ---------------------------
// Approach 2: DP
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
        
        for(auto num: nums) {
            for(int j= sum; j>=0; j--){
                if(j >= num)
                    dp[j] = dp[j] || dp[j-num];
            }
        }
        return dp[sum];
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