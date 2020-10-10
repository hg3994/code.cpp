/*

Harshit Gupta | 5th October, 2020
---------------------------------

C++ program for "Topological Sorting"
https://leetcode.com/problems/course-schedule-ii/solution/
------

Solution: The previous solution for Topological Sort written in "sorting.cpp" is not efficient. 
  It takes O(n3) time since the data structure which it uses is matrix and it has another for() within it.
  Here, we have discussed two solutions:
  - Stack based: This solution does not detect cycles and return faulty results when we have cycles.
  - Queue based: This solution detect cycles in the graph as well. Returns {} for it.

  Queue based solution is preffered over stack.

NOTE: If nodes in a graph have a cyclic dependency, then there won't exist a node with indegree 0.

https://www.geeksforgeeks.org/topological-sorting-indegree-based-solution/?ref=rp
https://www.geeksforgeeks.org/topological-sorting/

Time Complexity: O(V+E)
Space Complexity: O(V)

*/


class Graph {
public: 
  int V;
  list<int> *adj;
  
  Graph(int v){
    this->V = v;
    adj = new list<int> [V];
  }
  
  void addEdge(int u, int v){
    adj[u].push_back(v);
  }
};


// Solution 1: Stack based.
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


// Soluton 2: Queue Based.
class Solution {
  public:

    vector<int> topologicalSort(Graph g){

      // Get a vector to store the indegree of the vertices.
      vector<int> in_degree(g.V, 0);
      
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