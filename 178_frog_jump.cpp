
/*

Harshit Gupta | 14th August, 2021
---------------------------------

Problem Statement:

Given a sorted stone array containing the positions at which there are stones in a river. We need to determine whether it is 
possible or not for a frog to cross the river by stepping over these stones, provided that the frog starts at position 0, 
and at every step the frog can make a jump of size k−1, kk or k+1 if the previous jump is of size k.
Initially, the frog is on the first stone and assumes the first jump must be 1 unit.

Example 1:
    Input: stones = [0,1,3,5,6,8,12,17]
    Output: true
    Explanation: The frog can jump to the last stone by jumping 1 unit to the 2nd stone, then 2 units to the 3rd stone, 
        then 2 units to the 4th stone, then 3 units to the 6th stone, 4 units to the 7th stone, and 5 units to the 8th stone.

Example 2:
    Input: stones = [0,1,2,3,4,8,9,11]
    Output: false
    Explanation: There is no way to jump to the last stone as the gap between the 5th and 6th stone is too large.

https://leetcode.com/problems/frog-jump/
------

Solution: 3 solutions are discussed below:
    1. Classic Recursion.
        TC: O(3^n)
        SC: O(n) for recursion stack.

    2. Recursion with Memoization. This is the best solution in my idea.
        TC: O(n2)
        SC: O(n2) for DP[][] array

    3. Pure DP approach
        TC: O(n2)
        SC: O(n2) for DP[][] array

Paradigm:
---
    NOTE: 
        1. Do not get confused on the 'pos' and 'index' thing. Since we are going to need the stones, we must always recurse on pos
            which is the current position(stone).
        2. Asked in Flipkart.

    Similar Questions:
        1.

*/

// Approach 1: Normal Recursion with HashMap for checking if a position exists
// TC: O(3^n)
class Solution {
public:
    unordered_map<int, bool> positions;
    
    bool recurse(vector<int>& stones, int pos, int J){
        if(pos == stones.back())
            return true;
        if(!positions[pos] || pos > stones.back() || J==0)
            return false;
        return recurse(stones, pos+J, J) || recurse(stones, pos+J+1, J+1) || recurse(stones, pos+J-1, J-1);
    }
    
    bool canCross(vector<int>& stones) {
        if(stones[1]-stones[0] != 1)
            return false;
        for(int i=0;i<stones.size();i++)
            positions[stones[i]] = true;
        return recurse(stones, stones[0], 1);
    }
};


// Approach 2: Recursion with Memoization & HashMap for checking if a position exists
// TC: O(n2)
// Why is the TC: O(n2) ? 
//      The function is called only as many times as you have distinct parameters: 
//      if you want to call it with parameters you've used already, you save having to call it.
//      Here, the max distinct parameters are the dp[][] array values which are nxn. We are never going to 
//      calculate values which are not in this dp[][] array.
// More explanation here: https://stackoverflow.com/questions/53143539/how-does-complexity-get-reduced-to-on2-from-o2n-in-case-of-memoization
class Solution {
public:
    unordered_map<int, bool> positions;
    unordered_map<int, int> positions_to_index;
    vector<vector<int>> dp;
    
    bool recurse(vector<int>& stones, int pos, int J){
        // cout<<"recurse: pos: "<<pos<<" J: "<<J<<endl;
        if(pos == stones.back())
            return true;
        if(!positions[pos] || pos > stones.back() || J==0)
            return false;
        if(dp[positions_to_index[pos]][J] != -1)
            return dp[positions_to_index[pos]][J];
        
        dp[positions_to_index[pos+J]][J] = recurse(stones, pos+J, J);
        dp[positions_to_index[pos+J+1]][J+1] = recurse(stones, pos+J+1, J+1);
        dp[positions_to_index[pos+J-1]][J-1] = recurse(stones, pos+J-1, J-1);
        
        return dp[positions_to_index[pos+J]][J] || dp[positions_to_index[pos+J+1]][J+1] || dp[positions_to_index[pos+J-1]][J-1];
    }
    
    bool canCross(vector<int>& stones) {
        if(stones[1]-stones[0] != 1)
            return false;
        if(stones.size() == 2 && stones[1]-stones[0] == 1)
            return true;
        int n = stones.size();
        dp.resize(n, vector<int>(n, -1));
        
        for(int i=0;i<n;i++){
            positions[stones[i]] = true;
            positions_to_index[stones[i]] = i;
        }
        return recurse(stones, stones[1], 1);
    }
};



// Approach 3: DP (On2)
class Solution {
    
public:
    bool canCross(vector<int>& stones) {
        int n = stones.size();
        
        // Map to keep track of "if an element 'x' is present in stones[] vector" in O(1) time instead of O(n).
        unordered_map<int, bool> elements;
        for(int i=0;i<n;i++)
            elements[stones[i]] = true;
        
        // map to keep track of the jumps you can make to reach to dp[i]
        // dp[i] = {set of jumps you can make to reach this stones[i]}
        unordered_map<int, set<int>> dp;
        dp[0] = {0};
        
        // Iterate over all the stones
        for(int i=0; i<n; i++){
            set<int> jumps = dp[stones[i]];
            // Iterate over all the jumps with which this stone can be reached
            for (auto jump : jumps) { 
                
                // If the jump+where you are standing is an element ahead, add this jump to that stones' dp
                // since this is a way in which we can reach stone > jump+stones[i] by doing 'jump' steps of jump
                if (elements.find(jump+stones[i]) != elements.end() && jump!=0){
                    dp[jump+stones[i]].insert(jump);
                }
                // Similarly for jump+stones[i]+1
                if (elements.find(jump+stones[i]+1) != elements.end() && jump!=-1){
                    dp[jump+stones[i]+1].insert(jump+1);
                }
                // Similarly for jump+stones[i]-1
                if (elements.find(jump+stones[i]-1) != elements.end() && jump!=1){
                    dp[jump+stones[i]-1].insert(jump-1);
                }
            }
        }
        
        // If we can't reach the last stone, then return false, else true.
        if (dp[stones[n-1]].empty()){
            return false;
        }
        else{
            return true;
        }
        
    }
};