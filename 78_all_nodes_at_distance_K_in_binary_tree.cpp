
/*

Harshit Gupta | 5th May, 2021
---------------------------------

C++ program for "Printing all nodes in a Binary Tree which are at a distance K from a target node"
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/
------

Solution 1: BFS
	If we just need to find the nodes at distance K from a target node in child nodes, 
	then it is pretty easy. But here we need to find all the nodes at distance K which means
	that we need to search even in the parent nodes.
	
	1. We take the help of hash maps to traverse the whole tree from root and store the child->parent reln.
		This will help us in knowing the parent of every child. This is how we can traverse upward.
	2. We use BFS to traverse the graph from target node to downwards and upwards for a 
		distance of K nodes. We can now easily traverse upwards (thanks to the hash above)
    3. For travelling upwards, we can just refer to the map and whatever node it gives, we can add it to bfs q.
	3. We keep a visited map as well so that we dont traverse a node more than once.

https://www.youtube.com/watch?v=nPtARJ2cYrg

Time Complexity: O(n)
Space Complexity: O(n)
---

Solution 2: DFS
    Instead of BFS, one can also use DFS to traverse the tree and it will be similar.
	1. Create the parents hash to get the child->parent relationship.
	2. Iterate over left child, right child and parent node increasing the distance.
	3. Keep the "visited" hash which will help you get solution faster.
https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/discuss/143775/very-easy-to-understand-c%2B%2B-solution.

---
*/

#include<bits/stdc++.h>
using namespace std;

// Tree Node
struct TreeNode {
    int val;
    struct TreeNode *left, *right;
    TreeNode(int data){
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};
typedef struct TreeNode TreeNode;

class Solution {
public:

	// Recursive Function to get the "parents hash" where child->parent relationship is kept
    void fill_parents(unordered_map <TreeNode*, TreeNode*>& parents, TreeNode* node){    
        if (node == NULL)
            return;
        // store the child->parent relationship and iterate for the left child
        if(node->left != NULL){
            parents[node->left] = node;
            fill_parents(parents, node->left);
        }
        // store the child->parent relationship and iterate for the right child
        if(node->right != NULL){
            parents[node->right] = node;
            fill_parents(parents, node->right);
        }
    }
    
    // Function to get all nodes which are a distance K from target node.
    vector<int> distanceK(TreeNode* root, TreeNode* target, int K) {
        if (root == NULL)
            return {};
        
        unordered_map <TreeNode*, TreeNode*> parents;
        // Get the child->parent relationship in the "parents" map.
        fill_parents(parents, root);
        
        // Hash to store the nodes which are already visited so we do not fall in an infinite loop
        unordered_map<TreeNode*, bool> visited;

        // Queue for BFS
        queue<TreeNode*> q;

        int currentLevel = 0;
        q.push(target);
        visited[target] = true;
        
        // Till the queue is empty
        while(!q.empty()){

        	// If we are already at level 'K', then we break since queue will have our distance K nodes
        	// otherwise increase the level
        	if (currentLevel == K){
                break;
            }
            currentLevel++;

        	// Get the size of the queue.
            int size = q.size();
            
            // For the size number of elements in the queue, keep trying to visit them and push in the queue
            // This is needed because this will tell us the number of nodes which are at the same level.
            // This is really important to understand that when the control comes here the number of elements
            // in the queue are all at the same level. While the loop runs, it may increase but the 'size' 
            // variable is still the same and it will stop. The new nodes which are added are all at the same level.
            // NOTE:  Putting NULL marker after the level ends will not work here.
            for(int i=0; i<size; i++) {
                TreeNode* front = q.front();
                visited[front] = true;
                q.pop();

                if (front->left && !visited[front->left]){
                    q.push(front->left);
                }

                if (front->right && !visited[front->right]){
                    q.push(front->right);
                }

                if (parents[front] && !visited[parents[front]]){
                    q.push(parents[front]);
                }
            }
        }
        vector<int> res;
        while(!q.empty()){
            TreeNode *f = q.front();
            q.pop();
            res.push_back(f->val);
        }
        return res;
    }
};