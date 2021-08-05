
/*

Harshit Gupta | 5th August, 2021
---------------------------------

Problem Statement:

1. https://leetcode.com/problems/stone-game/
	- Alex and Lee play a game with piles of stones. There are an even number of piles arranged 
		in a row, and each pile has a positive integer number of stones piles[i].
		The objective of the game is to end with the most stones.  The total number of stones is odd, 
		so there are no ties.
		Alex and Lee take turns, with Alex starting first. Each turn, a player takes the entire pile 
		of stones from either the beginning or the end of the row.  This continues until there are no more 
		piles left, at which point the person with the most stones wins.
		Assuming Alex and Lee play optimally, return True if and only if Alex wins the game.
	- Solution is that Alex will always WIN since the number of piles are EVEN.

2. TODO:
	https://leetcode.com/problems/stone-game-ii/
	https://leetcode.com/problems/stone-game-iii/
	...

------

Solution: 

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


// ------------
// STONE GAME 1
// ------------
// Since the number of piles are even, it means that the player who will select first has the choice of
// selecting 1st, 3rd, 5th, ... OR 2nd, 4th, 6th, ...
// So both the players can add the odd numbers and even numbers and the series having a greater sum.
// The number of numbers in both the odd and even indexes are same (since the number of piles is even)
// Since the first player plays first and he knows that if I select the odd numbers I will win, then he will always
// select an odd number and then the other player will be forced to pick up an even number and thus the first player wins.
// NOTE that this will not work if the number of piles are odd since the number of elements in both the odd numbers array
// and the even numbered array are NOT same.
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};


