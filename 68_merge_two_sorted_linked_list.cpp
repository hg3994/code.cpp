/*

Harshit Gupta | 1st October, 2020
---------------------------------

C++ program for 
  Merge two sorted linked lists and return it as a new sorted list. 
  The new list should be made by splicing together the nodes of the first two lists.

https://leetcode.com/problems/merge-two-sorted-lists/

Input: 1->2->4, 1->3->4
Output: 1->1->2->3->4->4
------

Solution: https://leetcode.com/problems/merge-two-sorted-lists/solution/

For itertive solution:
  Time Complexity: O(n)
  Space Complexity: O(1)

For recursive solution:
  TC: O(n+m)
  SC: O(n+m)

NOTE: 
  1. This program can not be compiled since I didn't have time to write the LL creation methods.
  2. Recursive Solution is so so simple. Just look at it.
*/


#include<bits/stdc++.h>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(NULL) {}
    ListNode(int x) : val(x), next(NULL) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
  public:
  
  // void printLL(ListNode *a){
  //   while(a!= NULL){
  //     cout<<a->val<<" ";
  //     a = a->next;
  //   }
  //   cout<<endl;
  // }
  
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;
    
    ListNode prehead = ListNode(-1);
    ListNode *prev = &prehead;
    
    while(l1!=NULL && l2!=NULL){
      
      if(l1->val <= l2->val){
        prev->next = l1;
        l1 = l1->next;
      }
      else{
        prev->next = l2;
        l2 = l2->next;
      }
      prev = prev->next;
    }
    
    if(l1 == NULL)
      prev->next = l2;
    else
      prev->next = l1;
    
    return prehead.next;
  }
};


// Recursive Solution
// TC: O(n+m)
// SC: O(n+m)
class Solution {
public:
  ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
      
    if(l1==NULL)
      return l2;
    if(l2==NULL)
      return l1;
    
    if(l1->val < l2->val) {
      l1->next = mergeTwoLists(l1->next,l2);
      return l1;
    }
    else {
      l2->next = mergeTwoLists(l1,l2->next);
      return l2;
    }
    return l1;
  }
};