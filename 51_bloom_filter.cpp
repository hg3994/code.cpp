/* 
Harshit Gupta | 8th February, 2019

https://www.youtube.com/watch?v=Bay3X9PAX5k&t=30s
https://www.geeksforgeeks.org/bloom-filters-introduction-and-python-implementation/
https://blog.medium.com/what-are-bloom-filters-1ec2a50c68ff
https://www.quora.com/What-are-the-best-applications-of-Bloom-filters

C++ program to test whether an element is a member of a set. 

BLOOM FILTERS
=============

	If you're given a set of strings and you're asked if a particular string "cat" is present in that set or not. How
	are you going to search it?

	- Linear Search? Bad Idea. It taken a hell lot of time O(n)
	- Binary Search? Keep the array sorted while the set is being made. The insertion takes O(logn) time and 
			searching takes O(logn) as well.
	- HashMaps? This takes only O(1) time in terms of access but what if the set is huge? Even for better hash functions
			collisions will increase and thus the time wouldn't be O(1) but linear O(n). Also, to save the hashmap, the space
			required is a lot.
	- Bloom Filters? Yes. They take O(1) time as well as O(1) space to keep the records.


	A Bloom filter is a space-efficient probabilistic data structure that is used to test whether an 
		element is a member of a set. 

	For example, checking availability of username is set membership problem, where the set is the list of all 
	registered username. The price we pay for efficiency is that it is probabilistic in nature that means, 
	there might be some False Positive results. False positive means, it might tell that given username is 
	already taken but actually it’s not.
	But, it will never tell us that a username is available but actually it is not. And this is what that matters.

	Working of Bloom Filter
	-----------------------
	An empty bloom filter is a bit array of m bits, all set to zero, like this:
		[0 0 0 0 0 0 0 0 0 0]

	We need k number of hash functions to calculate the hashes for a given input. When we want to add an item in the 
	filter, the bits at k indices h1(x), h2(x), … hk(x) are set, where indices are calculated using hash functions.
		
			Example – Suppose we want to enter “geeks” in the filter, we are using 3 hash functions and a bit array of 
			length 10, all set to 0 initially. First we’ll calculate the hashes as following :

					h1(“geeks”) % 10 = 1
					h2(“geeks”) % 10 = 4
					h3(“geeks”) % 10 = 7

			Note: These outputs are random for explanation only.
			
			Now we will set the bits at indices 1, 4 and 7 to 1

			[1 0 0 1 0 0 1 0 0 0]
		
			Again we want to enter “nerd”, similarly we’ll calculate hashes

					h1(“nerd”) % 10 = 3
					h2(“nerd”) % 10 = 5
					h3(“nerd”) % 10 = 4

				Set the bits at indices 3, 5 and 4 to 1

			[1 0 1 1 1 0 1 0 0 0]

	Now if we want to check “geeks” is present in filter or not. We’ll do the same process but this time in reverse 
	order. We calculate respective hashes using h1, h2 and h3 and check if all these indices are set to 1 in the 
	bit array. If all the bits are set then we can say that “geeks” is probably present. If any of the bit at these 
	indices are 0 then “geeks” is definitely not present.

	The question is why we said “probably present”, why this uncertainty. Let’s understand this with an example. 

	Suppose we want to check whether “cat” is present or not. We’ll calculate hashes using h1, h2 and h3

				h1(“cat”) % 10 = 1
				h2(“cat”) % 10 = 3
				h3(“cat”) % 10 = 7

	If we check the bit array, bits at these indices are set to 1 but we know that “cat” was never added to the filter. 
	Bit at index 1 and 7 was set when we added “geeks” and bit 3 was set we added “nerd”.


	So, because bits at calculated indices are already set by some other item, bloom filter erroneously claim that 
	“cat” is present and generating a false positive result. Depending on the application, it could be huge downside 
	or relatively okay.

	We can control the probability of getting a false positive by controlling the size of the Bloom filter. 
	More space means fewer false positives. If we want decrease probability of false positive result, we have to 
	use more number of hash functions and larger bit array. This would add latency in addition of item and checking 
	membership.

	Space Efficiency
	----------------
	If we want to store large list of items in a set for purpose of set membership, we can store it in hashmap, 
	tries or simple array or linked list. All these methods require storing item itself, which is not very memory 
	efficient. For example, if we want to store “geeks” in hashmap we have to store actual string “ geeks” as a key 
	value pair {some_key : "geeks"}.
	Bloom filters do not store the data item at all. As we have seen they use bit array which allow hash collision. 
	Without hash collision, it would not be compact.


	Interesting Properties of Bloom Filters
	---------------------------------------
	- Unlike a standard hash table, a Bloom filter of a fixed size can represent a set with an arbitrarily 
			large number of elements.
	- Adding an element never fails. However, the false positive rate increases steadily as elements are added 
			until all bits in the filter are set to 1, at which point all queries yield a positive result.
	- Bloom filters never generate false negative result, i.e., telling you that a username doesn’t exist 
			when it actually exists.
	- Deleting elements from filter is not possible because, if we delete a single element by clearing bits at 
			indices generated by k hash functions, it might cause deletion of few other elements. 
			Example – if we delete “geeks” (in given example below) by clearing bit at 1, 4 and 7, we might end up 
			deleting “nerd” also Because bit at index 4 becomes 0 and bloom filter claims that “nerd” is not present.



Time Complexity: O(K) where K are the number of Hash Function

*/

#include <bits/stdc++.h>
using namespace std; 

int main() 
{
    
    return 0; 
} 
