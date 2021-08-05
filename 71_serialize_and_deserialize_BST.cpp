/*

Harshit Gupta | 10th October, 2020
---------------------------------

C++ program for "Serializing and Deserializing a BST"
https://leetcode.com/problems/serialize-and-deserialize-bst/
------

Solution: 
  Serialize: We do a Pre-Order Traversal of the BST and store it in a string separated by commas.
  Deserialize: We parse the string and convert it into a vector. Then we parse the vector to create the same BST again.

Why PreOrder?
    Let's use here the fact that BST could be constructed from preorder or postorder traversal only.
    In brief, it's a consequence of two facts:
    - Binary tree could be constructed from preorder/postorder and inorder traversal.
    - Inorder traversal of BST is an array sorted in the ascending order: inorder = sorted(preorder).

https://www.youtube.com/watch?v=H594EV9OuDI

Time Complexity: Serialize, Deserialize: O(N)
Space Complexity: Serialize: O(1)

Similar Questions:
    1. https://leetcode.com/problems/construct-binary-search-tree-from-preorder-traversal/
        - Construct BST with the preorder traversal.
        - We use this in Deserializing in the prev question.

*/



 // Definition for a binary tree node.
 struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
 
class Codec {
public:
  // ----------------------
  //    SERIALIZE BELOW
  // ----------------------

    void preOrder(TreeNode *root, string& s){
        if (root==NULL)
            return;
        s += to_string(root->val);
        s += ',';
        preOrder(root->left, s);
        preOrder(root->right, s);
    }

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        string s = "";
        preOrder(root, s);
        cout<<s<<endl;
        return s;
    }

    // ----------------------
    //   DESERIALIZE BELOW
    // ----------------------
  
    int findDiv(vector<int> v, int val, int low, int high){
        int i;
        for(i=low; i<=high; i++) {
            if(val < v[i]){
                break;
            }
        }
        return i;
    }
  
    TreeNode* deserializeHelper (vector<int> v, int low, int high){
        if(low>high)
            return NULL;
        // Create a node for v[low].
        TreeNode* root = new TreeNode (v[low]);
    
        // Find the index which has a number larger than v[low],
        // At that point we divide the array and elements to the left will be in Left subtree
        // and elements to the right are in the right subtree (since it is BST).
        int divIndex = findDiv(v, root->val, low+1, high);

        // Contruct the trees similarly for left and right subtree.
        root->left = deserializeHelper(v, low+1, divIndex-1);
        root->right = deserializeHelper(v, divIndex, high);
    
        return root;
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string s) {
        int n = s.size();
        vector<int> v;
        string buff = "";
        // Convert from comma separated string to a vector of ints.
        for(int i=0;i<n;i++){
            if(s[i]==','){
                v.push_back(stoi(buff));
                buff = "";
            }
            else{
                buff += s[i];
            }
        }
    return deserializeHelper(v, 0, v.size()-1);
    }
};


// ------------------------------------------------
// SIMILAR QUESTION 1 : BST FROM PREORDER TRAVERSAL
// ------------------------------------------------

//     8
//    / \
//   5   10
//  /\     \
// 1  7    12

// preorder = [8, 5, 1, 7, 10, 12]

// idx represent the index we are dealing with in the preorder array
// helper(INT_MIN, INT_MAX) is called for idx=0, which is 8
// 8->left is helper(INT_MIN, 8) increasing idx=1 now
//      5->left is helper(INT_MIN, 5) idx=2
//          1->left is helper(INT_MIN, 1) idx=3
//              val = 7 now and it doesn't lie between INT_MIN to 1 so we return NULL, ids = still 3
//          1->left = NULL, 
//          1->right is helper(1, 5)
//              val = 7 now and it doesn't lie between 1 to 5 so we return NULL, ids = still 3
//          1->right = NULL
//      5->left = 1 
//      5->right is helper(5, 8), idx=3
//          7->left = helper(7, 8) idx =4
//              val = 10 now and it doesn't lie between 7 and 8 so return NULL
//             7->left = NULL
//             7->right = NULL
//      5->right = 7
// 8->left 5 now
// 8->right = helper(8, INT_MAX) idx = 4
//      10->left = helper(8, 10) idx= 5
//          12->left = helper(10, 12) = NULL since idx reaches n
//          12->right = helper(12, INT_MAX) = NULL since idx reaches n
//      10->left = NULL
//      10->right = 12
// 8->right = 10

class Solution {
public:
    int idx = 0;
    vector<int> preorder;
    int n;
    
    TreeNode* helper(int lower, int upper){
        if (idx == n) 
            return NULL;
        
        int val = preorder[idx];
        
        if(val < lower || val > upper) 
            return NULL;
        
        idx++;
        TreeNode *root = new TreeNode(val);
        root->left = helper(lower, val);
        root->right = helper(val, upper);
        return root;
    }
    
    TreeNode* bstFromPreorder(vector<int>& preorder) {
        this->n = preorder.size();
        this->preorder = preorder;
        return helper(INT_MIN, INT_MAX);
    }
};