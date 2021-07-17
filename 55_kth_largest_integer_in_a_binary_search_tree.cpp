/* 
Harshit Gupta | 22nd February, 2019


C++ program for "Kth largest integer in a Binary Search Tree"

Solution: Inorder Traversal of a Binary Search Tree gives a sorted list (Ascending).
	Get the Kth largest integer by printing inorder and then taking Kth integer from back in O(N) time.

	Reverse Inorder Traversal of a Binary Search Tree gives a reverse sorted list (Descending).
	Get the Kth largest integer by printing reverse inorder and printing Kth integer in O(K) time.
		For values of N like 1 million and K to be small, O(K) is much better than O(N)

Paradigm: Heaps, PQ, Inorder

Time Complexity: O(K)

NOTE: 
	
	Similar Problem: 
		1. https://leetcode.com/problems/kth-smallest-element-in-a-bst/
			- This is simple plain inorder traversal.
			- O(k)
		2. https://leetcode.com/problems/kth-largest-element-in-an-array/
			- This uses a Min Heap of size K to insert the elements & the top element is Kth Largest.
			- O(nlogK)
		3. https://leetcode.com/problems/kth-largest-element-in-a-stream/
			- This uses the same Min Heap of size K and the top element would be Kth largest.
			- O(nlogK)

WHY MIN HEAP & NOT MAX HEAP?
>> Min Heap is better for this question. If it was Kth smallest in Array/Stream, 
	then Max Heap would have been better.

	Min Heap is better because that will serve our purpose, we want the Kth largest element to be 
		available at the top (so we can access it in O(1) time).
	For the Kth largest element to be at the top, all the k-1 elements which are greater than the 
		Kth largest are also important. 
	Hence, we must keep them, since after some time, one of them may become the Kth largest. 
	Also, The elements <K can be ignored since they can never become Kth largest so we just ignore them.

	All this would fit in perfectly in a min heap where the Kth largest will be at the top and 
		remaining K-1 elements (which are greater than K) will remain in the Min Heap.


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


// ------------------------------------------------------
// LEETCODE SOLUTION FOR Kth Smallest (Similar Problem 1)
// ------------------------------------------------------

// Approach 1: Do the complete inorder and select kth smallest
// TC: O(n)
// SC: O(n)
class Solution {
public:
    
    void inorder(TreeNode* root, vector<int>& v){
        if(root ==  NULL)
            return;
        inorder(root->left, v);
        v.push_back(root->val);
        inorder(root->right, v);
    }
    
    int kthSmallest(TreeNode* root, int k) {
        vector<int> v;
        inorder(root, v);
        return v[k-1];
    }
};


// Approach 2: Do the inorder and as soon as Kth smallest comes, return
// TC: O(k)
// SC: O(1)
class Solution {
public:
    
    void inorder(TreeNode* root, int& count, int k, int& ans){
        if(root ==  NULL || count > k || ans!=-1)
            return;
        inorder(root->left, count, k, ans);
        count++;
        
        if(count == k){
            ans = root->val;
            return;
        }
        
        inorder(root->right, count, k, ans);
    }
    
    int kthSmallest(TreeNode* root, int k) {
        int count = 0, ans=-1;
        inorder(root, count, k, ans);
        return ans;
    }
};


// ----------------------------------------------------
// LEETCODE SOLUTION FOR Kth Largest  Element in Array
// ----------------------------------------------------

class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        
        priority_queue <int,vector <int>,greater <int> > pq;
        
        for(int i=0;i<nums.size();i++){
            if(pq.size()<k){
                pq.push(nums[i]);
            }
            else{ // size == k
                if(pq.top()<nums[i]){
                    pq.pop();
                    pq.push(nums[i]);
                }
            }
        }
        
        return pq.top();
        
    }
};


// ----------------------------------------------------
// LEETCODE SOLUTION FOR Kth Largest  Element in Stream
// ----------------------------------------------------

class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int K;
    
    KthLargest(int k, vector<int>& nums) {
        K=k;
        for(auto n : nums)
            add(n);
    }
    
    int add(int val) {
        if(pq.size() < K)
            pq.push(val);
        else if(val > pq.top()) {
            pq.pop();
            pq.push(val);
        }
        return pq.top();
    }
};