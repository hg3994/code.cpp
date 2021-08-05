/*

Harshit Gupta | 27th July, 2021
---------------------------------

Problem Statement:

Given a list of item IDs and a cooldown K, create a random item generator class with a method that selects a random item 
	id which has not been previously selected in the last K calls.

------

Solution: 

	1. Rejection Sampling approach using a hashmap for each ID. -> O(k)
	2. If we know the the call number or can have a variable keep count of the number of times, I've called this,
		then we can simply keep a map of number and the instant it came(i). If it comes again and it is in the map, 
		we check the time it came, if it came at a iteration j where j-i>k, then output the random number, 
		otherwise generate random again.

Paradigm:
---
    NOTE: 

    Similar Questions:
        1. https://leetcode.com/problems/logger-rate-limiter/

*/