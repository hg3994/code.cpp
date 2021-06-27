/* 
Harshit Gupta | 22nd October, 2018

cpp.sh/9us6
https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/
https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/

C++ program for finding the lowest common ancestor for two nodes of a Binary Search Tree.

Solution: We will use the property of BST to get the solution faster. 
    To every node starting from root, 
    
        If both n1 and n2 are lesser than the root, 
            then we know that both the nodes must lie in the left subtree, so we recur there
        If both n1 and n2 are greater than the root node,
            then we know that both the nodes must lie in the right subtree, so we recur there.
        If it doesn't satisfy both the above cases, this means that one of the node is lesser than it 
            and one is larger than it, so we return the 'root' at that instance, since that would be the LCA.
            
Time Complexity: O(height) = O(logn) on average(usually) = O(n) in worst case(skewed).

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

node* lowestCommonAncestorBST(node *root, node *n1, node *n2){
    
    // If the root is NULL, then return NULL.
    if (root==NULL)
        return NULL;
        
    // If n1's data and n2's data are smaller than the root's data, 
    // then LCA must lie in the left subtree
    if(root->data > n1->data && root->data > n2->data)
        return lowestCommonAncestorBST(root->left, n1, n2);

    // If n1's data and n2's data are larger than the root's data, 
    // then LCA must lie in the right subtree
    else if(root->data < n1->data && root->data < n2->data)
        return lowestCommonAncestorBST(root->right, n1, n2);
    
    // Else the n1's data must be smaller than the root's data
    // and n2's data must be larger than the root's data.
    // This is the LCA of n1 and n2.
    else
        return root;
}

int main() {
    struct node *root        = new node(20); 
    root->left               = new node(8); 
    root->right              = new node(22); 
    root->left->left         = new node(4); 
    root->left->right        = new node(12); 
    root->left->right->left  = new node(10); 
    root->left->right->right = new node(14); 
    
    node *lca = lowestCommonAncestorBST(root, root->left->right , root->right); //LCA of 12 and 22
    if(lca!=NULL)
        cout<<lca->data<<" is the LCA of "<<root->left->right->data<<" and "<<root->right->data<<endl;
    else
        cout<<"Wrong Input"<<endl;
	return 0;
}