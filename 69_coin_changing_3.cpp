/*

Harshit Gupta | 2nd October, 2020
---------------------------------

C++ program for "Given an array of distinct integers candidates and a target integer target, 
  return a list of all unique combinations of candidates where the chosen numbers sum to target.
  You may return the combinations in any order."

  This is basically coin_chaining_1 question but here we have to output the different arrays 
    which form the sum "target" and not just the number of solutions possible.

https://leetcode.com/problems/combination-sum/

Input: candidates = [2,3,6,7], target = 7
Output: [[2,2,3],[7]]
Explanation:
  2 and 3 are candidates, and 2 + 2 + 3 = 7. Note that 2 can be used multiple times.
  7 is a candidate, and 7 = 7.
  These are the only two combinations.

------

Solution: Given below are two solutionsL
  #1: DP: We create the similar dp[][] array and then backtrack from dp[n][m] to dp[0][0]
      tracing all possible paths. We keep adding and removing the elements from an array
      through backtracking and as soon as we reach dp[0][0], we output the array.
  Time Complexity: O(n2)
  Space Complexity: O(n2)

  #2: BACKTRACKING: We iterate over all the coins and then choose it for the solution, 
      then move forward and see if a solution is feasible.
      If yes, add it in the result array, and then move to the next element.
      If not, remove it from the "consideration" and move to the next element.
  Time Complexity: O(number of coins)^(target/min(coins))
    https://leetcode.com/problems/combination-sum/discuss/16634/If-asked-to-discuss-the-time-complexity-of-your-solution-what-would-you-say

https://leetcode.com/problems/combination-sum/solution/


NOTE: 
  1. Recursive Solution is so so simple. Just look at it.
*/

// DP Solution #1
class Solution1 {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        int s = candidates.size();
        
        vector<vector<int>> dp(s, vector<int> (target+1, 0));
        
        for(int i=0; i<s;i++){
            dp[i][0] = 1;
        }
        
        for(int i=0; i<s;i++){
            for(int j=1;j<=target; j++){
            
                if(j >= candidates[i]){
                    if (i==0)
                        dp[i][j] = dp[i][j-candidates[i]];
                    else  
                        dp[i][j] = dp[i-1][j]+dp[i][j-candidates[i]];
                }
                else{
                    if (i!=0)
                        dp[i][j] = dp[i-1][j];
                }
            }
        }

        // - | 0  1  2  3  4  5
        // --------------------
        // 1 | 1  1  1  1  1  1
        // 2 | 1  1  2  2  3  3
        // 5 | 1  1  2  2  3  4
        
        vector<vector<int>> ans;
        vector<int> tempAns;
        calculateCombination(dp, candidates, ans, tempAns, s-1, target);

        return ans;
    }
  
    void calculateCombination(vector<vector<int>> dp, vector<int> candidates, vector<vector<int>>& ans, vector<int> tempAns, int i, int j) {
        // cout<<"calculateCombination(): i: "<<i<<" j: "<<j<<endl;
        if(j==0){
            ans.push_back(tempAns);
            tempAns.clear();
            return;
        }
    
        else {
            // if not considering this number.
            if (i>0 && dp[i-1][j]>=1){
                calculateCombination(dp, candidates, ans, tempAns, i-1, j);
            }

            // considering this number.
            if (j>=candidates[i] && dp[i][j-candidates[i]] >= 1){
                tempAns.push_back(candidates[i]);
                calculateCombination(dp, candidates, ans, tempAns, i, j-candidates[i]);
                tempAns.pop_back();
            }
        }
    }
  
};


// Backtracking Solution #2
class Solution2 {
public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> ans;
    vector<int> tempAns;
    backtrack(candidates, ans, tempAns, target, 0);
    return ans;
  }
  
  void backtrack(vector<int> candidates, vector<vector<int>>& ans, vector<int> tempAns, int remain, int start){
    
    if(remain < 0)
      return;
    
    if(remain == 0){
      ans.push_back(tempAns);
      return;
    }
    
    for(int i=start; i<candidates.size();i++){
      tempAns.push_back(candidates[i]);
      backtrack(candidates, ans, tempAns, remain-candidates[i], i);
      tempAns.pop_back();
    }
  }
  
};

int main(){

  Solution1 s1;
  Solution2 s2;
  vector<int> coins = {2,3,6,7};
  vector<vector<int>> ans;
  int target = 7;
  ans1 = s1.combinationSum(coins, target);
  ans2 = s2.combinationSum(coins, target);

  cout<<ans1<<endl;
  cout<<ans2<<endl;
  return 0;
}