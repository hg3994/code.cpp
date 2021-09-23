
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


/*

Approaches
-----------
    - Two Pointers
    - Binary Search (if input in sorted)
    - Sliding Window
    - DP
    - Expand from middle (Paindrome, Geometric Figures)
    - Prefix Sum
    - Left to Right and Right to Left Parsing (Rain Water, Distnace of 1s from each element in binary array)
    - Priority Queue
    - Stack
    - Making value Negative at some index
    - Intervals: Priority Queue, Stack, DP
    - Backtracking
    - Union Find
    - Deque (Sliding Window Maximum)
    - Segment Trees


Subarray Problems:
-----------------
     1. Longest Increasing Subarray                                 (Simple traversal)
     2. Longest Common Subarray                                     (DP: dp[i][j] = dp[i-1][j-1]+1)
     3. Longest Palindromic Subarray                                (Expand from Middle)
     4. Maximum Sum Subarray                                        (Kadane)
     5. Maximum Absolute Sum Subarray                               (Kadane)
     6. Maximum Product Subarray                                    (Kadane)
     7. Maximum Number of each subarray of size K                   (Deque)
     8. Maximum Sum of Subarrays of size K                          (Sliding Window) (43, 123)
     9. Num of Subarrays with Product < K                           (Sliding Window)
    10. Minimum length Subarray with Sum >= K                       (Sliding Window) (125)
    11. Num of Subarrays with Sum = K                               (Prefix Sum Freq in HashMap) (90)
    12. Maximum size of Subarray with Sum = K                       (Prefix Sum Index in HashMap) (90)
    13. Longest Subarray without repeating chars                    (Sliding Window)
    14. Longest Subarray with at most K distinct character          (Sliding Window)
    15. Longest Subarray of same char with K replacements           (Sliding Window) (124)
    15. Minimum length subarray with all chars from another String  (Sliding Window) (128)

Coin Changing
-------------
Given some numbers and a sum...
    1. ( 1) Number of ways you can make a sum with Infinite supplies of some Coins:               dp[i][j] = dp[i-1][j] + dp[i][j-coins[i-1]];
    2. (69) List the ways you can make a sum with Infinite supplies of some Coins:                dp[i][j] = dp[i-1][j] + dp[i][j-coins[i]]; + Backtracking /  Only Backtracking.
    3. (21) Can we make a sum with a single coin of some given coins :                            dp[i][j] = dp[i-1][j] || dp[i-1][j-coins[i-1]]; 
    4. (80) Minimum number of coins used to make a sum with Infinite supplies of some Coins:      dp[i][j] = min(dp[i][j-coins[i]]+1, dp[i-1][j]);
    5. ( 9) Minimum number of coins used to make a sum with a single coin of some coins:          Backtracking to find the coin sets which make the sum and then get the minimum size from them.
    6. (49) Knapsack (maximize val with single items of wt & :                                    dp[i][j] = max(dp[i-1][j], val[i-1]+dp[i][j-weight[i-1]])
                val with total Weight of Knapsack W)


Stock Buy-Sell
--------------
Best Time to Buy and Sell Stock to make most profit with:
    1. (54) 1 Transaction:
            for(int i=0; i<prices.size(); i++){
                minTillNow = min(minTillNow, prices[i]);
                maxProfit = max(maxProfit, prices[i]-minTillNow);
            }

    2. (75) Infinite Transactions:
            for(int i=1;i<prices.size();i++){
                profit += max(prices[i]-prices[i-1] ,0);
            }

    3. (76) K transactions / 2 Transactions (k=2)
            for(long int i=0;i<d;i++)
                dp[0][i] = 0;
            for(long int i=0;i<k+1;i++)
                dp[i][0] = 0;
            for(long int i=1;i<k+1;i++){
                long int max_diff = dp[i][0] - prices[0];
                for(long int j=1; j<d; j++){
                    max_diff = max(max_diff, dp[i-1][j]-prices[j]);
                    dp[i][j] = max(dp[i][j-1], max_diff+prices[j]);
                }
            }
            return dp[k][d-1];


Palindromes
-----------
    These types of questions can be of two types: 
     1. Checking if X is a palindrome or not? IF X is palindrome by removing Y chars?
            Can be solved by using two pointers i and j and traversing from start and end checking if the letters are same.
     2. Count the number of Palinromes in X
        - (82) Number of Palindromic Substrings in a String
            Expand from middle

Binary Search Problems
----------------------
    1. (93)  Find the index of a target element in a sorted rotated array + Find the index of the lowest element in a sorted rotated array.
        // Find index of the lowest element first
        int low = 0, high = n-1;
    
        // Finding the index of the lowest element
        while(low < high){
            int mid = low + (high-low)/2;
            if (v[mid] > v[high])
                low = mid+1;
            else
                high = mid;
        }
        // Now low = high = index of the lowest element

        if (index_lowest == 0)
            low=0, high=n-1;
        else if (target >= v[0])
            low=0, high=index_lowest-1;
        else if (target < v[0])
            low=index_lowest, high=n-1;
        
        // Now do binary search from low to high
        while(low <= high){
            int mid = low + (high-low)/2;
            if(v[mid] == target)
                return mid;
            else if (v[mid] > target)
                high = mid-1;
            else 
                low = mid+1;
        }

    2. 

Data Structures for common problems
-----------------------------------
    1. LRU: A DLL with nodes in the front meaning most recently used and back means least recently used, so we EVICT the keys from back
            list<pair<int, int>> dll; unordered_map<int, list<pair<int, int>>::iterator> map;

    2. LFU:

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

    3. GetRandom(): Vector + HashMap
    4. First Non-repeating Char in Stream: Queue + Hashmap
    5. Topological Sort: vector<int> in_degree(g.V, 0); queue<int> q;
    6. Rate Logger Limiter: unordered_map <string, int> m;
    7. Design HashMap:
         a. If the size of numbers are given, then a simple vector can act as a HashMap since it allows O(1) access.
         b. vector<list<pair<int,int>>> map;
            size_t m_size = 10000;
               Accessing elements by key%m_size


Ways to represent graphs
------------------------
Directed Graph:
    1. Normal Graph with Char Nodes:    
                                        unordered_map<string, vector<string>> graph  ||  A->B->C means {A: [B], B: [C], C: []}
    2. Normal Graph with Int Nodes:     
                                        vector<vector<int>> graph                    ||  0-->1-->2 means [[1], [2], []]
    3. Weighted Graph with Char Nodes:        
                        unordered_map<string, unordered_map<string, double>> graph;  ||  

                                                              a/b=2     b/c=3
                                                           a-------->b-------->c     ||  Graph: {a: {b: 2}, b: {a: 0.5, c: 3}, c: {b: 0.33}}
                                                           a<--------b<--------c     ||
                                                             b/a=1/2   c/b=1/3


Undirected Graph:
    1. Normal Graph with Char Nodes:   unordered_map<string, vector<string>> graph   ||  A--B--C means {A: [B], B: [A,C], C: [B]}
    2. Normal Graph with Int Nodes:    vector<vector<int>> graph                     ||  0--1--2 means [[1], [0,2], [1]]


    * Difference between Adjacency Matrix vector<vector<int>> and Adjacency List vector<vector<int>>
            0----1
            |
            |--2

        Adjacency Matrix: 
           [[0, 1, 1],
            [1, 0, 0],
            [1, 0, 0]]

        Adjacency List:
            [[1,2], [0], [0]]

        So basically, Adjacency MAtrix will store 0s for no edge and 1 for edge but Adjacency List will store only the nodes to which the index i has edge


Graph Problems
--------------
    1. Number of connected nodes in a graph: DFS, UnionFind
    2. Check if there exists a path between two nodes in a weighted directed graph & return product of weights: Backtracking
    3. Check if there exists a path between two nodes in an undirected graph: BFS/DFS/UnionFind


UNION FIND Variations
---------------------
    1. int count=n initially but then each union decreases count. Finally this count tells number of connected components (graph) / number of islands (matrix)
    2. vector<int> size(n,1) tells the size of each component. On every union, we make increase the sizes of the leader node by an amount of "size of non-leader node".
        We can return this size from the Union method and it will be telling us the size of the component after Union. 
        This is helpful in finding Max Area of a component / Largest Graph of Connected Components.
    3. Union Function returning TRUE/FALSE if the nodes belong to the different/same groups. 
        This can help us figure out if there exists a cycle in the graph. On adding which edge will the graph turn cyclic. The removal of this edge will make the graph non-cyclic.
        This can also help in telling "Is node X reachable from node Y"

Matrix / Island Questions:
--------------------------     
1. Number of Islands: DFS (Changing 1 to 0 so we dont need visited[])

    void DFS(vector<vector<char>>& grid, int r, int c){        
        if(r<0 || r==grid.size() || c<0 || c==grid[0].size() || grid[r][c]=='0')
               return;
           grid[r][c] = '0';
           DFS(grid, r-1, c); DFS(grid, r+1, c); DFS(grid, r, c+1); DFS(grid, r, c-1);
    }
    for(int i=0; i<m;i++){
       for(int j=0;j<n;j++){
           if(grid[i][j]=='1'){
               ans++;
               DFS(grid, i, j);
           }
       }
    }
    return ans;

2. Max Area of an Island: DFS with visited returning area

    int dfs (vector<vector<int>>& grid, vector<vector<int>>& visited, int i, int j) {
        if(i<0 || i==grid.size() || j<0 || j==grid[0].size() || visited[i][j] == 1 || grid[i][j] == 0)
            return 0;
        visited[i][j] = 1;
        return 1+dfs(grid, visited, i+1, j)+dfs(grid, visited, i-1, j)+dfs(grid, visited, i, j+1)+dfs(grid, visited, i, j-1);
    }
    for(int i=0; i<m; i++) {
        for(int j=0; j<n; j++) {
            if (grid[i][j] == 1 &&  visited[i][j]==0){
                area = dfs(grid, visited, i, j);
                maxArea = max(area, maxArea);
            }
        }
    }
    return maxArea;

====================================================================================================================
====================================================================================================================
====================================================================================================================

BFS
---
1. Binary Tree: Simple straight-forward using a queue. (Level Order Traversal - 3)

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

2. Matrix: Must use a visited[] array + queue (Shortest Path between two nodes in a matrix - 28)

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

3. Undirected Graph (Adjacency Matrix): We iterate over each row and check if not visited, we do BFS and insert all elements in its row (94)

    class Solution {
    public:
        int findCircleNum(vector<vector<int>>& isConnected) {
            int n = isConnected.size();
            vector<int> visited(n, 0);
            queue<int> q;
            int ans=0;
            for(int i=0; i<n; i++){
                if(visited[i] == 0){
                    q.push(i);
                    while(!q.empty()) {
                        int top = q.front();
                        q.pop();
                        visited[top] = 1;
                        for(int j=0; j<n; j++){
                            if(isConnected[top][j]==1 && visited[j]==0)
                                q.push(j);
                        }
                    }
                    ans++;
                }
            }
            return ans;
        }
    };

4. Undirected Graph (Adjacency List): Usual BFS with visited[] array. (Check if a path exists between two given nodes in a graph) (184)

    class Solution {
    public:
        bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
            vector<vector<int>> graph(n);

            for(int i=0; i<edges.size(); i++) {
                graph[edges[i][0]].push_back(edges[i][1]);
                graph[edges[i][1]].push_back(edges[i][0]);
            }
            
            queue<int> q;
            vector<int> visited(n, 0);
            q.push(start);
            visited[start] = 1;
            while(!q.empty()){
                int top = q.front();
                q.pop();
                if(top == end)
                    return true;

                for(int i=0; i<graph[top].size(); i++){
                    if(visited[graph[top][i]] == 0){
                        q.push(graph[top][i]);
                        visited[graph[top][i]] = 1;
                    }
                }
            }
            return false;
        }
    };


====================================================================================================================
====================================================================================================================
====================================================================================================================

DFS
---
1. MATRIX: 4 Way DFS with visited[][] returning the area it covered.
    
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

2. Undirected Graph (Adjacency Matrix): Check number of provinces (94)

    class Solution {
    public:
        void dfs(vector<vector<int>>& grid, vector<int>& visited, int i){
            for(int j=0; j< grid.size(); j++){
                if(i!=j && grid[i][j] == 1 && visited[j] == 0){
                    visited[j] = 1;
                    dfs(grid, visited, j);
                }
            }
        }
        
        int findCircleNum(vector<vector<int>>& grid) {
            int n = grid.size();
            int count = 0;
            vector<int> visited(n,0);
            
            for(int i=0; i<n; i++){
                if(visited[i] == 0) {
                    dfs(grid, visited, i);
                    count++;
                }
            }
            return count;
        }
    };

3. Undirected Graph (Adjacency List): DFS with visited[] on an undirected graph (Check if a valid path is present between two nodes-184)

    class Solution {
    public:
        
        bool dfs(vector<vector<int>>& graph, vector<int>& visited, int current, int end) {
            if(current == end)
                return true;
            if(visited[current])
                return false;
            
            visited[current] = 1;
            
            for(int i=0; i<graph[current].size(); i++){
                if(dfs(graph, visited, graph[current][i], end))
                    return true;
            }
            
            return false;
        }
        
        bool validPath(int n, vector<vector<int>>& edges, int start, int end) {
            vector<vector<int>> graph(n);
            for(int i=0; i<edges.size(); i++) {
                graph[edges[i][0]].push_back(edges[i][1]);
                graph[edges[i][1]].push_back(edges[i][0]);
            }
            vector<int> visited(n, 0);
            return dfs(graph, visited, start, end);
        }
    };



====================================================================================================================
====================================================================================================================
====================================================================================================================

Backtracking
------------

1. MATRIX: Classic Backtracking in Sudoku: Both loops present together

    bool solve(vector<vector<char>>& board){
        for(int i=0;i<9;i++){
            for(int j=0;j<9;j++){
                if(board[i][j] == '.'){
                    for(int k=0;k<9;k++){
                        if(isValidPlacement(board, i, j, k+'1')){
                            board[i][j] = '1'+k;
                            if(solve(board))
                                return true;
                            else
                                board[i][j] = '.';
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

2. MATRIX: Classic Backtracking in NQueen: 1 loops present and other by argument. Permutations of a string also very similar (except it runs for 1D string)

    void solve(vector<vector<int>>& board, vector<vector<string>>& res, int col){
        int n = board.size();
        if(col == n) {
            vector<string> s = convertAns(board);
            res.push_back(s);
            return;
        }
        
        for(int i=0; i<n; i++){
            if(board[i][col] == 0 && isValid(board, i, col)) {
                board[i][col] = 1;
                solve(board, res, col+1);
                board[i][col] = 0;
            }
        }
    }
    solve(board, res, 0);

    ---

    void permuteHelper(vector<int> nums, int l){
        int n = nums.size()-1;
        if(l == n){
            result.push_back(nums);
            return;
        }
        for(int i=l; i<=n; i++) {
            swap(nums[i], nums[l]);
            permuteHelper(nums, l+1);
            swap(nums[i], nums[l]);
        }
    }

3. MATRIX: DFS with backtracking in a matrix on chars looking for a special "WORD"

    bool dfs(vector<vector<char>>&board, vector<vector<bool>>&visited, string word, int i, int j, int word_i ) {
        int m = board.size(); int n = board[0].size();

        if (i<0 || i>=m || j<0 || j>=n || visited[i][j] == true || board[i][j] != word[word_i])
            return false;
        
        visited[i][j] = true;
        
        if(word_i == word.size()-1)
            return true;
        else if (dfs(board, visited, word, i+1, j, word_i+1) || dfs(board, visited, word, i-1, j, word_i+1) || dfs(board, visited, word, i, j+1, word_i+1) || dfs(board, visited, word, i, j-1, word_i+1))
            return true;

        visited[i][j] = false;
        return false;
    }
    
    bool exist(vector<vector<char>>& board, string word) {
        int m = board.size();
        int n = board[0].size();
        
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                vector<bool> tmp(n, false);
                vector<vector<bool>> visited (m, tmp);
                if(dfs(board, visited, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
 
4. Vector: DFS with Backtracking for balancing out the balance of money one needs to pay other in minimum number of transactions

    class Solution {
    public:
        vector<int> debt;
        
        int minTransfers(vector<vector<int>>& transactions) {
            vector<int> balance(21, 0); // max 21 people involved.
            int ans = 0;
            for(auto t: transactions){
                balance[t[0]] -= t[2];
                balance[t[1]] += t[2];
            }
            
            for(auto b: balance){
                if(b != 0)
                    debt.push_back(b);
            }
            return dfs(0);
        }
        
        int dfs(int s){
            while(s < debt.size() && debt[s] == 0)
                s++;
            
            int res = INT_MAX;
            for(int i=s+1; i<debt.size(); i++){
                if(debt[i]*debt[s] < 0){
                    debt[i] += debt[s];
                    res = min(res, 1+dfs(s+1));
                    debt[i] -= debt[s];
                }
            }
            return res == INT_MAX ? 0 : res;
        }
    };

5. Classic Coin Changing dfs for getting coins(infinite) that form a sum (69):
    
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ans;
        vector<int> tempAns;
        backtrack(candidates, ans, tempAns, target, 0);
        return ans;
    }

    void backtrack(vector<int> candidates, vector<vector<int>>& ans, vector<int> tempAns, int remain, int start){
        if(remain < 0)
            return;
        if(remain == 0){
            ans.push_back(tempAns);
            return;
        }
        for(int i=start; i<candidates.size();i++){
            tempAns.push_back(candidates[i]);
            backtrack(candidates, ans, tempAns, remain-candidates[i], i);
            tempAns.pop_back();
        }
    }

====================================================================================================================
====================================================================================================================
====================================================================================================================



// ====================================================================================================================
// ====================================================================================================================
// ====================================================================================================================

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


// TrieNode
#define ALPHABETSIZE 26
class TrieNode {
public: 
    TrieNode* children[ALPHABETSIZE];
    bool isEndOfWord;
    TrieNode(){
        for(int i=0; i<ALPHABETSIZE; i++)
            this->children[i] = NULL;
        this->isEndOfWord = false;
    }
};
class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
};


// ====================================================================================================================
// ====================================================================================================================
// ====================================================================================================================

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