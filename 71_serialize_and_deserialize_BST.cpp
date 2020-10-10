/*

Harshit Gupta | 10th October, 2020
---------------------------------

C++ program for "Serializing and Deserializing a BST"
https://leetcode.com/problems/serialize-and-deserialize-bst/
------

Solution: 
  Serialize: We do a Pre-Order Traversal of the BST and store it in a string separated by commas.
  Deserialize: We parse the string and convert it into a vector. Then we parse the vector to create the same BST again.

https://www.youtube.com/watch?v=H594EV9OuDI

Time Complexity: Serialize, Deserialize: O(N)
Space Complexity: Serialize: O(1)

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
    // and elements to the right are in the right subtree.
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

// Commented this I will have to write a printTree function
// Your Codec object will be instantiated and called as such:
// int main() {
//   Codec* ser = new Codec();
//   Codec* deser = new Codec();
//   string tree = ser->serialize(root);
//   TreeNode* ans = deser->deserialize(tree);
//   printTree(ans);
// }