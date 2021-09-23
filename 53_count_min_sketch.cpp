/* 
Harshit Gupta | 9th February, 2019

https://www.youtube.com/watch?v=ibxXO-b14j4
C++ program for finding frequency of a word/letter/number in an infinite stream of word/letter/number ?

Count-Min Sketch
================

	If you're given an infinite stream of characters and then asked what is the frequency of the letter 'A' in that stream. 
	How are you going to answer this problem? How are you going to store the stream of numbers so that	you're able to answer 
	"What is the frequency of xxx?" at any point of time?
	
	NOTE: When we talk about streams, then we usually expect the answer to the question in O(1) time.

	- Array: Are we going to store everything in an array one by one and then going to calculate the frequency by iterating 
		over the whole thing? Foolish! Stupid! No. We can't store infinite stream of data. We don't have infinite memory.

	- Array (try 2): Are we going to have a frequency array of size 26 and for each character, we will increase the counter of 
		frequency. When asked the frequency of any character, we can tell it quickly in O(1) time by accessing that specific index. 
		Good one. But, is this a general solution? No. Our sample alphabet size isn't limited to 26 or 256 characters. We can have 
		numbers, words, sentences and what not. This solution isn't feasible for the rest of the streams. So, a No-No.
		If this question was just for characters then 256 sized array would have been fine but question also asks us about 
		words/nums/sentences which we cant anser with the 'frequency arrays'

	- HashMaps: Did someone say O(1)? Yes. I'm here. HashMaps are almost the synonyms for the term O(1). Similar to the second try 
		of Arrays, we can solve it for characters. but, what about other type of streams? We can store all the incoming words in our 
		hash-map and then access them in O(1) time provided we have infinite memory. Moreover, if the incoming data is huge, 
		then we won't be able to tell the frequency in O(1) time because hashmaps would have collisions and thus the time tends to O(n). 
		Err.. Not Good.

	- Count-Min Sketch: Yes. This will solve our purpose but at a cost. The data might not be 100% correct but then it will give you 
		a pretty good estimate and the error deviation would decrease on using more and more hash functions.


	Implementation of Count-Min Sketch
	----------------------------------
	Sketch means a 2-D array and we can implement the solution in sub-linear space.
	We need:
		- 'n' hash functions
		- A 2D matrix having 'n' rows and a very large number of columns 'c'.


	The 2D matrix should ideally have 'c' number of columns where 'c' is the maximum output of these hashfunctions.
	We know that is pretty hard to figure out and so we would take a large value MOD M as 'c'. We initialize this 2D matrix as 0.
	
		int countMinSketch[numOfHashFunctions][M] = {0} // M=INT_MAX

	For every input that we get from the stream, we pass it through 'n' functions and then we get 'n' values from it. 
	We increment the values of matrix[h1][h1(input)%M], matrix[h2][h2(input)%M], ... matrix[hn][hn(input)%M]
	We do for all the input streams and keep on incrementing it. 

	When asked the frequency of a particular word/number/sentence, we pass that input into the 'n' hash functions and we will 
	get 'n' different values from them. They should ideally be same, but here comes the probability part, it may vary due 
	to others words/numbers/letters incrementing the values due to hash collisions and this is the reason why we would 
	choose the MINIMUM out of all the 'n' numbers that we get. The probabilistic freqency that we can say after this would 
	be min(matrix[h1][h1(input)%M], matrix[h2][h2(input)%M], ... matrix[hn][hn(input)%M]).

	One thing should be noted that the correct output of this probable output wouldn't be lesser than what is predicted. 
	It would always be equal or more than the given output.

	Interesting Facts about Count Min Sketch
	----------------------------------------
	* The output is probabilistic in nature but with a very good accuracy. Trade of between (Time&Space) with Accuracy.
	* More hash functions and better gets the probability of your answer.
	* The space complexity is sub-linear. It's not constant. Not logarathmic. Not linear. It's sub-linear because of the 
		huge number of columns that we are using in the matrix.
	* The correct output of this probable output wouldn't be lesser than what is predicted. It would always be equal or more 
		than the given output.

	Issue with Count-min sketch and its solution: 
	---------------------------------------------
	What if one or more elements got the same hash values and then they all incremented. So, in that case, the value would have 
	been increased because of the hash collision. Thus sometimes (in very rare cases) Count-min sketch overcounts the frequencies 
	because of the hash functions. So the more hash function we take there will be less collision. The fewer hash functions we take 
	there will be a high probability of collision. Hence it always recommended taking more number of hash functions. 

Solution: 

Paradigm: 

Time Complexity: 

*/

#include <bits/stdc++.h>
using namespace std; 

int main() 
{
    
  return 0; 
} 
