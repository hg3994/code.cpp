
/*

Harshit Gupta | 14th October, 2020
---------------------------------

C++ program for "Sorting a Linked List"

https://leetcode.com/problems/sort-list/
https://www.geeksforgeeks.org/merge-sort-for-linked-list/
https://en.wikipedia.org/wiki/Merge_sort
------

Solution: Using merge sort and "68_merge_two_sorted_lists"
  Comments below in great detail.

Time Complexity: O(NlogN)
Space Complexity: O(logn) , where n is the number of nodes in linked list. 
  Since the problem is recursive, we need additional space to store the recursive call stack. 
  The maximum depth of the recursion tree is log n
---
 
 Difference between pointer and pointer(*) to pointer(**)
1
  ListNode *head  -> A variable called 'head' which will store address of only ListNode types of data.
  ListNode **head -> A variable called 'head' which will store address of a pointer that will store address of only ListNode types of data.
  
  ListNode* head = new ListNode(10);
  ListNode** headref = *head; 
  ---
  Value of Node = 10
  Address of Node = 6000
  --
  Value at head = 6000
  Address of head = 5000
  --
  Value at headref  = 5000
  --

  We use *head when we want to change something in the node of address(6000), its 'val' or 'next' anything.
  We use **head when we want to change the '6000' itself. When we want to put address of some other node there.
*/


#include<bits/stdc++.h>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
  ListNode* sortList(ListNode* head) {
    return mergeSort(&head);
  }
  
  // ** because it is required to be called recursively like this with the address of head in this function.
  ListNode* mergeSort(ListNode** head){
    
    // Take a copy of the node address which head is pointing to.
    ListNode *headref = *head;
    ListNode *a = *head;
    ListNode *b;
    
    // Base condition when it boils down to just 1 node in the LL.
    // If the length of the LL is 0 or 1, return;
    if (headref==NULL || headref->next==NULL)
      return headref;
    
    /* 
        Divide the linked list into two halves from the middle.
      - We must pass address of a and b since we have GARBAGE present in them initially. 
        They are just pointers which will point to nodes in future. However, they do not have any 
        value in them now so we must pass the address to these 'a' and 'b' pointers so that we are 
        able to change the value present in these pointers and make them point to valid ListNodes.
      - If we send a node only, then we would be able to modify only the the LL and not the pointer which 
      points to the address but here we want to change that from GARBAGE to an actual node address.
    */
    frontBackSplit(headref, &b);
    
    // Now that a and b are valid LL separately. Sort the two halves a->..->.. and b->..->..
    // Address of 'a' since it may modify the head pointer.
    mergeSort(&a);
    mergeSort(&b);
    
    // Merge the sorted lists into just one and return the pointer to the first node.
    // This statement modifies the head of the method and due to this line we had to pass the address to the head pointer (**)
    *head = merge(a,b);
    return *head;
  }
  
  
  void frontBackSplit(ListNode *head, ListNode **last){
    // Take a fast and slow pointer and try to find the middle location.  
    ListNode* slow = head;
    ListNode* fast = head->next;
    
    while(fast!= NULL){
      fast = fast->next;
      if(fast!= NULL){
        slow = slow->next;
        fast = fast->next;
      }
    }
    
    // We have the first and last pointers which point to the head of their own LL.
    *last = slow->next;
    
    // Detach both LL to form separate LLs.
    slow->next = NULL;
  }
  
  
  ListNode* merge(ListNode *a, ListNode *b){
    
    // Base condition
    // If one LL is NULL, then return the second LL so that the whole 2nd LL is attached to the end.
    if (a==NULL)
      return b;
    else if (b==NULL)
      return a;
    
    // We must have an a node which will basically act like the 'head' node and then we return this node.
    // This will point to the 1st node of the LL for the 1st call.
    // This will point to the other nodes of the LL for other later calls.
    ListNode *result = NULL;
    
    if (a->val <= b->val){
      result = a;
      result->next = merge(a->next, b);
    }
    else {
      result = b;
      result->next = merge(a, b->next);
    }
    
    // This is the most important part. We return the result so that result->next gets the pointer to the next node.
    return result;
  }
  
};