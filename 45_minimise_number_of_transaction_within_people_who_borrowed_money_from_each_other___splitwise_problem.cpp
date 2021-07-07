/* 
Harshit Gupta | 11th January, 2019

https://github.com/rachitiitr/DataStructures-Algorithms/blob/master/Famous-Coding-Interview-Problems/TheSplitwiseProblem.cpp
https://www.youtube.com/watch?v=Vy5PLlpDoks
https://www.geeksforgeeks.org/minimize-cash-flow-among-given-set-friends-borrowed-money/

C++ program for "Minimize Cash Flow among a given set of friends who have borrowed money from each other"

Solution: 
    1) Compute the net amount for every person. The net amount for person ‘i’ can be computed be subtracting sum of all debts 
        from sum of all credits.

    2) Find the two persons that are maximum creditor(Pc) and maximum debtor(Pd). Let the maximum amount to be credited maximum creditor 
        be maxCredit and maximum amount to be debited from maximum debtor be maxDebit.

    3) Find the minimum of maxDebit and maxCredit. Let minimum of two be x. Debit ‘x’ from Pd and credit this amount to Pc

    4) If x is equal to maxCredit, then remove Pc from set of persons and recur for remaining (n-1) persons.

    5) If x is equal to maxDebit, then remove Pd from set of persons and recur for remaining (n-1) persons.

---

Why are we using multi_set and not a priority_queue?

> For this problem, we want some DS where we can traverse and which contains our elements in sorted order.
  In a priority queue, we can only do operations like push, pop, top, etc.. We can't iterate over it
    since internally it is implemented using Heap.
  We can iterate over different elements of a multiset because they are ordered and 
    we can traverse over it as well.

Why are we using multi_set and not a set?
> The only difference between a set and a multiset is that multiset can have duplicate values.

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