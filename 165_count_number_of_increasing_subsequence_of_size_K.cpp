
/*

Harshit Gupta | 1st August, 2021
---------------------------------

Problem Statement:

    Given an array arr[] containing n integers. The problem is to count number of increasing 
    & decreasing subsequences in the array of size 3.

    Input: [5,2,3,1,4]
    Output: [5,2,1], [5,3,1], [2,3,4]

    https://www.geeksforgeeks.org/count-number-increasing-subsequences-size-k/

------

Solution: 
    The idea is to use Dynamic Programming by define 2D matrix, say dp[][]. dp[i][j] stores the count of 
        increasing subsequences of size i ending with element arr[j]. 
    So dp[i][j] can be defined as:
        dp[i][j] = 1, where i = 1 and 1 <= j <= n 
        dp[i][j] = sum(dp[i-1][j]), where 1 < i <= k, i <= j <= n and arr[m] < arr[j] for (i-1) <= m < j.

    TC: O(kn2)
    SC: O(kn)

Paradigm:
---
    NOTE: Asked in Goldman Sachs

    Similar Questions:
        1.

*/

// dp[][] increasing
//     5 2 3 1 4
// --------------
// 0 | 1 1 1 1 1 
// 1 | 0 0 1 0 3 
// 2 | 0 0 0 0 1 

// dp[][] decreasing
//     5 2 3 1 4
// --------------
// 0 | 1 1 1 1 1
// 1 | 0 1 1 3 1
// 2 | 0 0 0 2 0
 
// ans: [5,2,1], [5,3,1], [2,3,4]
 

Example: 2


// dp[][] increasing
//     1 2 3 4 5
// --------------
// 0 | 1 1 1 1 1 
// 1 | 0 1 2 3 4 
// 2 | 0 0 1 3 6 

// dp[][] decreasing
//     1 2 3 4 5
// --------------
// 0 | 1 1 1 1 1
// 1 | 0 0 0 0 0
// 2 | 0 0 0 0 0
 
// ans: [1,2,3], [1,2,4], [1,3,4], [2,3,4], [1,2,5], [1,3,5], [1,4,5], [2,3,5], [2,4,5], [3,4,5]


// Complete the getCountOfPossibleTeams function below.
int getCountOfPossibleTeams(vector<int> coders) {
    int n= coders.size();
    // dp[i][j] would represent a subsequence of size i ending with coders[j]
    // For size 3, we will need to add dp[2][...]
    vector<vector<int>> dp (3, vector<int>(n, 0));
    int ans=0;
    for(int i=0; i<n; i++)
        dp[0][i] = 1;
    
    // For all sizes of substrings from 1, 2 (since 0 is already calc'd)
    for(int l=1; l<3; l++){
        // For all the strings ending with index l till n of size l+1. i is the size of the substring
        for(int i=l; i<n; i++){
            // For all the strings ending with index l-1 till i of size l+1
            for(int j=l-1; j<i; j++){
                // If num[j] < num[i], it means it is an increasing string, so dp[l][i] += dp[l-1][j]
                if(coders[j] < coders[i]){
                    dp[l][i] += dp[l-1][j];
                }
            }
        }
    }
    
    for(int i=2; i<n; i++)
        ans += dp[2][i];
        
    vector<vector<int>> dp1 (3, vector<int>(n, 0));
    for(int i=0; i<n; i++)
        dp1[0][i] = 1;
        
    for(int l=1; l<3; l++){
        for(int i=l; i<n; i++){
            dp1[l][i] = 0;
            for(int j=l-1; j<i; j++){
                if(coders[j] > coders[i]){
                    dp1[l][i] += dp1[l-1][j];
                }
            }
        }
    }
    
    for(int i=2; i<n; i++)
        ans += dp1[2][i];
    
    return ans;

}