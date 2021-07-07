
/*

Harshit Gupta | 5th July, 2021
---------------------------------

In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge 
added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already 
existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates 
that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are 
multiple answers, return the answer that occurs last in the input.

https://leetcode.com/problems/redundant-connection/
------

Solution:       

    1. DFS: We will construct the graph by adding edges one after another. After each addition of a new edge, 
        we will do a dfs traversal to check if any cycle has formed. If a cycle is detected, we know that the 
        last edge addition has led to the formation of cycle and hence we will simply return that edge.

TC: O(n2)
SC: O(n)
---

    2. Union Find

    We can solve this using a Disjoint Subset Union (DSU). It involes two operations -

    - find(x): finds the id which represents the component that a node belongs to
    - union(x, y): joins the two components into a single component. This involves finding the 
        representative of x-component (by find(x)) and y-component (by find(y)) and assigning 
        them a common representative (same parent).
        
    We are given various edges of the graph. These can be consider as different disconnected components. 
    We will join these one by one. A component will be represented as a tree with all its members linked to 
    some parent and the top parent will be considered that component's representative. When we find an edge 
    that joins two nodes which are already in the same component, we will return that edge as answer. 
    Otherwise, we will just Union it, i.e, connect the two components by picking that edge.

TC: O(n)
SC: O(n)

Paradigm: DFS, Union Find
---
  NOTE: 

*/

// DFS
// Time Complexity : O(n2), In worst case, we may need n dfs calls with each taking O(n) time complexity.
// Space Complexity : O(n), to maintain graph
class Solution {
public:
    
    vector<int> findRedundantConnection(vector<vector<int>>& e) {
        int n = size(e);
        vector<vector<int>> graph(n+1);
        vector<bool> vis(n+1);
        
        for(auto &E: e) {
            fill(begin(vis), end(vis), false);
            graph[E[0]].push_back(E[1]), graph[E[1]].push_back(E[0]);
            if(dfs(graph, vis, E[0])) return E;
        }
        return { };
    }
    
    bool dfs(vector<vector<int>>& graph, vector<bool>& vis, int cur, int par = -1){
        if(vis[cur]) return true;
        vis[cur] = true;
        for(auto child: graph[cur])
            if(child != par && dfs(graph, vis, child, cur)) return true;
        return false;
    }
};

// =====================================================================================================


// Union Find 
// -----------
// Time Complexity : O(n2), In this naive implementation, the worst case may lead to a scenario where we 
//      get a single component with a long lopsided chain and each find call will take O(n) for a total of n calls.
// Space Complexity : O(n), to maintain par array
// For a Graph like this: [[1,2],[1,3],[2,3]]
// parent:  [0,1,2,3]
//          [0,2,2,3] // [1,2] => parent[1] = 1 || parent[2] = 2, then parent[1] = 2
//          [0,2,3,3] // [1,3] => parent[1] = 2, parent[2] = 2 || parent[3] = 3, then parent[2] = 3
//          [0,2,3,3] // [2,3] => parent[2] = 3, parent[3] = 3 || parent[3] = 3, Both index have same id so this is the extra edge
//          
class DSU {
public: 
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        // initializes each node's parent to be itself - fills as [0,1,2,3,...,n], now each node is a parent of itself (self loop)
        iota(begin(parent), end(parent), 0);
    }
    
    int find (int x) {
        // x is itself the parent of this component, then return, 
        // else recurse for parent of x.
        if (x == parent[x])
            return x;
        return find(parent[x]);
    }
    
    bool Union (int x, int y){      // since union is already a keyword, so Union.
        int xp = find(x);           // find parents of x and y, i.e, representatives of components that x and y belong to
        int yp = find(y);
        if (xp == yp)               // x and y already belong to same component - not possible to union
            return false;
        parent[xp] = yp;            // union x and y by making parent common
        return true;
    }
    
    // iterative implementation of find
    // int find(int x) {  
    //     while(x != parent[x]) x = parent[x];
    //     return parent[x];
    // }
};



class Solution {
public:
    vector<int> findRedundantConnection(vector<vector<int>>& e) {
        DSU ds(e.size() + 1);
        for (auto& E: e){
            if(! ds.Union(E[0], E[1]))
                return E;
        }
        return {}; // Will never reach here.
    }
};



// ==================================================================================


// Union Find WITH PATH COMPRESSIONS
// ------------------------------------

// There's a very small change here from Solution above in the find() function. We update the par[x] as the 
// result returned by find(par[x]) before returning from each recursive call. This will ensure that any future 
// calls to find(x) won't require us to re-iterate all the way till the base par[x]. This effectively, compresses 
// the path to parent of x (for future calls), as the name suggests.

// Time Complexity : Θ(nlogn) , find may take O(n) for first few calls but since we are using path 
// compression, each one makes subsequent searches faster and hence the amortized time complexity 
// over a set of calls to find operation is O(logn)
// Space Complexity : O(n)

class DSU {
public: 
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        // initializes each node's parent to be itself - fills as [0,1,2,3,...,n], now each node is a parent of itself (self loop)
        iota(begin(parent), end(parent), 0);
    }
    
    int find (int x) {
        // x is itself the parent of this component, then return, 
        // else recurse for parent of x.
        if (x == parent[x])
            return x;
        parent[x] = find(parent[x]); // PATH COMPRESSION
        return parent[x];
    }
    
    bool Union (int x, int y){      // since union is already a keyword, so Union.
        int xp = find(x);           // find parents of x and y, i.e, representatives of components that x and y belong to
        int yp = find(y);
        if (xp == yp)               // x and y already belong to same component - not possible to union
            return false;
        parent[xp] = yp;            // union x and y by making parent common
        return true;
    }
};



// ==================================================================================


// Union Find WITH PATH COMPRESSIONS & UNION BY RANK
// -------------------------------------------------

// This optimization involves doing the union based on the rank (or size) of parents / representative of a 
// component instead of just attaching one to the other randomly. This will ensure that even in the worst-case, 
// we don't end up in a scenario where the parent forms a skewed tree (all nodes on one-side) and we wouldn't need 
// to iterate all nodes on each find call. Performing the union based on rank will keep the components/tree 
// balanced in size.

// Time Complexity : O(n*α(n)) ≈ O(n), the time complexity of each find call after union-by-rank and path 
// compression comes out to be O(α(n)), where α(n) is the inverse Ackermann function. It doesn't exceed 4 
// for any n < 10600 and hence is practically constant. We make O(n) calls in total.
// Space Complexity : O(n)

class DSU {
public: 
    vector<int> parent, rank;
    
    DSU(int n) {
        parent.resize(n);
        rank.resize(n);
        // initializes each node's parent to be itself - fills as [0,1,2,3,...,n], now each node is a parent of itself (self loop)
        iota(begin(parent), end(parent), 0);
    }
    
    int find (int x) {
        // x is itself the parent of this component, then return, 
        // else recurse for parent of x.
        if (x == parent[x])
            return x;
        parent[x] = find(parent[x]); // PATH COMPRESSION
        return parent[x];
    }
    
    bool Union (int x, int y){      // since union is already a keyword, so Union.
        int xp = find(x);           // find parents of x and y, i.e, representatives of components that x and y belong to
        int yp = find(y);
        if (xp == yp)               // x and y already belong to same component - not possible to union
            return false;
        if (rank[xp] > rank[yp])    // union by rank - join smaller ranked to bigger one
            parent[yp] = parent[xp];
        else if (rank[yp] > rank[xp])
            parent[xp] = parent[yp];
        else {                      // same rank - join either to other and increment rank of final parent
            parent[xp] = yp;        // union x and y by making parent common
            rank[yp]++;
        }
        return true;
    }
};