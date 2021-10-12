/* 
Harshit Gupta | 3rd November, 2018

https://ide.geeksforgeeks.org/xt9mwoLfV3
https://www.geeksforgeeks.org/diameter-of-a-binary-tree/
https://leetcode.com/problems/diameter-of-binary-tree/

C++ program for finding diameter of a binary tree. The diameter of a tree 
(sometimes called the width) is the number of EDGES(not NODES) on the longest path between two end nodes.

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
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };


 Similar Problem:
    1. https://leetcode.com/problems/maximum-depth-of-binary-tree/
        - Max Height of the Tree
    2. Print the elements forming the max Height of the Tree

*/ 

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


// ---------------------------
// LEETCODE SIMILAR QUESTION 1
// ---------------------------

class Solution {
public:
    int maxDepth(TreeNode* root) {
        if(root == NULL)
            return 0;
        int leftPath = maxDepth(root->left);
        int rightPath = maxDepth(root->right);
        
        return max(leftPath, rightPath)+1;
    }
};

// SIMILAR QUESTION 2

vector<int> result;
bool elementInMaxDepth(TreeNode* node, vector<int>& temp){
    int n = temp.size();
    if(node == NULL){
        if(temp.size() > result.size()){
            result = temp;
            return;
        }
    }
    temp.push_back(node->val);
    elementInMaxDepth(node->left, temp);
    elementInMaxDepth(node->right, temp);
    temp.pop_back();
}

