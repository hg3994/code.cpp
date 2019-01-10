/* 
Harshit Gupta | 9th January, 2019

C++ program for inorder, preorder and postorder traversal of a binary tree.

Solution: LVR -> inorder
    VLR -> preorder
    LRV -> postorder
    
    Just remember that the place of 'V' depends of xxx-order. 
    'in' is middle. 'pre' is before. 'post' is after.

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
void inOrder(node *head){
    if(head==NULL)
        return;
    inOrder(head->left);
    cout<<head->data<<" ";
    inOrder(head->right);
}

// VLR for in-order traversal
void preOrder(node *head){
    if(head==NULL)
        return;
    cout<<head->data<<" ";
    inOrder(head->left);
    inOrder(head->right);
}

// // LRV for in-order traversal
void postOrder(node *head){
    if(head==NULL)
        return;
    inOrder(head->left);
    inOrder(head->right);
    cout<<head->data<<" ";
}

int main() 
{
    // Create a binary tree.
    node *head = new node(10);
    head->left = new node(20);
    head->right = new node(30);
    
    cout<<"Inorder: "<<endl;
    inOrder(head); // LVR
    
    cout<<endl<<"PreOrder: "<<endl;
    preOrder(head); // VLR
    
    cout<<endl<<"PostOrder: "<<endl;
    postOrder(head); // LRV
    return 0; 
} 
