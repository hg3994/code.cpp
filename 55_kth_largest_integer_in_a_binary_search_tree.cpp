/* 
Harshit Gupta | 22nd February, 2019


C++ program for "Kth largest integer in a Binary Search Tree"

Solution: Inorder Traversal of a Binary Search Tree gives a sorted list (Ascending).
	Get the Kth largest integer by printing inorder and then taking Kth integer from back in O(N) time.

	Reverse Inorder Traversal of a Binary Search Tree gives a reverse sorted list (Descending).
	Get the Kth largest integer by printing reverse inorder and printing Kth integer in O(K) time.

	For values of N like 1 million and K to be small, O(K) is much better than O(N)

Paradigm: 

Time Complexity: O(K)

NOTE: Related Problem: https://leetcode.com/problems/kth-largest-element-in-an-array/

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
	int data;
	struct node *left, *right;
	node (int data) {
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

typedef struct node node;

void KthLargestIntegerInBST(node* root, int k, int &count) {
	// Uncomment to see that it takes O(K) time only. It doesn't iterate into all the N nodes.
	// cout<<count<<endl;
	
	// Base cases, the second condition is important to avoid unnecessary recursive calls.
	// This is the reason why the time complexity is O(K) and not O(N)
	if(root== NULL || count>k)
	    return;

    // Follow reverse inorder traversal so that the largest element is visited first 
	KthLargestIntegerInBST(root->right, k, count);

    // Increase the counter of the number of nodes covered till now.
	count++;
	
	// If count becomes k now, then this is the k'th largest node.
	if (k== count){
		cout<<"The Kth largest integer in the BST is: "<<root->data<<" ";
		return;
	}
	
	// Recur for left subtree
	KthLargestIntegerInBST(root->left, k, count);

}

int main() {
  node *root = new node(30);
  root->left = new node(20);
  root->right = new node(40);
  root->left->left = new node(10);
  root->left->right = new node(25);
  root->right->left = new node(35);
  root->right->right = new node(50);
  int k = 3;
  int count = 0;
  KthLargestIntegerInBST(root, k, count);
  return 0; 
} 
