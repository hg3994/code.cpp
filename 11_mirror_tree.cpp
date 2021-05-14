/* 
Harshit Gupta | 19th October, 2018

C++ program for 
    1. Finding the mirror tree of a given binary tree.
        a. Create a new Mirror Tree
        b. Modify the given tree inplace
    2. Is a given Binary tree a symmetric/mirror Tree?

https://ide.geeksforgeeks.org/ZLqeqL8WyO
https://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/
https://leetcode.com/problems/symmetric-tree/

Solution:   We will use recursion to solve our problem.
    * Copy the root node since that is always same.
    * Recur on the left and right subtree of root and then keep making nodes.
        Make a left subnode in the mirror tree for a right subnode in the normal tree.
        Make a right subnode in the mirror tree for a left subnode in the normal tree.
        Recur again on the nodes so that their subtree is also a mirror subtree.
    * Use Level Order Traversal to print the Trees.
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

void printTree(node *root){
    // Level Order Traversal (BFS) to print the tree.
    
    queue <node *> q;
    q.push(root);
    while(!q.empty()){
        node *f = q.front();
        q.pop();
        
        cout<<f->data<<" ";
        
        if(f->left!=NULL)
            q.push(f->left);
            
        if(f->right!=NULL)
            q.push(f->right);
    }
    cout<<endl;
}

void MirrorNodes(node *root1, node *root2){
    
    // If the root1's right child is not NULL, 
    // then make a node to root2's left with the same data.
    // Recur on the same function by setting root1=root1->right and root2=root2->left
    if(root1->right!=NULL){
        root2->left = new node(root1->right->data);
        MirrorNodes(root1->right, root2->left);
    }
    
    // If the root1's left child is not NULL, 
    // then make a node to root2's right with the same data.
    // Recur on the same function by setting root1=root1->left and root2=root2->right
    if(root1->left!=NULL){
        root2->right = new node(root1->left->data);
        MirrorNodes(root1->left, root2->right);
    }
}


void makeMirrorTree(node *root1){
    
    // Make the root2 node with the same data as root1
    node *root2 = new node(root1->data);
    
    // get the mirror tree with root as root2
    MirrorNodes(root1,root2);
    
    // Print the Level Order Traversal of both Trees to prove your point!
    cout<<"Normal Tree: "<<endl;printTree(root1);
    cout<<"Mirror Tree: "<<endl;printTree(root2);
}


void InPlaceMirrorTree(node* root){
    // This will modify the existing tree to its mirror tree

    // If the root is not NULL
    if(root != NULL){
        // swap the left and right pointers
        node* temp = root->left;
        root->left = root->right;
        root->right = temp;

        // If left child exists and its left or right child exists, then recur
        if(root->left && (root->left->left != NULL || root->left->right != NULL))
            InPlaceMirrorTree(root->left);

        // If right child exists and its left or right child exists, then recur
        if(root->right && (root->right->left != NULL || root->right->right != NULL))
            InPlaceMirrorTree(root->right);
        
    }

    // NOTE: This method uses Pre-Order kind of traversal but it is equally good to use Post order traversal here
}

// Is the given binary tree a mirror tree?
bool isMirror(node *t1, node* t2){
    if(t1 == NULL && t2 == NULL) return true;
    if(t1 == NULL || t2 == NULL) return false;
    return (t1->data == t2->data) && isMirror(t1->left, t2->right) && isMirror(t1->right, t2->left);
}

int main(){
    
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left = new node(40);
    root->left->right = new node(50);
    // root->right->left = new node(60);
    root->right->right = new node(70);
    
    // To make a new mirror tree from a Binary Tree.
    makeMirrorTree(root);

    // To modify the existing Binary Tree to its own Mirror Tree.
    InPlaceMirrorTree(root);
    cout<<"Normal Tree: "<<endl;printTree(root);
    
    // Check if it is a mirror tree by sending two args
    cout<<"Is Mirror Tree?: "<<isMirror(root, root)<<endl;

    return 0;
}