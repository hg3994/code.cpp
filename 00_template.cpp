
/*

Harshit Gupta | .........., 2020
---------------------------------

C++ program for ""
------

Solution: 

Time Complexity: 
Space Complexity: =
---
  NOTE: 

*/


#include<bits/stdc++.h>
using namespace std;

// Sort one array according to another array. Modifies the array a and b.
// Input : 2 1 5 4 9 3 6 7 10 8
//         A B C D E F G H I J
// Output : 1 2 3 4 5 6 7 8 9 10 
//          B A F D C G H J E I 
void pairsort(vector<int>& a, vector<int>& b, int n) { 
  vector<pair<int, int>> pairt;
  for (int i = 0; i < n; i++) pairt.push_back(make_pair(a[i], b[i]));
  sort(pairt.begin(), pairt.end());
  for (int i = 0; i < n; i++) { 
	  a[i] = pairt[i].first; 
	  b[i] = pairt[i].second; 
  }
}

// Sorting vector of vectors on some element of the inner vector.
void v_of_v_sort( vector<vector<int>>& p){
  sort(p.begin(), p.end(),
    [](const std::vector<int>& a, const std::vector<int>& b) {
    if(a[0]==b[0]) 
      return a[1] < b[1];
    else
      return a[0] < b[0];
  });
}

// Shifting a vector by 'x' times
// (abcde, 3) -> cdeab
string shift_right_arr(string s, int x) {
  reverse(s.begin(), s.end());
  reverse(s.begin(), s.begin()+x);
  reverse(s.begin()+x, s.end());
  return s;
}

// Set the array to value 0.
// memset(combination,0, sizeof(combination));