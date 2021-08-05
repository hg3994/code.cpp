


/*

Harshit Gupta | 27th July, 2021
---------------------------------

Problem Statement:
	The ball is present at Nth stair and we want to calculate the number of ways 
		it can reach the ground.
	1. Some of the steps are sticky so the ball would stop after it
	2. In an odd turn the ball can take 1,2 or 4 steps.
	3. In an even turn, the ball can take 1,3 or 4 steps.
	
  	3 ()
	----
  		|2
		----
		  	|1
			----
		  		|_0_


Example: You're at 3rd step and 2nd step is stick
odd steps: [1,2,4]
even steps: [1,3,4]

1st step: 
    3->2 by taking 1 step(XXX-Sticky), 
    3->1 by taking 2 steps (looks fine), 
    3->0 by taking 4 steps (Ans=1)

2nd Step: You're already at step 1 and that's the only possibility
	1->0 by taking 1 step
	1->0 by taking 3 steps
	1->0 by taking 4 steps

So in total you can reach there is 4 ways.

------

Solution: Recursion + Memoization.

    TC: O(n) since it calculates it for each N one time.
    SC: O(n) each for visitedOdd and visitedEven.

Paradigm: Recursion + Memoization.
---
    NOTE: 

    Similar Questions:
        1.

*/

#include <bits/stdc++.h>
using namespace std;
#define N 5
unordered_map <int, bool> sticky = {};
vector<int> visitedOdd(N+1, -1);
vector<int> visitedEven(N+1, -1);

int numberOfWaysToReachN(int n, bool isOdd){
	if(sticky[n])
		return 0;
	if(n <= 0)
		return 1;

	if(isOdd){
		if(visitedOdd[n] == -1)
			visitedOdd[n] =	numberOfWaysToReachN(n-1, !isOdd)+
							numberOfWaysToReachN(n-2, !isOdd)+
							numberOfWaysToReachN(n-4, !isOdd);
		return visitedOdd[n];
	}

	else {
		if(visitedEven[n] == -1)
			visitedEven[n] = numberOfWaysToReachN(n-1, !isOdd)+
							 numberOfWaysToReachN(n-3, !isOdd)+
							 numberOfWaysToReachN(n-4, !isOdd);
		return visitedEven[n];	
	}

}

int main() {
	cout<<numberOfWaysToReachN(N, true)<<endl;
	return 0;
}
