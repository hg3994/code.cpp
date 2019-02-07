/* 
Harshit Gupta | 9th January, 2019

https://ide.geeksforgeeks.org/0wlKa1Gl0T
https://www.geeksforgeeks.org/iterative-preorder-traversal/

C++ program for inorder, preorder and postorder traversal of a binary tree.

Solution: LVR -> inorder
    VLR -> preorder
    LRV -> postorder
    
    Just remember that the place of 'V' depends of xxx-order. 
    'in' is middle. 'pre' is before. 'post' is after.

preOrderIterative
=================
 Following is a simple stack based iterative process to print Preorder traversal.
  1) Create an empty stack nodeStack and push root node to stack.
  2) Do following while nodeStack is not empty.
    a) Pop an item from stack and print it.
    b) Push right child of popped item to stack
    c) Push left child of popped item to stack

  NOTE: Right child is pushed before left child to make sure that left subtree is processed first.


Paradigm: Recursion.

Time Complexity: O(n) for all the traversals.

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
    int data;
    struct node* left;
    struct node* right;
    node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

typedef struct node node;

// LVR for in-order traversal
void inOrder(node *root){
    if(root==NULL)
        return;
    inOrder(root->left);
    cout<<root->data<<" ";
    inOrder(root->right);
}

// VLR for in-order traversal
void preOrder(node *root){
    if(root==NULL)
        return;
    cout<<root->data<<" ";
    inOrder(root->left);
    inOrder(root->right);
}

void preOrderIterative(node *root){
    // Base Case 
    if (root == NULL) 
       return;

    // Create an empty stack and push root to it 
    stack<node *> s;
    s.push(root);

    // Pop all items one by one. Do following for every popped item 
    // a) print it 
    // b) push its right child 
    // c) push its left child 
    // Note that right child is pushed first so that left is processed first
    while(s.empty() == false){
      node *top = s.top();
      cout<<top->data<<" ";
      // Pop the top item from stack and print it 
      s.pop();

      // Push right and left children of the popped node to stack 
      if (top->right)
        s.push(root->right);
      if (top->left)
        s.push(root->left);
    }
    cout<<endl;

}

// LRV for in-order traversal
void postOrder(node *root){
    if(root==NULL)
        return;
    inOrder(root->left);
    inOrder(root->right);
    cout<<root->data<<" ";
}

int main() 
{
    // Create a binary tree.
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    
    cout<<"Inorder: "<<endl;
    inOrder(root); // LVR
    
    cout<<endl<<"PreOrder: "<<endl;
    preOrder(root); // VLR
    
    cout<<endl<<"PreOrder (Iterative): "<<endl;
    preOrderIterative(root); // VLR

    cout<<endl<<"PostOrder: "<<endl;
    postOrder(root); // LRV
    return 0; 
} 
