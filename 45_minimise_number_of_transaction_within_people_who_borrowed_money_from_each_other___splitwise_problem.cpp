/* 
Harshit Gupta | 11th January, 2019

https://github.com/rachitiitr/DataStructures-Algorithms/blob/master/Famous-Coding-Interview-Problems/TheSplitwiseProblem.cpp
https://www.youtube.com/watch?v=Vy5PLlpDoks
https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

C++ program for "Minimize Cash Flow among a given set of friends who have borrowed money from each other"

Solution: 
    1) Compute the net amount for every person. The net amount for person ‘i’ can be computed be subtracting sum 
        of all debts from sum of all credits.
    2) Find the two persons that are maximum creditor(Pc) and maximum debtor(Pd). Let the maximum amount to be 
        credited maximum creditor be maxCredit and maximum amount to be debited from maximum debtor be maxDebit.
    3) Find the minimum of maxDebit and maxCredit. Let minimum of two be x. Debit ‘x’ from Pd and credit 
        this amount to Pc
    4) If x is equal to maxCredit, then remove Pc from set of persons and recur for remaining (n-1) persons.
    5) If x is equal to maxDebit, then remove Pd from set of persons and recur for remaining (n-1) persons.

NOTE: This solution does not work for disconnected graphs.
    Eg: [[0 1 8], [2 3 4], [2 4 6]] We see that it can happen in 3 transactions, but the code will give 4
    The reason behind that is the fact that it has 2 disconnected graphs (0,1) and (2,3,4). If we apply the logic
    for both the graphs, then it will work.
---

Why are we using multi_set and not a priority_queue?

> For this problem, we want some DS where we can traverse and which contains our elements in sorted order.
  In a priority queue, we can only do operations like push, pop, top, etc.. We can't iterate over it
    since internally it is implemented using Heap.
  We can iterate over different elements of a multiset because they are ordered and 
    we can traverse over it as well.

Why are we using multi_set and not a set?
> The only difference between a set and a multiset is that multiset can have duplicate values.
> The difference between a vector and a multiset is that is will always remain sorted.
> The difference between a priority queue and a multiset is that is not a Queue so we can pop from the back as well.

---
    Similar Problem:
        1. https://leetcode.com/problems/optimal-account-balancing/
            - The same problem but test cases also have disconnected graphs so we need to implement different soln.
            - DFS/BACKTRACKING based solution written below
            - TC: O(n!) since T(n) = n*T(n-1)
            - Asked in Oyo
*/

//Given the list of M transacations b/w N people, find out the minimum number of transactions required to settle it up!
#include <bits/stdc++.h>
using namespace std;
const int N = 1e6;
int balance[N];
int main()
{
    int i, n, m, u, v, w, poor, x, rich, y;
    cin >> n >> m;
    for(i=0; i<m; i++) {
        cin >> u >> v >> w;
        //u has to pay v an amount w
        balance[u] -= w;
        balance[v] += w;
    }
    
    // multiset of a tuple so that we are also able to keep track of "who" is associated with the transaction.
    // ONLY insert in the multiset IFF balance[i] != 0
    multiset<tuple<int,int>> S;
    for(i=0; i<n; i++) 
        if(balance[i] != 0) S.insert(make_tuple(balance[i], i));
    

    int transactions = 0;
    while(!S.empty()) {

        // Get the smallest and highest element and remove them from the multiset.
        tie(poor, x) = *S.begin(); S.erase(S.begin());
        tie(rich, y) = *S.rbegin(); S.erase(prev(S.end()));
        int amount = min(-poor, rich);
        
        transactions++; //poor pays amount "amount" to rich
        printf("%d pays %d amount to %d\n", x, amount, y);
        poor += amount;
        rich -= amount;
        
        // At most one of these conditions would be true since other one would become 0
        // , or both would become 0 (in the final case -10, 10)
        if (poor) S.insert(make_tuple(poor, x));
        if (rich) S.insert(make_tuple(rich, y));
    }
    
    cout << transactions << endl;   
}

// ---------------------------
// LEETCODE SOLUTION USING DFS
// ---------------------------
// TC: O(n!)
class Solution {
public:
    vector<int> debt;
    
    int minTransfers(vector<vector<int>>& transactions) {
        vector<int> balance(21, 0); // max 21 people involved.
        int ans = 0;
        for(auto t: transactions){
            balance[t[0]] -= t[2];
            balance[t[1]] += t[2];
        }
        
        for(auto b: balance){
            if(b != 0)
                debt.push_back(b);
        }
        return dfs(0);
    }
    
    // Returns the minimum number of transactions needed to settle the debt
    int dfs(int s){
        // Skip the debts if they are 0
        while(s < debt.size() && debt[s] == 0)
            s++;
        
        int res = INT_MAX;
        // Iterate i from s+1 till the end looking for the perfect match of this debt[s]
        // If we have a perfect match (+5, -5), then it will be considered in our soln otherwise
        // near perfect will be taken since we have "min" func. written
        for(int i=s+1; i<debt.size(); i++){
            // If the signs are opposite, then try to balance them
            if(debt[i]*debt[s] < 0){
                // Try to balance debt[i] and debt[s]. It may/maynot be perfect & get the min from this
                debt[i] += debt[s];
                res = min(res, 1+dfs(s+1));
                // Backtrack and then try for other i's looking for a better answer.
                debt[i] -= debt[s];
            }
        }
        return res == INT_MAX ? 0 : res;
    }
    
};
