/* 
Harshit Gupta | 22nd October, 2018

https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree-iii/

C++ program for finding the lowest common ancestor for two nodes of a Binary Tree (root node not given).

Solution: 
        1. Iterative.
        2. Recursion.

Time Complexity: O(N)

*/


// Definition for a Node.
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* parent;
};


// Approach 1: Iterative
// This solution uses the sum of the paths from the node till the root
// Assume Dist of p to root=x  and q to root=y
// the sum x+y will remain the same for both q and q.
// Out of this x+y, some dist is common(from LCA to root): z and some dist is their own(p/q to LCA)
// To reach LCA from p: we need to travel (x+(y-z)), LCA from q: we need to travel (y+(x-z)) as well.
// E.g: x:2, y:3 and z:1, x+y-z:4
// If you start from p and reach till x and then travel (y-z) you reach LCA!
// If you start from q and reach till y and then travel (x-z) you reach LCA!
// So after travelling x from p and y from q, we reach the root and its parent is NULL,
// then we start p from q and q from p so that they reach x+y-z at the same time!

class Solution {
public:
    
    Node* lowestCommonAncestor(Node* p, Node * q) {
        Node* a = p;
        Node* b = q;
        while(a!=b){
            // if(a!=NULL) cout<<"a: "<<a->val<<endl;
            // if(b!=NULL) cout<<"b: "<<b->val<<endl;
            // cout<<"---"<<endl;
            
            if(a==NULL)
                a = q;
            else
                a = a->parent;
            
            if(b == NULL)
                b = p;
            else
                b = b->parent;
        }
        return a;
        
    }
};


// Approach 2: Recursion

// This function is for searching a node when if one of them is the LCA of the other one
bool searchDown(Node* root, Node* p){
    if(root==NULL)
        return false;
    if(root == p || searchDown(root->left, p) || searchDown(root->right, p))
        return true;
    else 
        return false;
}

// Check if q is the LCA for p
// Check if p is the LCA for q
// If not, then check for their parents
Node* lowestCommonAncestor(Node* p, Node * q) {
    if(p == NULL || q == NULL || p==q)
        return p;
    if(searchDown(p,q))
        return p;
    else if (searchDown(q,p))
        return q;
    else
        return lowestCommonAncestor(p->parent, q->parent);
}