/* 
Harshit Gupta | 3rd November, 2018

https://ide.geeksforgeeks.org/xt9mwoLfV3
https://www.geeksforgeeks.org/diameter-of-a-binary-tree/
https://leetcode.com/problems/diameter-of-binary-tree/

C++ program for finding diameter of a binary tree. The diameter of a tree 
(sometimes called the width) is the number of nodes on the longest path between two end nodes.

Paradigm: Recursions, Binary Trees
Time Complexity: O(n)

LEETCODE PROBLEM SOLUTION:
--------------------------
Algo: Find the node where the sum of its longest left and right branches is maximized.
          10
         / \
        3   1
       / \ 
      5   4
     /   /
    2   9
   /   /
  8   7

Take the tree for example, 
diameter = 0, root= 10
longestPath(8)=max(0,0)+1 = 1, diameter = max(0,0+0)=0
longestPath(7)=max(0,0)+1 = 1, diameter = max(0,0+0)=0
longestPath(2)=max(1,0)+1 = 2, diameter = max(2,3+3)=1
longestPath(9)=max(1,0)+1 = 2, diameter = max(1,1+0)=1
longestPath(5)=max(2,0)+1 = 3, diameter = max(1,2+0)=2
longestPath(4)=max(2,0)+1 = 3, diameter = max(2,2+0)=2
longestPath(3)=max(3,3)+1 = 4, diameter = max(2,3+3)=6
longestPath(1)=max(0,0)+1 = 1, diameter = max(6,0+0)=6
longestPath(1)=max(4,1)+1 = 5, diameter = max(6,4+1)=6

Notes:
 1. Diamter is maximum of leftPath+rightPath for ALL the NODES (not just root)
 2. The leftPath and rightPath are calculated by the max path of their child+1
 3. Basically we are iterating over the whole tree calculating the longestPath, diameter is just calculated amidst all that.

Definition for a binary tree node.
*/

 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

class Solution {
private:
    int diameter;
public:
    
    // longestPath takes a TreeNode as input and returns the longest path from it to the leaf node.
    // It will recursively visit children nodes and retrieve the longest paths from them to the leaf first, and then add 1 to the longer one before returning it as the longest path.
    // The return type of this fn has nothing to do with the diameter.
    // diameter is calculated in between as the leftPath+rightPath for every node.
    int longestPath(TreeNode* node){
        if(node == NULL)
            return 0;
        
        // recursively find the longest path in both left child and right child
        int leftPath = longestPath(node->left);
        int rightPath = longestPath(node->right);
        
        // update the diameter if left_path plus right_path is larger
        diameter = max(diameter, leftPath+rightPath);
        
        // return the longest one between left_path and right_path; 
        // remember to add 1 for the path connecting the node and its parent
        return max(leftPath,rightPath)+1;
        
    }
    
    int diameterOfBinaryTree(TreeNode* root) {
        diameter = 0;
        longestPath(root);
        return diameter;
    }
};

// ------------------------------------------------------------------------------------------

// Approach 2:

// Solution: The diameter of a tree is: max(max(ldia, rdia), lh+rh+1)
//     We can have a O(n2) Solution easily but the O(n) solution is really tricky.
//     The trick is that we are calculating height in the same recursion 
//     as the diameter recursion. Each node has its own copy of the variables 
//     'lh', 'rh', 'ldia' and 'rdia'.
//     The values of 'ldia' and 'rdia' are the return values from prev recursions.
//     The values of 'lh' and 'rh' are passed by reference. 
//         They are updated and to the height of the left and right subtrees.
//     Then, we can easily calculate the diameter of the node since we know all the 4 var:
//         max(ldia, rdia, lh+rh+1);

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
