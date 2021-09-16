/* 
Harshit Gupta | 6th February, 2019

https://ide.geeksforgeeks.org/HmLDqj35Wu
https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

C++ program for Inserting elements in an AVL Tree.

AVL Tree
========
AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right
subtrees cannot be more than one for all nodes.

Other Self Balancing Binary Search Trees are:
  Red–black tree
  B-tree
  2–3 tree
  AA tree
  Scapegoat tree
  Splay tree
  Tango tree
  Treap
  Weight-balanced tree

Why AVL Trees?
Most of the BST operations (e.g., search, max, min, insert, delete.. etc) take O(h) time where h is the height
of the BST. The cost of these operations may become O(n) for a skewed Binary tree. If we make sure that height 
of the tree remains O(Logn) after every insertion and deletion, then we can guarantee an upper bound of O(Logn) 
for all these operations. The height of an AVL tree is always O(Logn) where n is the number of nodes in the tree

Steps to follow for insertion:
Let the newly inserted node be w
1) Perform standard BST insert for w.
2) Starting from w, travel up and find the first unbalanced node. Let z be the first unbalanced node, y 
	be the child of z that comes on the path from w to z and x be the grandchild of z that comes on the path 
	from w to z.
3) Re-balance the tree by performing appropriate rotations on the subtree rooted with z. There can be 
	4 possible cases that needs to be handled as x, y and z can be arranged in 4 ways. Following are the 
		possible 4 arrangements:
		a) y is left child of z and x is left child of y (Left Left Case)
		b) y is left child of z and x is right child of y (Left Right Case)
		c) y is right child of z and x is right child of y (Right Right Case)
		d) y is right child of z and x is left child of y (Right Left Case)

		a) Left Left Case
		=================

		T1, T2, T3 and T4 are subtrees.
		         z                                      y 
		        / \                                   /   \
		       y   T4      Right Rotate (z)          x      z
		      / \          - - - - - - - - ->      /  \    /  \ 
		     x   T3                               T1  T2  T3  T4
		    / \
		  T1   T2

		b) Left Right Case
		==================

		     z                               z                           x
		    / \                            /   \                        /  \ 
		   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
		  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
		T1   x                          y    T3                    T1  T2 T3  T4
		    / \                        / \
		  T2   T3                    T1   T2
		
		c) Right Right Case
		===================

		  z                                y
		 /  \                            /   \ 
		T1   y     Left Rotate(z)       z      x
		    /  \   - - - - - - - ->    / \    / \
		   T2   x                     T1  T2 T3  T4
		       / \
		     T3  T4

		d) Right Left Case
		==================

		   z                            z                            x
		  / \                          / \                          /  \ 
		T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
		    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
		   x   T4                      T2   y                  T1  T2  T3  T4
		  / \                              /  \
		T2   T3                           T3   T4

---

IMPLEMENTATION
==============

	The following implementation uses the recursive BST insert to insert a new node. In the recursive BST insert, 
	after insertion, we get pointers to all ancestors one by one in a bottom-up manner. So we don’t need parent 
	pointer to travel up. The recursive code itself travels up and visits all the ancestors of the newly inserted node.

	1) Perform the normal BST insertion.
	2) The current node must be one of the ancestors of the newly inserted node. Update the height of the current node.
	3) Get the balance factor (left subtree height – right subtree height) of the current node.
	4) If balance factor is greater than 1, then the current node is unbalanced and we are either in Left Left case or 
	left Right case. To check whether it is left left case or not, compare the newly inserted key with the key in left 
	subtree root.
	5) If balance factor is less than -1, then the current node is unbalanced and we are either in Right Right case 
	or Right-Left case. To check whether it is Right Right case or not, compare the newly inserted key with the key 
	in right subtree root.


Solution: 

Paradigm: 

Time Complexity: 

*/

#include <bits/stdc++.h>
using namespace std; 

// An AVL tree node 
struct Node { 
  int key; 
  struct Node *left; 
  struct Node *right; 
  int height; 

  // constructor
  Node(int key){
  	this->key = key;
  	this->left = NULL;
  	this->right = NULL;
  	this->height = 1;
  }
};

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return N->height; 
} 

// A utility function to left rotate subtree rooted with x 
// See the diagram given above. 
struct Node *leftRotate(struct Node *x) 
{ 
  struct Node *y = x->right; 
  struct Node *T2 = y->left; 

  // Perform rotation 
  y->left = x; 
  x->right = T2; 

  //  Update heights 
  x->height = max(height(x->left), height(x->right))+1; 
  y->height = max(height(y->left), height(y->right))+1; 

  // Return new root 
  return y; 
} 

// A utility function to right rotate subtree rooted with y 
// See the diagram given above. 
struct Node *rightRotate(struct Node *y) 
{ 
  struct Node *x = y->left; 
  struct Node *T2 = x->right; 

  // Perform rotation 
  x->right = y; 
  y->left = T2; 

  // Update heights 
  y->height = max(height(y->left), height(y->right))+1; 
  x->height = max(height(x->left), height(x->right))+1; 

  // Return new root 
  return x; 
} 



// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
    if (N == NULL) 
        return 0; 
    return height(N->left) - height(N->right); 
} 

struct Node *insertIntoAVL (struct Node *node, int key){

	/* 1.  Perform the normal BST insertion */
  if (node == NULL) 
      return(new Node(key)); 

  if (key < node->key) 
      node->left  = insertIntoAVL(node->left, key); 
  else if (key > node->key) 
      node->right = insertIntoAVL(node->right, key); 
  else // Equal keys are not allowed in BST 
      return node; 

  /* 2. Update height of this ancestor node */
  node->height = 1 + max(height(node->left), 
                         height(node->right)); 


  /* 3. Get the balance factor of this ancestor 
        node to check whether this node became 
        unbalanced */
  int balance = getBalance(node); 

  // If this node becomes unbalanced, then 
  // there are 4 cases 

  // Left Left Case 
  if (balance > 1 && key < node->left->key) 
      return rightRotate(node); 

  // Right Right Case 
  if (balance < -1 && key > node->right->key) 
      return leftRotate(node); 

  // Left Right Case 
  if (balance > 1 && key > node->left->key) 
  { 
      node->left =  leftRotate(node->left); 
      return rightRotate(node); 
  } 

  // Right Left Case 
  if (balance < -1 && key < node->right->key) 
  { 
      node->right = rightRotate(node->right); 
      return leftRotate(node); 
  } 

  /* return the (unchanged) node pointer */
  return node; 
  
}

// A utility function to print preorder traversal 
// of the tree. 
// The function also prints height of every node 
void preOrder(struct Node *root) { 
  if(root != NULL) { 
    printf("%d ", root->key); 
    preOrder(root->left); 
    preOrder(root->right); 
  } 
} 


int main() 
{
  struct Node *root = NULL; 
    
  /* Constructing tree given in the above figure */
  root = insertIntoAVL(root, 10); 
  root = insertIntoAVL(root, 20); 
  root = insertIntoAVL(root, 30); 
  root = insertIntoAVL(root, 40); 
  root = insertIntoAVL(root, 50); 
  root = insertIntoAVL(root, 25); 
  
  /* The constructed AVL Tree would be 
            30 
           /  \ 
         20   40 
        /  \     \ 
       10  25    50 
  */  

  printf("Preorder traversal of the constructed AVL"
         " tree is \n"); 
  preOrder(root); 
  return 0; 
} 
