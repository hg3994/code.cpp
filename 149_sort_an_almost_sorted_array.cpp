
/*

Harshit Gupta | 22nd July 2021
---------------------------------

Problem Statement:

Given a sorted n-size array, there are k elements have been changed 
i.e. [1, 3, 5, 6, 4, 2, 12] (it might be changed from [1, 3, 5, 6, 7, 8, 12] with k = 2). 
Important to know is that k is unknown and k is much smaller than n. The task is to re-sort the entire array.
The interviewer wants O(n) solution. 

	What he suggested: 
		a. Break the array into two: one sorted array and one unsorted array e.g. [1, 3, 5, 12] and [6, 4, 2]. O(n) 
		b. Sort the unsorted array. This takes O(klogk) 
		c. Merge two sorted arrays. This takes O(n). 

	Because k is very small, so in the end O(n) + O(klogk) ~= O(n).

------

Solution: 

	1. Find elements which are not sorted by traversing the array.
	2. If an element was found which is larger than the next one, then either it or the following one 
		are out of order (or both).
	3. Keep both of them aside, and remove them from the array.
	4. Continue traversing on the newly obtained array (after removal), from the index which comes before 
		the found element.
	5. This will put aside 2k elements in O(n) time.
	6. Sort 2k elements O(klogk)
	7. Merge two sorted lists which have total n elements, O(n)
		
		Total O(n + klogk)

	For the above array, the resulting arrays will be - [1, 3, 12] and [5, 6, 4, 2] ( 2k elements ). 
	I think the above will give O(n) in worst case if (k << n).

  TC: O(n)+O(klogk) = O(n)
  SC: O(k)



 	NOTE: 
 		1. I think the important and tricky part here is that removing the out-of-order elements this 
 			way will not exceed 2 * k.
		2. We should not modify the array itself because that results in n*k complexity. we need to modify 
			the array into a linked list and then the rest of the steps are the same

Paradigm:
---

*/
