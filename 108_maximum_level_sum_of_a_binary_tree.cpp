
/*

Harshit Gupta | 5th June, 2021
---------------------------------

C++ program for 

Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.
Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

https://leetcode.com/problems/maximum-level-sum-of-a-binary-tree/

Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
    Level 1 sum = 1.
    Level 2 sum = 7 + 0 = 7.
    Level 3 sum = 7 + -8 = -1.
    So we return the level with the maximum sum which is level 2.

------

Solution: We will go through each level with help of BFS and update the level on the basis of the sum at this level. 
    More explanation below..

Time Complexity: O(n)
Space Complexity: O(n) for queue

Paradigm: BFS
---
  NOTE: 

*/



class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        
        // If both left and right child are not present, there is just 1 level
        if(root->left == NULL && root->right == NULL)
            return 1;
        
        // Set some vars
        int max_sum=INT_MIN, sum_of_this_level=0, max_level=0;
        
        // Get a queue to store a pair of node* and level. Insert the root node here with level 1
        queue<pair<TreeNode*, int>> q;
        q.push({root,1});
        q.push({NULL, 1});
        
        // BFS: Till the queue is empty
        while(!q.empty()){
            
            // Get the front node & pop it
            pair<TreeNode*, int> front = q.front();
            q.pop();
            
            // If the node is a NULL, it means that the level has ended so we update the max_sum by checking it with this level's sum. 
            // If it is more, update max_level
            if(front.first == NULL ){
                if(sum_of_this_level > max_sum){
                    max_sum = sum_of_this_level;
                    max_level = front.second;
                }
                // If after popping this null, the size is 0, we do not want to keep pushing NULLs but we want to break from the loop
                if(q.size() == 0)
                    break;
                // Push a null notifying the end of the level & reset the sum of level count to 0
                q.push({NULL, front.second+1});
                sum_of_this_level = 0;
            }
            // Insert the left and right child of the node if they are not NULLs and update the sum of this level with your val
            else{
                sum_of_this_level += front.first->val;
                if(front.first->left)
                    q.push({front.first->left, front.second+1});
                if(front.first->right)
                    q.push({front.first->right, front.second+1});   
            }
        }
        
        return max_level;
        
    }
};



// ---------------------------------------------------
// SOLUTION WITHOUT INVOLVING NULLS - CLEANER SOLUTION
// ---------------------------------------------------

class Solution {
public:
    int maxLevelSum(TreeNode* root) {
        
        // If both left and right child are not present, there is just 1 level
        if(root->left == NULL && root->right == NULL)
            return 1;
        
        int max_sum=INT_MIN, sum_of_this_level=0, max_level=1, level=1;
        
        queue<TreeNode*> q;
        q.push(root);
        
        while(!q.empty()){
            int size = q.size();
            sum_of_this_level = 0;
            for(int i=0; i<size; i++){
                TreeNode* front = q.front();
                q.pop();
                
                sum_of_this_level+=front->val;
                
                if (front->left)
                    q.push(front->left);
                if (front->right)
                    q.push(front->right);
            }
            if(sum_of_this_level > max_sum){
                max_sum = sum_of_this_level;
                max_level = level;
            }
            level++;
        }
        
        return max_level;
        
    }
};