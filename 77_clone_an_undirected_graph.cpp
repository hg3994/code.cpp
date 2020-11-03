
/*

Harshit Gupta | .........., 2020
---------------------------------

C++ program for "Given a reference of a node in a connected undirected graph. Return a deep copy (clone) of the graph."

https://leetcode.com/problems/clone-graph/
------

Solution: We can do this with DFS or BFS.

    DFS:
        1. 


Time Complexity: 
Space Complexity: =
---
  NOTE: 

  KEY TERMS: Recursion, DFS, BFS

*/


#include<bits/stdc++.h>
using namespace std;




// Definition for a Node.
// contains a value and an array of pointers to other nodes (neighbors)
class Node {
  public:
    int val;
    vector<Node*> neighbors;
    
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};


class Solution {
  private:
    // We store the map from 'original' node to 'cloned' node
    unordered_map<Node*, Node*> mp;

  public:
  
  Node* cloneGraph(Node* node) {
    // If node is null, return.
    if(node == NULL)
      return NULL;
    
    // If the node is present already, return the 'cloned' node of the 'original' node.
    if(mp.count(node)){
      return mp[node];
    }
    
    // Create the cloned node with the val in original node.
    Node* cloneNode = new Node(node->val);

    // Update the map with this original -> cloned node.
    mp[node] = cloneNode;

    // Iterate over all the neighbors of the original node to create the neighbour clone nodes.
    for(auto nbr : node->neighbors){
      // Push the neighbour of original nodes to the neighbour of cloned node.
      cloneNode->neighbors.push_back(cloneGraph(nbr));
    }
    return cloneNode;
  }
};