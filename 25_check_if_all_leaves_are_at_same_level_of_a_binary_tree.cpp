/* 
Harshit Gupta | 23rd October, 2018

https://ide.geeksforgeeks.org/9TRpaFhMm0
https://www.geeksforgeeks.org/check-leaves-level/

C++ program for checking if all the leaves are at the same level in a Binary Tree.

Solution: We caluclate the first leaf level and we store it in a variable(leaf_level).
    We used INT_MIN as the leaf_level value to distinguish finding the first leaf level.
    Everytime we get a level, we check if the leaf is of the same 
        level as previous levels were.
    If this was true for all the cases, then return true. Else False.
    Recur like this for all the nodes and check for leaf node levels.
    

Time complexity: O(n)

Paradigm: Recursion

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

bool checkLeavesSameLevel(node *root, int level, int *leaf_level){
    
    // If root is NULL, return NULL.
    // This case comes when lets say a node has only left child, no right.
    // Then on the call checkLeavesSameLevel(root->right...), we return true.
    if(root==NULL)
        return true;

    // If both the pointers are NULL, this means it is a leaf node.
    if(root->left == NULL && root->right==NULL){
        
        // If leaf_level is INT_MIN, this means this is the first leaf we have seen.
        // So, set the leaf_level value to this level.
        // All other leaves should be equal to this level.
        if(*leaf_level==INT_MIN){
            *leaf_level = level;
            return true;
        }
        // For iterations of leaves other than first, they have to be equal to leaf_level
        else if(*leaf_level == level){
            return true;
        }
        
        // If they are not, we return FALSE.
        else
            return false;
    }
    else{
        // Recur for left and right subtrees to check more leaves.
        return checkLeavesSameLevel(root->left, level+1, leaf_level) && checkLeavesSameLevel(root->right, level+1, leaf_level);
    }
}

int main() {
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left = new node(40);
    root->left->right = new node(50);
    root->right->left = new node(60);
    root->right->right = new node(70);
    root->left->right->left = new node(80); // comment this and they will be at same level
    
    int level = 1;
    int leaf_level = INT_MIN;
    bool ans = checkLeavesSameLevel(root,level, &leaf_level);
    if(ans==1)
        cout<<"Yes. All leaves are at the same level."<<endl;
    else
        cout<<"No. All leaves are not at the same level."<<endl;
	return 0;
}