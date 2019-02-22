/* 
Harshit Gupta | 22nd October, 2018

cpp.sh/9yxha
https://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/

C++ program for finding the lowest common ancestor for two nodes of a Binary Tree.

Solution: We will recur for left and right subtrees for each node.
    The first node where we see that the node1 is on the left subtree and 
    node2 is at the right subtree will be the lowest common ancestor of the binary tree.
        
Time Complexity: O(N)

*/


#include <bits/stdc++.h>
using namespace std;

struct node{
    int data;
    struct node *left, *right;
    
    node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

node* lowestCommonAncestor(node *root, node *n1, node *n2){
    
    // If the root is NULL, then return NULL.
    if (root==NULL)
        return NULL;
    
    // If root matches any of the nodes, then we return it.
    // This will actually find the nodes.
    if(root==n1 || root==n2)
        return root;
    
    // Search for the nodes in the left subtree and right subtree recursively.
    node *left_subtree = lowestCommonAncestor(root->left, n1, n2);
    node *right_subtree = lowestCommonAncestor(root->right, n1, n2);
    
    // If we get a node where we found something in the left subtree and 
    // something in the right subtree, then return 'ROOT' since this will 
    // be the LCA of the two nodes n1 and n2.
    if(left_subtree!=NULL && right_subtree!=NULL)
        return root;
        
    // If something is found in the left subtree and nothing(NULL) in the right subtree.
    // then return that since you have found atleast one node. Another branch may have
    // found the other node and thus that level of recursion will return that 
    // instance of 'ROOT' and we will know the LCA of it.
    else if(left_subtree!=NULL)
        return left_subtree;
        
    // If something is found in the right subtree and nothing(NULL) in the left subtree.
    // then return that since you have found atleast one node. 
    else
        return right_subtree;
}

int main() {
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left = new node(40);
    root->left->right = new node(50);
    root->right->left = new node(60);
    root->right->right = new node(70);
    root->left->right->left = new node(80);
    
    node *lca = lowestCommonAncestor(root, root->left->left, root->left->right->left);
    if(lca!=NULL)
        cout<<lca->data<<" is the LCA."<<endl;
    else
        cout<<"Wrong Input"<<endl;
	return 0;
}