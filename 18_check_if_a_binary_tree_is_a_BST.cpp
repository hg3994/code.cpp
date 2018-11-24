/* 
Harshit Gupta | 24th October, 2018

https://ide.geeksforgeeks.org/1LS3B9dAfC
https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/

C++ program for checking if a given tree is a BST or not.

Solution: For a binary tree to be a BST, we know that all the node values 
    on its left subtree must be smaller than the root node, all the values in the right
    subtree must be larger than the root node. This must be recurseively true for all the nodes.
    
    We are assigning a minimum and maximum value to each node in which its value must lie.
    For root node, it can be between INT_MIN and INT_MAX.
    Fot its left node, it can be between INT_MIN and root-1
    Fot its right node, it can be between root+1 and INT_MAX.
    This will be true for all the nodes cosidering them as root.

Time complexity: O(n)

Paradigm: Recursion

*/

#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    struct node* left;
    struct node* right;
    
    node(int data){
        this->data = data;
        this->left = left;
        this->right = right;
    }
};
typedef struct node node;


bool isBST(node *root, int mini, int maxi){
    // If root is NULL, this is a leaf node and it is fine to have leaf nodes.
    if (root==NULL)
        return true;
    
    // If the data is not within the specfied range, then return false.
    if(root->data < mini || root->data > maxi)
        return false;
        
    // If the data is fine for the root, then go on and check if it is true
    // for the left and right subtrees recurseively with appropriate values.
    return isBST(root->left, mini, root->data-1) && 
        isBST(root->right, root->data+1, maxi);
}

int main() {
    node *root = new node(40);
    root->left = new node(20);
    root->right = new node(50);
    root->left->left = new node(10); // Change this to 100 for it lose the BST property.
    root->left->right = new node(30);
    root->right->right = new node(70);
    
    if (isBST(root, INT_MIN, INT_MAX))
        cout<<"This tree is a Binary Search Tree."<<endl;
    else
        cout<<"This tree is NOT a Binary Search Tree."<<endl;
        
	return 0;
}