
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for "Given a vector of integers, return true if it has pythagorean triplets in it"

The equation that Pythagorean Triplets follows are: a^2+b^2 = c^2
So, we need to find if there exists three numbers a,b & c which satisfy the given equation

Ex1:   [1,3,2,5,4]
  Output: true
  Explanation: 3,4,5 are satufying the condition

Ex2:  [1,0,2]
  Output: false

------
https://ideone.com/TS5YkJ

Solution: 1. By Brute Force it will take you O(n3) time using 3 for loops.
  2. We can decrease the complexity of the code by using a hash map
    - Convert the arrays to store square of the numbers
    - Store all these numbers in a map with values as index so that we know if a number X is present in O(1) time.
    - Iterate and fix the first number arr[i]
      - Iterate and get the second number arr[j]
        - If map contains arr[i]+arr[j], then it means that there exists a triplet

  [1,3,2,5,4]
  [1,9,4,25,16] -> store all in a map
  [  |      | ] -> When it adds 9 and 16 and see 25 is there in the map, it knows that there is a triplet.

  NOTE: A tricky situation is example 2 where the update array after squaring would be [1,0,4]. 
    When i=1, j=0, 1+0=1 would be present in the map, so we need to check whether the sum of arr[i]+arr[j] is 
    NOT being referred either from i or j. We can do this by checking the index!
    If map[arr[i]+arr[j]] != i && != j then we are sure that they are three distinct elements.

    This is a one-off case since usually all pythogorean triplets are 3 distinct numbers.


Time Complexity: O(n2)
Space Complexity: O(n) for map.

Paradigm: HashMap

*/


#include <bits/stdc++.h>
using namespace std;

bool hasPythTriplets (vector<int> arr) {
  int n = arr.size();
  unordered_map<int, int> map;
  
  for(int i=0; i<n; i++){
    arr[i] = arr[i]*arr[i];
    map[arr[i]] = i;
  }
  
  for(int i=0; i<n-1; i++){
    for(int j=i+1; j<n; j++){

      if (map.count(arr[i] + arr[j]) && map[arr[i]+arr[j]] != i && map[arr[i]+arr[j]] != j)
        return true;
    }
  }
  return false;
}


int main() {
	vector<int> arr = {1,0,1,3,4};
	cout<<hasPythTriplets(arr)<<endl;
}