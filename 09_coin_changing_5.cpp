/* 
Harshit Gupta | 18th October, 2018

C++ program for "Minimum Coins required for a Sum"

    Given a set of coins which are NOT INFINITE in number, how many minimum coins would you select to form a target sum?
    OR
    Given a set of numbers in an array and a sum, select minimum number of coins to form the sum.

Example:

    1. arr: [1,3,5,7,9], sum: 8
        => 2 (5,3)
    2. arr: [1,3,5,7,9], sum: 12
        => 2 (5,7)
    3. arr: [1,3,5,7,9], sum: 25
        => 1 (1,3,5,7,9)
    4. arr: [1,3,5,7,9], sum: 15
        => 3 (3,5,7)

NOTE:
    1. This is very very similar to the problem where we have to infinite number of coins and we have to output the 
        coins which form the sum (69). We use backtracking to get the array of coins which form the sum. 
        Here we are going to do a similar thing but only thing is.. here we do not have infinite number of coins
        so in our logic we will exclude "infinite" thing.


*/

#include <bits/stdc++.h>
using namespace std;

void backtrack(vector<int> candidates, vector<int>& minCoins, vector<int> tempAns, int remain, int start){
    if(remain < 0)
        return;
    if(remain == 0){
        minCoins = tempAns.size() < minCoins.size() ? tempAns : minCoins;
        return;
    }
    // NOTE THAT i=start+1 is used so that we do not use one coin more than once.
    // In other case(69), we used i=start since we wanted infinite number of coins.
    for(int i=start+1; i<candidates.size();i++){
        tempAns.push_back(candidates[i]);
        backtrack(candidates, minCoins, tempAns, remain-candidates[i], i);
        tempAns.pop_back();
    }
}

vector<int> combinationSum(vector<int>& candidates, int target) {
    vector<int> minCoins(candidates.size()+1, 0);
    vector<int> tempAns;
    backtrack(candidates, minCoins, tempAns, target, -1);
    return minCoins;
}

int main() {
    vector<int> arr = {1,3,5,7,9};
    int sum = 25;
    vector<int> minCoins = combinationSum(arr, sum);
    cout<<minCoins.size()<<endl;
    for(auto c: minCoins)
        cout<<c<<" ";
    return 0;
}

