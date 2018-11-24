/* 
Harshit Gupta | 19th October, 2018

C++ program for finding the mirror tree of a given binary tree.

https://ide.geeksforgeeks.org/mNSyzs8gDP
https://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/

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

int main(){
    
    node *root = new node(10);
    root->left = new node(20);
    root->right = new node(30);
    root->left->left = new node(40);
    root->left->right = new node(50);
    // root->right->left = new node(60);
    root->right->right = new node(70);
    
    makeMirrorTree(root);
    return 0;
}