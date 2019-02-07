/* 
Harshit Gupta | 6th February, 2019

https://www.geeksforgeeks.org/avl-tree-set-1-insertion/

C++ program for Inserting elements in an AVL Tree.

AVL Tree
========
AVL tree is a self-balancing Binary Search Tree (BST) where the difference between heights of left and right
subtrees cannot be more than one for all nodes.

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

---

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


Solution: 

Paradigm: 

Time Complexity: 

*/

#include <bits/stdc++.h>
using namespace std; 

int main() 
{
    
    return 0; 
} 
