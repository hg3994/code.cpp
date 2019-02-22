/* 
Harshit Gupta | 14th October, 2018

https://ide.geeksforgeeks.org/K6h4Dopr06

C++ program for Left View of a Binary Tree.

Solution: Maintain a maximum height of whatever depth you have reached. 
    Recur for left and right subtrees.
    Since left is recurred first, we will cover left view and set maximum 
    so that the right ones at the same level get ignored.

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

void leftView(node *root, int level, int *maxlevel){
    if(root== NULL){
        return;
    }
    
    // If the maximum level reached till now is lesser than the current level, 
    // print it and increase the maxlevel.
    // This would be reached by left subtree before the right subtrees since that is recurred before right one.
    if(*maxlevel < level){
        cout<<root->data<<" ";
        *maxlevel = level;
    }
        
    leftView(root->left, level+1, maxlevel);
    leftView(root->right, level+1, maxlevel);
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
    int level=1, maxlevel=0;
    leftView(root, level, &maxlevel);
	return 0; 
} 
