
/*

Harshit Gupta | .........., 2021
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

// Tree Node
struct TreeNode {
    int data;
    struct TreeNode *left, *right;
    TreeNode(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};
typedef struct TreeNode TreeNode;

// LL Node
struct LLNode{
    int data;
    struct LLNode *next;
    LLNode(int data){
        this->data = data;
        this->next = NULL;
    }
};
typedef struct LLNode LLNode;


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

// Set the array to value 0 / -1 (Not for other values)
// int combination[sum+1];
// memset(combination,0, sizeof(combination));

// Convert an integer to a string
// string s = to_string(num)

// Convert a string to an integer
// int n = stoi(s);

// Create 2D vector with size mxn initialized with 0.
// vector<int> tmp(n, 0);
// vector<vector<int>> dp (m, tmp);

// Passing a vector(or anything) by reference
// void myfunc(vector<int>& res)

// Creating a hash map
// unordered_map <int, int> parents;
// Set: parent[1] = 1
// Check: if (parent.find(1) == parent.end() ) { not found }
// If you want to add pair as a key, then we need to provide a hash function as well  
// unordered_map<pair<string, string>, int, boost::hash<pair<string, string>>> m;

// Creating an unordered_set
// unordered_set <TreeNode*> myset;
// if(myset.find(node) == myset.end())
//    node not found in set
// Iterate through a set<>
// for (auto elem : myset) { cout << elem << " , "; }

// Pair
// Declare: pair<int, int> p
// Create:  make_pair(1, 2)
// Values:  p.first, p.second
