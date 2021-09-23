/*

Harshit Gupta | 5th October, 2020
---------------------------------

C++ program for "Topological Sorting"
------

Solution: The previous solution for Topological Sort written in "sorting.cpp" is not efficient. 
  It takes O(n3) time since the data structure which it uses is matrix and it has another for() within it.
  Here, we have discussed two solutions:
  
  1. Stack based: This solution does not detect cycles and return faulty results when we have cycles.

  2. Queue based: This solution detect cycles in the graph as well. Returns {} for it.
    Queue based solution is preffered over stack.

    Algorithm: Steps involved in finding the topological ordering of a DAG: 
        1: Compute in-degree (number of incoming edges) for each of the vertex present 
            in the DAG and initialize the count of visited nodes as 0.
        2: Pick all the vertices with in-degree as 0 and add them into a queue (Enqueue operation)
        3: Remove a vertex from the queue (Dequeue operation) and then. 
            a. Increment count of visited nodes by 1.
            b. Decrease in-degree by 1 for all its neighbouring nodes.
            c. If in-degree of a neighbouring nodes is reduced to zero, then add it to the queue.
        4: Repeat Step 3 until the queue is empty.
        5: If count of visited nodes is not equal to the number of nodes in the graph then the 
            topological sort is not possible for the given graph.

    If nodes in a graph have a cyclic dependency, then there won't exist a node with indegree 0 
        at some point of time and thus some part of the graph will not be traversed resulting in 
            visited_nodes < total nodes

---

Time Complexity: O(V+E) where V represents the number of vertices and E represents the number of
    edges. We pop each node exactly once from the zero in-degree queue and that gives us V. 
    Also, for each vertex, we iterate over its adjacency list and in totality, we iterate 
    over all the edges in the graph which gives us EE. Hence, O(V+E)

Space Complexity: O(V+E). We use an intermediate queue data structure to keep all the nodes with 
    0 in-degree. In the worst case, there won't be any prerequisite relationship and the queue 
    will contain all the vertices initially since all of them will have 0 in-degree. That gives 
    us O(V). Additionally, we also use the adjacency list to represent our graph initially. 
    The space occupied is defined by the number of edges because for each node as the key, 
    we have all its adjacent nodes in the form of a list as the value. Hence, O(E). 
    So, the overall space complexity is O(V+E).

------------------------------

Similar Questions:
    1. https://leetcode.com/problems/course-schedule/
        - We need to check if a cycle exists in a Directed Graph
        - We can use Kahn's Algorithm to test if a cycle exists in DAG

    2. https://leetcode.com/problems/course-schedule-ii/
        - We need to return the order (topological ordering) of the DAG.
        - We can use Kahn's Algorithm to get the topological ordering.
        - Asked in BOLT

    3. https://leetcode.com/problems/minimum-height-trees/
        - Amazing explanation given here: https://leetcode.com/problems/minimum-height-trees/solution/
        - The input is a non-directed acyclic graph with some edges and we can choose a 
            node as root and call the graph as tree.
        - We need to find the minimum height of the tree by choosing any node as root node.
        - We can rephrase the problem as finding out the nodes that are overall 
            close to all other nodes, especially the leaf nodes.
        - The idea is that we trim out the leaf nodes layer by layer, until we reach the 
            core of the graph, which are the centroids nodes. Once we trim out the first layer of the 
            leaf nodes (nodes that have only one connection), some of the non-leaf nodes would become 
            leaf nodes.The trimming process continues until there are only two nodes left in the graph, 
            which are the centroids that we are looking for.
        - The above algorithm resembles the topological sorting algorithm which generates the order of 
            objects based on their dependencies. For instance, in the scenario of course scheduling, 
            the courses that have the least dependency would appear first in the order.
        - We do not use the regular graph DS but used vector of vector to represent the graph.

    4. https://leetcode.com/problems/parallel-courses/
        - Given a directed graph of courses and the relationship between them. For a courseA which depends
            on courseB, we need to complete courseB and then we can complete courseA. We need to find the min number
            of semesters in which we can complete all the courses. 
        - Take as many courses as you can in first semester, then again the max we can in the next sem and so on..
        - We consider them as nodes and create a directed graph, then we complete the courses with indegree 0
            and implement the regular Topological Sort here.

Resources:
    - Stack Solution: https://www.geeksforgeeks.org/topological-sorting/
        - This works only for Acyclic Graph
    - Kahn's Algo: https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/
    - Adjacency Matrix and Adjacency List Representation of Graph: 
        https://www.softwaretestinghelp.com/graph-implementation-cpp/


*/



// Solution 3: Graph is represented by vector of vectors.
// THIS SHOULD BE THE PREFERRED SOLUTION FOR TOPOLOGICAL SORT
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        int n = numCourses;
        vector<int> ans;
        queue<int> q;
        vector<vector<int>> graph(n);
        vector<int> indegree(n, 0);
        
        for(auto& p: prerequisites){
            graph[p[1]].push_back(p[0]);
            indegree[p[0]]++;
        }
        
        for(int i=0; i<n; i++){
            if(indegree[i] == 0)
                q.push(i);
        }
        
        while(!q.empty()){
            int top = q.front();
            ans.push_back(top);
            q.pop();
            
            for(auto &e: graph[top]){
                if(--indegree[e] == 0)
                    q.push(e);
            }
        }
        if(n == ans.size())
            return ans;
        else
            return {};
    }
};


// Solution 4 (by lee215): Concise and Amazing. Similar to above
bool canFinish(int n, vector<vector<int>>& prerequisites) {
    vector<vector<int>> G(n);
    vector<int> degree(n, 0), bfs;
    for (auto& e : prerequisites) {
        G[e[1]].push_back(e[0]);
        degree[e[0]]++;
    }
    for (int i = 0; i < n; ++i) 
        if (!degree[i]) 
            bfs.push_back(i);

    for (int i = 0; i < bfs.size(); ++i)
        for (int j: G[bfs[i]])
            if (--degree[j] == 0) 
                bfs.push_back(j);

    return bfs.size() == n;
}







// Adjacency List representation of a graph
// Contains the number of nodes and an array of "pointers to linked lists"
class Graph {
public: 
    int V;
    list<int> *adj;
    
    Graph(int v){
        V = v;
        adj = new list<int> [V]; // array of of size V having pointer to lists
    }
  
    void addEdge(int u, int v){
        adj[u].push_back(v);  // access the linkedlist @ index u and insert node v in the end
    }
};

// Soluton 2: Queue Based.
// Kahn's Algorithm
// This solution detect cycles in the graph as well. Returns {} for it.

// Graph 1                                Graph 2 (with Cycles)
// -------                                ---------------------
// 0 -> 1                               | 0 -> 1            ->2->3
// 1 -> 2 ->3              /->2->4      | 1 -> 2           /     |
// 2 -> 4             0->1-             | 2 -> 3       0->1<-----|
// 3 -> NULL               \->3         | 3 -> 1           (Cycle)
// 4 -> NULL                            | 
class Solution {
public:

    vector<int> topologicalSort(Graph g) {

        // Get a vector to store the indegree of the vertices.
        vector<int> in_degree(g.V, 0);
      
        // O(V+E)
        // in_degree[0] = 0  | in_degree[0] = 0
        // in_degree[1] = 1  | in_degree[1] = 2
        // in_degree[2] = 1  | in_degree[2] = 1
        // in_degree[3] = 1  | in_degree[3] = 1
        // in_degree[4] = 1  | 
        for(int i=0;i<g.V;i++){
            list<int>::iterator it;
            for(it=g.adj[i].begin(); it!= g.adj[i].end(); it++){
                in_degree[*it]++;
            }
        }
      
        // Push the vertices that has indegree 0 in the queue.
        queue<int> q;
        for(int i=0;i<g.V; i++)
            if(in_degree[i] == 0)
                q.push(i);
      
        // This is to track the visited nodes to detect cycles in the graph.
        int visited_nodes = 0;
        vector<int> ans;
      
        // Till the queue is not empty, remove a vertex and push it in my answer vector.
        // Increment a visited_node counter by 1.
        // Since we have taken that vertex out now and visited it, 
        //   we decrease the indegree of all the adjacent vertices that it used to point to. 
        // If any of the adjacent vertices have an indegree 0 after this decrement, we push it in the queue.
        while(!q.empty()){
            int u = q.front();
            q.pop();
            ans.push_back(u);
            visited_nodes++;
            
            list<int>::iterator it;
            for(it=g.adj[u].begin(); it!= g.adj[u].end(); it++){
              if(--in_degree[*it] == 0)
                q.push(*it);
            }
        }
      
        // If we didn't visit all the nodes, then there must have been a cycle in the graph.
        if(visited_nodes != g.V)
            return {};
        else
            return ans;
    }
  
    vector<int> findOrder(int numCourses, vector<vector<int>>& p) {
        Graph g(numCourses); 
      
        for(int i=0;i<p.size();i++){
            g.addEdge(p[i][1], p[i][0]);
        }
      
        return topologicalSort(g);
    }
};


// --------------------------------------------------------------------------------

// Solution 1: Stack based.
// This solution does not detect cycles and return faulty results when we have cycles.
class Solution {
  public:
  
    void topologicalSortUtil(Graph g, int v, vector<int>& stack, vector<bool>& visited){
      visited[v]= true;
      
      list<int>::iterator it;
      
      for(it = g.adj[v].begin(); it!=g.adj[v].end(); it++)
        if (!visited[*it])
          topologicalSortUtil(g, *it, stack, visited);
      
      stack.push_back(v);
    }
  
    vector<int> topologicalSort(Graph g){
      vector<int> stack;
      vector<bool> visited(g.V, false);
      
      for(int i=0;i<g.V;i++){
        if(visited[i] == false)
          topologicalSortUtil(g, i, stack, visited);
      }
      return stack;
    }
  
    vector<int> findOrder(int numCourses, vector<vector<int>>& p) {
      Graph g(numCourses); 
      
      // Construct the graph
      for(int i=0;i<p.size();i++){
        g.addEdge(p[i][0], p[i][1]);
      }
      
      vector<int> s = topologicalSort(g);
      vector<int> ans;

      // Construct reverse of stack for answer.
      while(!s.empty()){
        int v = s.back();
        s.pop_back();
        ans.push_back(v);
      }
      
      return ans;
    }
};


// --------------------------------------------------------------
// SIMILAR QUESTION 3 - MINIMUM Height oF Tree-Like DS from Graph
// --------------------------------------------------------------

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if(n == 0)
            return {};
        if (n==1)
            return {0};
        
        vector<int> res;
        vector<int> degrees(n, 0);
        vector<vector<int>> adj(n);
        
        //creating adjacent list & degreees vector for the undirected graph
        for(int i=0;i<edges.size();i++) {
            adj[edges[i][0]].push_back(edges[i][1]); 
            adj[edges[i][1]].push_back(edges[i][0]);
            degrees[edges[i][1]]++; //updating how many edges each node has
            degrees[edges[i][0]]++;
        }
        queue<int>queue;
        for(int i=0;i<n;i++) {
            if(degrees[i]==1) // adding all the leave nodes
                queue.push(i);
        }
        
        while(!queue.empty()) {
            res.clear(); // clear vector before we start traversing level by level since we didn't reach centroid of the graph
            int size=queue.size();
            for(int i=0;i<size;i++) {
                int cur=queue.front();
                queue.pop();
                res.push_back(cur); // adding nodes to vector.Goal is to get a vector of just 1 or 2 nodes available.
                for(auto &neighbor:adj[cur])
                {
                    degrees[neighbor]--;      //removing current leave nodes
                    if(degrees[neighbor]==1)  //adding current leave nodes
                        queue.push(neighbor);
                }
            }
        }
        return res;
        
    }
};


// -------------------------------------
// SIMILAR QUESTION 4 - PARALLEL COURSES
// -------------------------------------

class Solution {
public:
    int minimumSemesters(int n, vector<vector<int>>& relations) {
        vector<vector<int>> g(n+1);
        vector<int> indegree(n+1, 0);
        queue<int> q;
        int ans=0, visited_nodes=0;
        
        for(auto a: relations){
            g[a[0]].push_back(a[1]);
            indegree[a[1]]++;
        }
        for(int i=1; i<n; i++){
            if(indegree[i] == 0)
                q.push(i);
        }
        
        while(!q.empty()){
            ans++;
            int size = q.size();
            for(int i=0; i<size; i++){
                int top = q.front();
                q.pop();
                visited_nodes++;
                for(auto& a: g[top]){
                    if(--indegree[a] == 0)
                        q.push(a);
                }
            }
        }
        
        if(visited_nodes == n)
            return ans;
        else
            return -1;
        
    }
};