
/*

Harshit Gupta | .........., 2021
---------------------------------

Problem Statement:

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


// Approaches
// -----------
// - Two Pointers
// - Binary Search (if input in sorted)
// - Sliding Window
// - DP
// - Expand from middle (Paindrome, Geometric Figures)
// - Prefix Sum
// - Left to Right and Right to Left Parsing (Rain Water)
// - Priority Queue
// - Stack
// - Making value Negative at some index
// - Intervals: Priority Queue, Stack, DP
// - Backtracking
// - Union Find
// - Deque (Sliding Window Maximum)
// - Segment Trees


// Subarray Problems:
// -----------------
//   1. Longest Increasing Subarray                                 (Simple traversal)
//   2. Longest Common Subarray                                     (DP: dp[i][j] = dp[i-1][j-1]+1)
//   3. Longest Palindromic Subarray                                (Expand from Middle)
//   4. Maximum Sum Subarray                                        (Kadane)
//   5. Maximum Absolute Sum Subarray                               (Kadane)
//   6. Maximum Product Subarray                                    (Kadane)
//   7. Maximum Number of each subarray of size K                   (Deque)
//   8. Maximum Sum of Subarrays of size K                          (Sliding Window)
//   9. Num of Subarrays with Product < K                           (Sliding Window)
//  10. Minimum length Subarray with Sum >= K                       (Sliding Window)
//  11. Num of Subarrays with sum = K                               (Prefix Sum Freq in HashMap)
//  12. Maximum size of Subarray with sum = K                       (Prefix Sum Index in HashMap)
//  13. Longest Subarray without repeating chars                    (Sliding Window)
//  14. Longest Subarray with at most K distinct character          (Sliding Window)
//  15. Longest Subarray of same char with K replacements           (Sliding Window)
//  15. Minimum length subarray with all chars from another String  (Sliding Window)

// Coin Changing
// -------------
// 1. Number of ways you can create a sum :         dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
// 2. List the ways you can create a sum :          dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]]; +  Backtracking
// 3. Can we create a sum? :                        dp[i][j] = dp[i-1][j] || dp[i-1][j-coins[i-1]]; 
// 4. Fewest number of coins used to create a sum : dp[i][j] = min(dp[i][j-coins[i]]+1, dp[i-1][j]);


// Data Structures
// ---------------
// 1. LRU: A DLL with nodes in the front meaning most recently used and back means least recently used, so we EVICT the keys from back
     list<pair<int, int>> dll; unordered_map<int, list<pair<int, int>>::iterator> map;
// 2. LFU:
    // Map to store the key and value. Also, as a part of the value, we will be storing the address of the DLL node which contains the key.
    unordered_map<Key_t, Node> m_values;
    // Map to store the frequency of each key
    unordered_map<Key_t, Count_t> m_counts;
    // Map to store the frequencies as keys and a DLL associated to them which are keys for that frequency.
    // In this DLL, the back is least recently used while the front is the most freshly added node.
    unordered_map<Count_t, list<Key_t>> m_countKeyMap;
    
    // This will contain the lowest frequency so that we can refer the m_countKeyMap hash and get the keys for the lowest freq
    int m_lowestFrequency;
    int m_maxCapacity;
// 3. GetRandom(): Vector + HashMap
// 4. First Non-repeating Char in Stream: Queue + Hashmap
// 5. Topological Sort: vector<int> in_degree(g.V, 0); queue<int> q;
// 6. Rate Logger Limiter: unordered_map <string, int> m;

// Ways to represent graphs
// ------------------------
// Directed Graph:
//  1. unordered_map<string, vector<string>> graph                  ||  A->B, A->C means map[A]=[B,C]
//  2. unordered_map<string, unordered_map<string, double>> graph;  ||  Graph: {a: {b: 2}, b: {a: 0.5, c: 3}, c: {b: 0.33}}

// Graph Problems
// --------------
// 1. Number of connected nodes in a graph: DFS, UnionFind
// 2. Check if there exists a path between two nodes in a weighted directed graph & return product of weights: Backtracking
// 3. 

// Palindromes
// -----------
// These types of questions can be of two types: 
//  1. Checking if X is a palindrome or not? IF X is palindrome by removing Y chars?
//      Can be solved by using two pointers i and j and traversing from start and end checking if the letters are same.
//  2. Count the number of Palinromes in X
//      Expand from middle


// BFS
// ---
// 1. Binary Tree: Simple traight-forward using a queue.
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if (root == NULL)
            return ans;
        queue<TreeNode*> q;
        q.push(root);
        while(!q.empty()){
            int size = q.size();
            vector<int> levelNodes;
            for(int i=0; i<size; i++){
                TreeNode* frontNode = q.front();
                q.pop();
                levelNodes.push_back(frontNode->val);
                if(frontNode->left)
                    q.push(frontNode->left);
                if(frontNode->right)
                    q.push(frontNode->right);
            }
            ans.push_back(levelNodes);
        }
        return ans;
    }

// 2. Matrix: Must use a visited[] array + queue
    int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
        int n = grid.size();
        
        if(grid[0][0] == 1)
            return -1;
        
        queue<pair<int, int>> q;
        vector<int> a(n, 0);
        vector<vector<int>> visited(n, a);
        int moves = 1;
        q.push(make_pair(0, 0));
        visited[0][0] = 1;
        
        while(!q.empty()){
            int size = q.size();
            for(int i=0;i<size; i++){
                pair<int, int> f = q.front(); q.pop();
                
                if (f.first == n-1 && f.second == n-1){
                    return moves;
                }
                
                vector<int> x = {0, 1, 1,  1,  0, -1, -1, -1};
                vector<int> y = {1, 1, 0, -1, -1, -1,  0,  1};
                
                for(int i=0;i<8;i++){
                    if ( f.first+x[i] >= 0 && f.first+x[i] < n 
                       && f.second+y[i] >=0 && f.second+y[i] < n
                       && grid[f.first+x[i]][f.second+y[i]] == 0
                       && visited[f.first+x[i]][f.second+y[i]] == 0){
                        
                        q.push(make_pair(f.first+x[i],f.second+y[i]));
                        visited[f.first+x[i]][f.second+y[i]] = 1;
                    }
                }   
            }
            moves++;
        }
        return -1;
    }

// 3. 


// DFS
// ---

// 1. 4 Way DFS with visited returning the area it covered.
    class Solution {
        
        int dfs (vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j) {
            if(i<0 || i==grid.size() || j<0 || j==grid[0].size() || visited[i][j] == 1 || grid[i][j] == 0)
                return 0;
            visited[i][j] = 1;
            return 1+dfs(grid, visited, i+1, j)+dfs(grid, visited, i-1, j)+dfs(grid, visited, i, j+1)+dfs(grid, visited, i, j-1);
        }
        
    public:
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int m = grid.size(), n = grid[0].size();
            vector<int> tmp(n, 0); vector<vector<int>> visited (m, tmp);
            int maxArea = 0, area;
            for(int i=0; i<m; i++) {
                for(int j=0; j<n; j++) {
                    if (grid[i][j] == 1 &&  visited[i][j]==0){
                        area = dfs(grid, visited, i, j);
                        maxArea = max(area, maxArea);
                    }
                }
            }
            return maxArea;
        }
    };







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
int combination[sum+1];
memset(combination,0, sizeof(combination));

// Resize a vector
v.resize(5, 10); // 5 elements , init to 10
// Append two vectors
first.insert(first.end(), second.begin(), second.end());

// Convert set to a vector
vector<int> v(s.begin(), s.end());
copy(s.begin(), s.end(), v.begin());

// Convert a character to a string
// string s; s += 'a';
// String s has a character 'a' now.
// XXXX string s = 'a'; // FAIL XXXX

// Convert an integer to a string
string s = to_string(num)

// Convert a string to an integer
int n = stoi(s);

// Create 2D vector with size mxn initialized with 0.
vector<int> tmp(n, 0);
vector<vector<int>> visited (m, tmp);

// Passing a vector(or anything) by reference
void myfunc(vector<int>& res)

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


// GOOGLE
// ------
// Time Management - 20 mins
// 2 questions - 45mins.
// Practice - Talk to your self.
// 1st round: HashMap, Array, Trie, DFS, BFS.
// Revision - DP & Graph
// Can you sort 1 million numbers?
// Don't get nervous.
// Go with Hints - Last Resort!