/* 
Harshit Gupta | 14th October, 2018

C++ program for Lowest Common Ancestor of a Binary Tree.

https://ide.geeksforgeeks.org/jCVqREBwEa
https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/

Solution: If root is equal to any of the nodes, then LCA is the root.
    If one node is present in the left subtree and one node is present in the right subtree,
        then that node is the LCA of both the nodes.
    If both node lies in the left subtree, then LCA must be present in the left subtree.
    If both node lies in the right subtree, then LCA must be present in the right subtree.
    This code assumes that both the nodes are present in the binary tree.

Time Complexity: O(n) since each node is visited once.

Similar Questions:
    1. https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-ii/
        - What if there may not exist both nodes? Only 1? or None?
        - Solved below using 2 approaches

    2. https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/
        - What is the address of the root node is not given & you need to find out the LCA of 2 nodes
        - Each node has a pointer to its parent node.
        - Solved using two approaches below.
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

node* lowestCommonAncestor(node *root, node *node1, node *node2){
    
    // Base case. Returns NULL when the node is not present in a subtree
    if(root==NULL)
        return NULL;
    
    // Returns the root node when it is equal to any of the node.
    // Keeping this condition here returns as soon as we find one node
    // We can write this condition here and prevent iterating over the whole tree because we know 
    //      that the other node will exist and if not anywhere it MUST be below this node.
    // We can't write this condition if we are not sure that the node exists or not (Q2) since then
    //      we must traverse the whole tree to check if it really exists or not.
    if(root==node1 || root==node2){
        return root;
    }
    
    // Look for keys in left and right subtrees
    node *left_lca  = lowestCommonAncestor(root->left, node1, node2); 
    node *right_lca = lowestCommonAncestor(root->right, node1, node2);
    
    // If the above returns nodes both calls, then root is the LCA.
    if(left_lca && right_lca){
        return root;
    }

    // This would propagate the asnwer till the root.
    // If it gets the answer (root from above 'if'), then it is propagated till the actual root with these statements
    // Else for leaf nodes when node was not found, it will propagate NULL upward.
    // In this example, when 20 is the answer, it is propagated to root "10" with this statement

    // If node is found in the left subtree only, then left_lca is LCA.
    else if (left_lca){
        return left_lca;
    }
    // If node is found in the right subtree only, then right_lca is LCA.
    else {
        return right_lca;
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
    node *lca = lowestCommonAncestor(root, root->left->right, root->left->left);
    cout<<lca->data<<endl;
	return 0; 
} 




// -----------------------------------------------------------
// Similar Question 1: LCA when one of the node may not exist?
// -----------------------------------------------------------
class Solution {
public:
    
    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q, int& count){
        if(root==NULL)
            return NULL;
        
        // if(root== p || root == q)
        //     return root;
        // Dont return early, wait for the whole tree to execute & then check for this cond.
        
        TreeNode* leftLCA = lca(root->left, p, q, count);
        TreeNode* rightLCA = lca(root->right, p, q, count);
        
        // Now check for these conditions
        if(root == p || root == q) {
            count++;
            return root;
        }
        
        if(leftLCA && rightLCA)
            return root;
        else if(leftLCA)
            return leftLCA;
        else
            return rightLCA;
        
    }
    
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        int count = 0;
        TreeNode *l = lca(root, p, q, count);
        if(count == 2)
            return l;
        else
            return NULL;
    }
};


// Approach 1: Check for existance and then find LCA
    bool checkIfExists(TreeNode* root, TreeNode* node){
        if(root==NULL || node == NULL)
            return false;
        if(root->val == node->val)
            return true;
        if(checkIfExists(root->left, node) || checkIfExists(root->right, node))
            return true;
        else
            return false;
    }

    TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q){
        if(root==NULL)
            return NULL;

        if(root== p || root == q)
            return root;

        TreeNode* leftLCA = lca(root->left, p, q);
        TreeNode* rightLCA = lca(root->right, p, q);

        if(leftLCA && rightLCA)
            return root;
        else if(leftLCA)
            return leftLCA;
        else
            return rightLCA;

    }

    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(checkIfExists(root, p) && checkIfExists(root, q)){
            return lca(root, p, q);
        }
        else{
            return NULL;
        }
    }


// -----------------------------------------------------------
// Similar Question 2: LCA when root node is not known
// -----------------------------------------------------------
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};
*/

// Approach 2:
// This solution uses the sum of the paths from the node till the root
// Assume Dist of p to root=x  and q to root=y
// the sum x+y will remain the same for both p and q.
// Out of this x+y, some dist is common(from LCA to root): z and some dist is their own(p/q to LCA)
// To reach LCA from p: we need to travel (x+(y-z)), LCA from q: we need to travel (y+(x-z)) as well.
// E.g: x:2, y:3 and z:1, x+y-z:4
// If you start from p and reach till x and then travel (y-z) you reach LCA!
// If you start from q and reach till y and then travel (x-z) you reach LCA!
// So after travelling x from p and y from q, we reach the root and its parent is NULL,
// then we start p from q and q from p so that they reach x+y-z at the same time!

class Solution {
public:
    
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* a = p;
        Node* b = q;
        while(a!=b){
            // if(a!=NULL) cout<<"a: "<<a->val<<endl;
            // if(b!=NULL) cout<<"b: "<<b->val<<endl;
            // cout<<"---"<<endl;
            
            if(a==NULL)
                a = q;
            else
                a = a->parent;
            
            if(b == NULL)
                b = p;
            else
                b = b->parent;
        }
        return a;
        
    }
};

// Approach 1:
// 1. Search assuming that p is the root and q may be a child of it
// 2. Search assuming that q is the root and p may be a child of it
// 3. If both above are not true, then call LCA with their parents.

// bool search(Node* root, Node* p){
//     if(root==NULL)
//         return false;
//     if(root == p || search(root->left, p) || search(root->right, p))
//         return true;
//     else 
//         return false;
// }

// Node* lowestCommonAncestor(Node* p, Node * q) {
//     if(p == NULL || q == NULL || p==q)
//         return p;
//     if(search(p,q))
//         return p;
//     else if (search(q,p))
//         return q;
//     else
//         return lowestCommonAncestor(p->parent, q->parent);
// }