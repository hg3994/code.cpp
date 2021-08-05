/*

Harshit Gupta | 27th July, 2021
---------------------------------

Problem Statement:

Given a very large file with integers, find the 99% value and its index.
Eg: If the file has 1000 entires, find the 10th largest number


------

Solution: 

	1. If the file is sorted already, we need to see from the back the last 1% (.99*total entries)
	2. If the file not sorted but sortable, then we can sort and apply #1 to it.
	3. If the numbers are within a range for ex: student marks (0-100), then we can have an array of
		size 101 and then iterate over the file to fill in the frequency of all the numbers(0-100) in a hash.
		Once we have the freq of all the numbers & the total number count, we iterate over the freq hash 
		from back and try to find the 1% from the back. Complexity of going through list would be O(n). 
		Finding 99 percentile would take fixed set of iteration, complexity there would be O(1).
	4. QuickSelect: TODO


Questions to Ask Interviewer:
-----------------------------
	1. Are the numbers all positive?
	2. Is the file sorted/ sortable?
	3. Can such a large file fit in memory?
	4. Do the numbers have a range?

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/