/* 
Harshit Gupta | 13th October, 2018

https://www.geeksforgeeks.org/level-order-tree-traversal/
https://ide.geeksforgeeks.org/9tNMvmrZ8X

C++ program for Level Order Traversal of a Tree.

Solution: We apply BFS on the tree to obtain its Level Order Traversal.
* We use a queue to apply BFS. Firstly, enqueue the root node and run a loop.
    The loop runs till the queue is empty. In the loop, we print the data, 
    then we enqueue the children of that node in the same queue and remove the node from the front.
    
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
