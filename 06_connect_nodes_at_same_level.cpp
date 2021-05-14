/* 
Harshit Gupta | 17th October, 2018

C++ program for Connecting Nodes at same level

https://leetcode.com/problems/populating-next-right-pointers-in-each-node

Solution: We will use Level Order Traversal to connect nodes at the same level.
    * The strategy is to enqueue NULL in the queue after end of each level.
    * We keep enquing left and right nodes of a tree.
    * We know we can pop an element and then it has to be connected with queue.front() now
    * When we see that we have a NULL in the queue, 
        then we know that we have enqueued left and right nodes for the previous level, 
        so we will add another NULL which will signify end of this level.
    * We print the COnnected Graph with help of Level Order Traversal on it.
*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
    int data;
    struct node *left, *right, *next_right;
    node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
        this->next_right = NULL;
    }
};

typedef struct node node;

void connectNodesAtSameLevel(node *root){
    queue <node *> q;
    
    // Enqueuing the root
    q.push(root);
    // Enqueuing NULL since it signifies end of this level.
    q.push(NULL);
    
    while(!q.empty()){
        
        // Take the front node. This will point to the node now in q.front() if not NULL;
        node *f = q.front();
        q.pop();
        
        if(f!=NULL){
            
            // Pointing f to the node now in q.front();
            f->next_right = q.front();
            
            // Enqueue the children of 'f' if they are not NULL.
            if (f->left != NULL)
                q.push(f->left);
            if (f->right != NULL)
                q.push(f->right);
        }
        else if(!q.empty()){ 
            // f == NULL meaning the level has ended and nodes of next level are already in queue. 
            // Mark the end of their level.
            q.push(NULL);
            
        }
    }
}

// Simply traverse with L.O.T. and get the connected Tree
void printConnectedTree(node *root){
    
    queue <node*> q;
    q.push(root);
    
    while(!q.empty()){
        node *f = q.front();
        q.pop();
        
        if (f->next_right == NULL)
            cout<<f->data<<" -> NULL"<<endl;
        else
            cout<<f->data<<" -> "<<f->next_right->data<<endl;
        
        if(f->left)
            q.push(f->left);
        if(f->right)
            q.push(f->right);
    }
    
}

int main() 
{
    node *root= new node(10);
    root->left= new node(20);
    root->right= new node(30);
    root->left->left= new node(40);
    root->right->right= new node(50);
    root->left->left->right= new node(60);
    
    connectNodesAtSameLevel(root);
    printConnectedTree(root);
    
    return 0; 
} 
