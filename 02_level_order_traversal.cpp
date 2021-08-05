/* 
Harshit Gupta | 13th October, 2018

https://www.geeksforgeeks.org/level-order-tree-traversal/
https://ide.geeksforgeeks.org/9tNMvmrZ8X
https://leetcode.com/problems/binary-tree-level-order-traversal/

C++ program for Level Order Traversal of a Tree.

Solution: We apply BFS on the tree to obtain its Level Order Traversal.
* We use a queue to apply BFS. Firstly, enqueue the root node and run a loop.
    The loop runs till the queue is empty. In the loop, we print the data, 
    then we enqueue the children of that node in the same queue and remove the node from the front.
    
    Similar Question:
        1. https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/
            a. Traversal has to be done in ZigZag manner.
                - One can do normal Level Order Traversal => [[1],[2,3],[4,5,6,7]]
                - Then reverse the alternate subarrays => [[1],[3,2],[4,5,6,7]]
            b. Use a deque to store the elements of that specific order
                - Push them from front for even levels and from back for odd levels.
                - Convert the deque to vector and insert it in ans.
        2. https://leetcode.com/problems/binary-tree-level-order-traversal-ii/
            a. Traverse from end towards top.
            b. Use a stack or just reverse the normal Level Order Traversal output.
*/

#include <bits/stdc++.h>
using namespace std; 

struct node {
    int data;
    struct node *left, *right;
    node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

typedef struct node node;

void levelOrderTraversal(node *root){
    
    if (root==NULL) return;

    queue<node *> q;
    
    // Enqueue the root node to start with.
    q.push(root);
    
    // Run this till the queue is empty.
    while(!q.empty()){
        
        node *top = q.front();
        
        // Print the data from the front.
        cout<<top->data<<" ";
        
        //Push the left and right childs of the node if they are not NULL.
        if(top->left != NULL)
            q.push(top->left);
        if(top->right != NULL)
            q.push(top->right);
        
        // Remove the top element
        q.pop();
    }
}

// Driver program to test above functions 
int main() 
{ 
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left = new node(40);
    root->left->right = new node(50);
    root->left->right->left = new node(60);
    root->left->left->right = new node(70);
    levelOrderTraversal(root);
	return 0; 
} 

// ----------------
// LEETCODE SOLUTION
// ----------------

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




// ------------
// ZigZag Order
// ------------

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> ans;
        if(root == NULL)
            return ans;
        queue<TreeNode*> q;
        q.push(root);
        bool isEven = false; // root level->1.
        
        while(!q.empty()){
            int size = q.size();
            deque<int> levelNodesDQ;
            for(int i=0; i<size; i++){
                TreeNode* front = q.front();
                q.pop();
                if(isEven)
                    levelNodesDQ.push_front(front->val);
                else
                    levelNodesDQ.push_back(front->val);
                    
                if(front->left)
                    q.push(front->left);
                if(front->right)
                    q.push(front->right);
            }
            isEven = !isEven;
            vector<int> levelNodesV = vector(begin(levelNodesDQ), end(levelNodesDQ));
            ans.push_back(levelNodesV);
        }
        return ans;
    }
};