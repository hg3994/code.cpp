/* 
Harshit Gupta | 14th October, 2018

C++ program for Lowest Common Ancestor of a Binary Tree.

https://ide.geeksforgeeks.org/jCVqREBwEa
https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

Solution: If root is equal to any of the nodes, then LCA is the root.
    If one node is present in the left subtree and one node is present in the right subtree,
        then that node is the LCA of both the nodes.
    If both node lies in the left subtree, then LCA must be present in the left subtree.
    If both node lies in the right subtree, then LCA must be present in the right subtree.
    This code assumes that both the nodes are present in the binary tree.
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
