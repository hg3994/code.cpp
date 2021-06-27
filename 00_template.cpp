
/*

Harshit Gupta | .........., 2021
---------------------------------

C++ program for ""
------

Solution: 

TC: 
SC:

Paradigm:
---
  NOTE: 

*/


// Approaches
// -----------
// - Two Pointers
// - Sliding Window
// - DP
// - Segment Trees
// - Expand from middle (Paindrome, Geometric Figures)
// - Prefix Sum
// - Priority Queue
// - Stack
// - Making value Negative at some index
// - Intervals: Priority Queue, Stack, DP


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
//  Can be used to sort an array with increasing size of elements (string)
//  Array with String length -> a, Array with strings -> b
// Input : 2 1 5 4 9 3 6 7 10 8 <- "a"
//         A B C D E F G H I J  <- "b"
// Output : 1 2 3 4 5 6 7 8 9 10 
//          B A F D C G H J E I 
void pairsort(vector<int>& a, vector<int>& b) { 
  int n = a.size();
  vector<pair<int, int>> pairt;
  for (int i = 0; i < n; i++) pairt.push_back(make_pair(a[i], b[i]));
  sort(pairt.begin(), pairt.end());
  for (int i = 0; i < n; i++) { 
	  a[i] = pairt[i].first; 
	  b[i] = pairt[i].second; 
  }
}

// Sorting vector of vectors on some element of the inner vector.

// Sort on "endtimes" of intervals can be done like this:, 
void v_of_v_sort( vector<vector<int>>& p){
  sort(p.begin(), p.end(),
    [](const std::vector<int>& a, const std::vector<int>& b) {
    if(a[1]==b[1]) 
      return a[0] < b[0];
    else
      return a[1] < b[1];
  });
}

// Sort on start times can simply be done like this
void v_of_v_sort( vector<vector<int>>& p){
  sort(p.begin(), p.end());
}

// Shifting a vector by 'x' times
// (abcde, 3) -> cdeab
string shift_right_arr(string s, int x) {
  reverse(s.begin(), s.end());
  reverse(s.begin(), s.begin()+x);
  reverse(s.begin()+x, s.end());
  return s;
}

void print_arr(string message, vector<int> a){
    cout<<message<<" ";
    for(auto e: a){
        cout<<e<<" ";
    }
    cout<<endl;
}

// Set the array to value 0 / -1 (Not for other values)
// int combination[sum+1];
// memset(combination,0, sizeof(combination));

// Resize a vector
// v.resize(5, 10); // 5 elements , init to 10
// Append two vectors
// first.insert(first.end(), second.begin(), second.end());

// Convert set to a vector
// vector<int> v(s.begin(), s.end());
// copy(s.begin(), s.end(), v.begin());

// Convert a character to a string
// string s; s += 'a';
// String s has a character 'a' now.
// XXXX string s = 'a'; // FAIL XXXX

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


// map.find(): O(logN)
//  Use it if you want to store all the key, values in sorted order. Internally it is implemented using BST.

// set.find(): O(logN)
//  Use it if you want to have a sorted set. Internally it is implemented using BST.

// unordered_map.find(): O(1)
//  Use it if you want to have a hash map having key value pairs. It is unordered.

// unordered_set.find(): O(1)
//  Use it if you want to have a set with faster retrival. Consider this as a hashmap
//  with element as keys and values as true. It is simpler to use this then that hashmap.


// BST Examples: set, multiset
// HashTable Example: unordered_set, unordered_multiset