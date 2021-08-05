
/*

Harshit Gupta | 4th Agugust, 2021
---------------------------------

Problem Statement: PATH SUM

      5
     / \
    4   8
   /   / \
  11  13   4
  /\        \
 7  2        1

targetSum: 22
Path: [5->4->11->2]

1. https://leetcode.com/problems/path-sum/
	- Given the root of a binary tree and an integer targetSum, return true if the tree has a 
		"root-to-leaf" path such that adding up all the values along the path equals targetSum.
	- Apply DFS to check for the currentSum and if it is achieved at a leaf node.
	- TC: O(n), SC: O(n) for recursion stack

2. https://leetcode.com/problems/path-sum-ii/
	- Given the root of a binary tree and an integer targetSum, return all root-to-leaf 
		paths where each path's sum equals targetSum.
	- We need to keep saving the current Path of the Nodes and Apply DFS to check for the currentSum 
		and if it is achieved at a leaf node, we save it into another vector.
	- BACKTRACK: Note that we after adding a node to the current path, we must remove it from the currentPath 
		after both its childs are iterated. We do this so that we can maintain the correct "currentPath"
		for all the nodes that we visit.
	- TC: O(n2), SC: O(n)

3. https://leetcode.com/problems/path-sum-iii/

4. https://leetcode.com/problems/path-sum-iv/

5. https://leetcode.com/problems/minimum-falling-path-sum/

6. https://leetcode.com/problems/minimum-falling-path-sum-ii/

7. https://leetcode.com/problems/binary-tree-maximum-path-sum/

8. https://leetcode.com/problems/minimum-path-sum/

9. https://leetcode.com/problems/binary-tree-paths/

------

Solution: 

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/

// ----------
// PATH SUM 1
// ----------
class Solution {
public:
    
    bool dfs(TreeNode* node, int currentSum, int target){
        if(node == NULL)
            return false;
        if(currentSum+node->val == target && node->left == NULL && node->right == NULL)
            return true;
        return dfs(node->left, currentSum+node->val, target) ||  dfs(node->right, currentSum+node->val, target);
    }
    
    bool hasPathSum(TreeNode* root, int targetSum) {
        if(root== NULL)
            return false;
        return dfs(root,0,targetSum);
    }
};


// -------------
// PATH SUM - 2
// -------------
// TC: 
// 		Consider the tree like so:
// 		          A
// 		         / \
// 		        B   C
// 		           / \
// 		          D   E
// 		             / \
// 		        and so on...
// 		Let the number of nodes = n
// 		Therefore depth of tree is approx n/2 and number of leaves are also approx n/2
// 		Now, potential correct paths are of length: 2, 3, ... n/2
// 		Copying these n/2 paths n/2 times to the answer arr gives us the time complexity O(n*2)
// SC: O(n)

class Solution {
public:
    vector<vector<int>> ans;
    
    void dfs(TreeNode* node, int currentSum, int target, vector<int>& currentPath){
        if(node == NULL)
            return;
        
        // add node to the current path
        currentPath.push_back(node->val);
        
        if(currentSum+node->val == target && node->left == NULL && node->right == NULL)
            ans.push_back(currentPath);
        else{
            dfs(node->left, currentSum+node->val, target, currentPath);
            dfs(node->right, currentSum+node->val, target, currentPath);    
        }
        
        // backtrack
        currentPath.pop_back();
    }
    
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if(root == NULL)
            return {};
        vector<int> currentPath;
        dfs(root, 0, targetSum, currentPath);
        return ans;
    }
};