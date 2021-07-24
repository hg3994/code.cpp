
/*

Harshit Gupta | 20th October, 2020
---------------------------------

C++ program for "Given a reference of a node in a connected undirected graph. 
  Return a deep copy (clone) of the graph."

https://leetcode.com/problems/clone-graph/
------

Solution: We can do this with DFS or BFS.

    1. DFS:
        1. We use map to store original -> cloned node
        2. Iterate over neighbours recursively to get their own cloned nodes
        3. If we already know the address of a cloned node from map, we return it.
        4. Function 
            a. Checks if you already have a cloned node, if yes, return it.
            b. Create a cloned node.
            c. Iterate over the original neighbours and get their cloned neighbours(recursively) 
                & attach to cloned node.
            d. Return the cloned node.

    1-2
    | |
    4-3

    Graph
        1-> [2,4]
        2-> [1,3]
        3-> [2,4]
        4-> [1,3]

    Map contains X->X* where (X*) represents the cloned nodes
        1->1*
        2->2*
        3->3*
        4->4*

    For 1, We create cloneNode 1*, update the map with it and iterate on neighbour 2,4
        For 2, cloneGraph is called which creates 2*, updates in map and then iterate over neighbour 1,3
            For 1, we already have 1* in map, we return. 2* -> [1*] now
            For 3, cloneGraph is called which creates 3*, updates in map and then iterate over neighbour 2,4
                For 2, we already have 2* in map, we return. 3* -> [2*] now
                For 4, cloneGraph is called which creates 4*, updates in map and then iterate over neighbour 1,3
                    For 1, we already have 1* in map, we return. 4* -> [1*] now
                    For 3, we already have 3* in map, we return. 4* -> [1*, 3*] now
                4* is returned so we have 3* -> [2*, 4*] now.
            3* is returned,so we have 2* -> [1*, 3*] now.
        2* is returned,so we have 1* -> [2*] now.
        For 4, we already have 4* in map, we return. 1* -> [2*, 4*]
    Return 1* which the function needs.


    Time Complexity: O(N+M) where N is a number of nodes (vertices) and M is a number of edges.
    Space Complexity: O(N+H) where N is space occupied for visited map. H is the height of the graph


    2. BFS: TODO
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
    unordered_map<Node*, Node*> visited;

public:
    
    Node* cloneGraph(Node* node) {
        // If node is null, return.
        if(node == NULL)
            return NULL;
        
        // If the node is present already in the map, return the 'cloned' node of the 'original' node.
        // If we do not do this, we may fall into an infinite loop.
        if(visited.count(node)){
            return visited[node];
        }
        
        // Create the cloned node with the val in original node.
        Node* cloneNode = new Node(node->val);

        // Update the map with this original -> cloned node.
        visited[node] = cloneNode;

        // Iterate over all the neighbors of the original node to create the neighbour clone nodes.
        for(auto nbr : node->neighbors){
            // Push the neighbour of original nodes to the neighbour of cloned node.
            cloneNode->neighbors.push_back(cloneGraph(nbr));
        }
        return cloneNode;
    }
};


// ---------------------
// BFS SOLUTION IN JAVA
// ---------------------
class Solution {
    public Node cloneGraph(Node node) {
        if (node == null) {
            return node;
        }

        // Hash map to save the visited node and it's respective clone
        // as key and value respectively. This helps to avoid cycles.
        HashMap<Node, Node> visited = new HashMap();

        // Put the first node in the queue
        LinkedList<Node> queue = new LinkedList<Node> ();
        queue.add(node);
        // Clone the node and put it in the visited dictionary.
        visited.put(node, new Node(node.val, new ArrayList()));

        // Start BFS traversal
        while (!queue.isEmpty()) {
            // Pop a node say "n" from the from the front of the queue.
            Node n = queue.remove();
            // Iterate through all the neighbors of the node "n"
            for (Node neighbor: n.neighbors) {
                if (!visited.containsKey(neighbor)) {
                    // Clone the neighbor and put in the visited, if not present already
                    visited.put(neighbor, new Node(neighbor.val, new ArrayList()));
                    // Add the newly encountered node to the queue.
                    queue.add(neighbor);
                }
                // Add the clone of the neighbor to the neighbors of the clone node "n".
                visited.get(n).neighbors.add(visited.get(neighbor));
            }
        }

        // Return the clone of the node from visited.
        return visited.get(node);
    }
}