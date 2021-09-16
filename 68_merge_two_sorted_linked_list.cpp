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

        1. For itertive solution:
          Time Complexity: O(n+m)
          Space Complexity: O(1)

        2. For recursive solution:
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
  
    // We are doing this inplace just by moving and updating the pointers without any extra space.
    // prehead is a new node which we take and then we keep making it point to the right node from
    //      either of the linked lists & move their pointers(l1/l2) one ahead.
    // l1 & l2 will keep pointing to the next nodes in the LL (init they point to the head)

    // Init:
    // 1->3->6
    // 2->4->5

    // Result:
    //      1   3      6
    // -1 -/ \ / \    /
    //        2   4->5

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

//  L1  , L2
// 1->3 , 2->4 | merge(1,2)
// 1->3 , 2->4 | 1<2,   1-> = merge(3,2)
// 1->3 , 2->4 | 3>2,      2-> = merge(3,4)
// 1->3 , 2->4 | 3<4,          3-> = merge(NULL,4)
// 1->3 , 2->4 | return        3->4
// 1->3 , 2->4 | return    2->3->4
// 1->3 , 2->4 | return 1->2->3->4
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
    }
};

