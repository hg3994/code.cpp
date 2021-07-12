/* 
Harshit Gupta | 14th October, 2018

https://ide.geeksforgeeks.org/K6h4Dopr06
https://leetcode.com/problems/binary-tree-right-side-view/

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



// ----------------------------
// RIGHT VIEW LEETCODE SOLUTION
// ----------------------------

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    
    void helper(TreeNode* root, int currentLevel, int &maxLevel, vector<int>& res){
        if(root == NULL)
            return;
        if(currentLevel > maxLevel){
            res.push_back(root->val);
            maxLevel = currentLevel;
        }
        helper(root->right, currentLevel+1, maxLevel, res);
        helper(root->left, currentLevel+1, maxLevel, res);
    }
    
    vector<int> rightSideView(TreeNode* root) {
        int maxLevel = -1;
        vector<int> res;
        helper(root, 0, maxLevel, res);
        return res;
    }
};

