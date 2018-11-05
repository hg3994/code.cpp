/* 
Harshit Gupta | 3rd November, 2018

https://ide.geeksforgeeks.org/xt9mwoLfV3
https://www.geeksforgeeks.org/diameter-of-a-binary-tree/

C++ program for finding diameter of a binary tree

Solution: We can have a O(n2) Solution easily but the O(n) solution is really tricky.
    The trick is that we are calculating height in the same recursion 
    as the diameter recursion. Each node has its own copy of the variables 
    'lh', 'rh', 'ldia' and 'rdia'.
    The values of 'ldia' and 'rdia' are the return values from prev recursions.
    The values of 'lh' and 'rh' are passed by reference. 
        They are updated and to the height of the left and right subtrees.
    Then, we can easily calculate the diameter of the node since we know all the 4 var:
        max(ldia, rdia, lh+rh+1);

Paradigm: Recursions, Binary Trees

Time Complexity: O(n)

*/

#include <bits/stdc++.h>
using namespace std; 

typedef struct node node;

struct node{
    int data;
    node *left;
    node *right;
    
    node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

int diameter(node *root, int *height){
    
    // Initialize the left height and right height for EACH NODE as 0.
    int lh = 0;
    int rh = 0;
    
    // Initialize the left and right diameter for EACH NODE as 0.
    int ldia = 0;
    int rdia = 0;
    
    // For leaf nodes, the height is set to 0.
    // The diameter is returned 0 from here.
    if(root==NULL){
        *height = 0;
        return 0;
    }
    
    // Update the left height and right height for the node from 0 to the real value.
    // Also, get the diameter of the left and right subtree.
    ldia = diameter(root->left, &lh);
    rdia = diameter(root->right, &rh);
    
    // This variable 'height' is representing either lh or rh from the previous call.
    // This updates the height of the left and right subtrees (lh and rh).
    *height = max(lh,rh)+1;
    
    // Uncomment this to see how the recursion happens.
    // cout<<"Node: "<<root->data<<" height: "<<(*height)<<endl;
    // cout<<"ldia: "<<ldia<<" rdia: "<<rdia<<endl;
    // cout<<"lh: "<<lh<<" rh: "<<rh<<endl;
    // cout<<"----------"<<endl;
    
    // This returns the diameter of each node.
    return max(max(ldia, rdia), lh+rh+1);
}

int main() 
{
    /* Constructed binary tree is  
                1 
              /   \ 
            2      3 
          /  \ 
        4     5 
    */
  node *root        = new node(1); 
  root->left        = new node(2); 
  root->right       = new node(3); 
  root->left->left  = new node(4); 
  root->left->right = new node(5); 
  
  int height = 0;
  int ans = diameter(root,&height);
  cout<<ans<<endl;
  
    return 0; 
} 
