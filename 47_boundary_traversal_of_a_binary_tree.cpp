/* 
Harshit Gupta | 27th January, 2019

https://www.geeksforgeeks.org/boundary-traversal-of-binary-tree/
https://ide.geeksforgeeks.org/j1ubcwKifD

C++ program for "Given a binary tree, print boundary nodes of the binary tree Anti-Clockwise 
	starting from the root."

Solution: We break the problem in 3 parts:
						1. Print the left boundary in top-down manner.
						2. Print all leaf nodes from left to right,
						3. Print the right boundary in bottom-up manner.

					We need to take care of one thing that nodes are not printed again. e.g. The left most node is also the leaf node of the tree.

Paradigm: 

Time Complexity: 

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
	int data;
	struct node *left, *right;
	node(int data){
		this->data = data;
		this->left = NULL;
		this->right = NULL;
	}
};

typedef struct node node;

void leftBoundary(node *root){
	// If the root is NULL, return
	if(root==NULL){
		return;
	}
	// If we have left node, then print and recurse on the left child
		// NOTE: remember to print the node data inside if/elsif because if kept outside it will print
		// the leaf nodes as well which we don't want (it will cause repetitive printing of leaf nodes) 
	if (root->left){
		cout<<root->data<<" "<<endl;
		leftBoundary(root->left);
	}
	// If we have right node, then print and recurse on the right child
	else if(root->right){
		cout<<root->data<<" "<<endl;
		leftBoundary(root->right);
	}
}

void rightBoundary(node *root){
	// If the root is NULL, return
	if(root==NULL){
		return;
	}
	// If we have right node, then print and recurse on the right child
		// NOTE: remember to print the node data inside if/elsif because if kept outside it will print
		// the leaf nodes as well which we don't want (it will cause repetitive printing of leaf nodes) 
	if (root->right){
		rightBoundary(root->right);
		cout<<root->data<<endl;
	}
	// If we have left node, then print and recurse on the left child
	else if(root->left){
		rightBoundary(root->left);
		cout<<root->data<<endl;
	}
}

void leafNodes(node *root){
	// If the root is NULL, return
	if(root==NULL){
		return;
	}
	// print the node->data if both right and left nodes are NULL.
	if (root->left == NULL && root->right == NULL){
		cout<<root->data<<endl;
	} 
	// Recurse on Left and Right subtrees
	leafNodes(root->left);
	leafNodes(root->right);
}

void boundaryTraversal(node *root){
	//check if the root is NULL
	if(root){
		// print root node
		cout<<root->data<<endl;
		// print left boundary in top-down manner.
			// NOTE: Don't print leaf nodes in left boundary to avoid repetitive printing of leaf nodes while
			// executing leafNodes(root) function.
		leftBoundary(root->left);
		// print leaf nodes from left to right order
		leafNodes(root);
		// print right boundary in bottom-up manner
			// NOTE: Don't print leaf nodes in right boundary to avoid repetitive printing of leaf nodes while
			// executing leafNodes(root) function.
		rightBoundary(root->right);
	}
}

int main() 
{
  node *root = new node(20);
  root->left = new node(8);
  root->left->left = new node(4);
  root->left->right = new node(12);
  root->left->right->left = new node(10);
  root->left->right->right = new node(14);
  root->right = new node(22);
  root->right->right = new node(25);
  boundaryTraversal(root);
  return 0; 
} 
