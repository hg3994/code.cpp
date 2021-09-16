/*

Harshit Gupta | 21st September, 2020
-------------------------------------

Program for "Add two numbers (in LL) to create another LL having its sum"
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

https://leetcode.com/problems/add-two-numbers/

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
------
Explanation: 342 + 465 = 807.

Solution: 

  We calculate the numbers in the given Linked lists with help of recursion. 
  The numbers are stored in reverse order and so we can use the position of node(level) to create the number.
  We have the level of each node and then we multiply the number in node with 10^level to get the actual number.
    2 -> 4 -> 3
    2*(0^10) + 4*(1^10) + 3 (2^10)
    2 + 40 + 300
    342

  We just have to create a new List with the number as SUM of two numbers in reverse order.
  - We will do num%10 to get the unit digit and then create a node.
  - We will get the remaining number by removing the unit digit and then dividing the number by 10 (num = num - num%10 ; num = num / 10)
  - We do the same thing with the remaining number.
    807
    7 + 00 + 800
    7*(0^10) + 0*(1^10) + 8*(2^10)

  We keep maintaining the list through recursion and then finally send it to main()

https://repl.it/repls/PoisedVisibleApplicationpackage#main.rb

#Agoda

*/

// # --------------------------------------
// # // SOLUTION IN C++
// # --------------------------------------

// carry will never be > 1 since at max 9+9 = 18 which is 1 carry.
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* c1=l1;
        ListNode* c2=l2;
        ListNode* l3head = new ListNode(0); //create this fake node 0 and in the end return l3head->next;
        ListNode* c3 = l3head;
        int carry = 0;
        while(c1!= NULL || c2!=NULL){
            int x = (c1 != NULL) ? c1->val : 0;
            int y = (c2 != NULL) ? c2->val : 0;
            int sum = (x+y+carry)%10;
            carry = (x+y+carry)/10;
            c3->next = new ListNode(sum);
            c3 = c3->next;
            if (c1!=NULL) 
                c1 = c1->next;
            if (c2!=NULL)
                c2 = c2->next;
        }
        if(carry > 0)
            c3->next = new ListNode(carry);
        return l3head->next;
    }
};
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */