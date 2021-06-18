
/*

Harshit Gupta | 17th June, 2021
---------------------------------

C++ program for "Flatten a Multilevel Doubly Linked List"
https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

You are given a doubly linked list which in addition to the next and previous pointers, 
it could have a child pointer, which may or may not point to a separate doubly linked list. 
These child lists may have one or more children of their own, and so on, to produce a 
multilevel data structure, as shown in the example below.

Flatten the list so that all the nodes appear in a single-level, doubly linked list. 
You are given the head of the first level of the list.

Input: head = [1,2,null,3]
Output: [1,3,2]
Explanation:

The input multilevel linked list is as follows:

  1---2---NULL
  |
  3---NULL

------

Solution: Explained Below.

TC: O(N)
SC: O(N)

Paradigm: Recursion, Stack

---
  NOTE: 

*/


/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;
};
*/

// This can also be solved by Stack

class Solution {
    
    
Node* helper(Node* current){
    // Node to hold the previous to current pointer
    Node *pre;
    
    // Till current reaches NULL (after the end of the DLL), we keep looping
    // When this condition is met, prev would contain the last node.
    while(current != NULL){
        
        // If the child pointer is NULL, updated prev and just move ahead
        if(current->child == NULL){
            pre = current;
            current = current->next;
        }
        // If the child pointer is not null, we do:
        // - connect child's prev to current
        // - save the current's next because it will be lost when we connect current's next to current's child
        // - current next will not point to the child
        // - call the same function for the child node recursively so it does all this too. This should return the last node of the child's DLL
        // - after child traversal is done, we make current's child to be NULL
        // - the last node of the child must be connected to the saved_node's prev
        // - update pre and move current looking for the next node
        else{
            current->child->prev = current;
            Node* saved_next = current->next;
            current->next = current->child;
            Node* last_node = helper(current->child);
            current->child = NULL;
            last_node->next = saved_next;
            if(saved_next)
                saved_next->prev = last_node;
            pre = current;
            current = current->next;
        }
    }
    return pre;
}
    
public:
    Node* flatten(Node* head) {
        if(head== NULL)
            return head;
        Node* current = head;
        helper(current);
        // printLL(head);
        return head;
    }
};


   
// void printLL(Node* current){
//     Node* lastNode;
//     Node* headNode = current;
//     while(current != NULL){
//         cout<<current->val<<"->";
//         if(current->next == NULL)    
//             lastNode = current;
//         current = current->next;
//     }
//     cout<<"NULL"<<endl;
//     current = lastNode;
//     cout<<"NULL";
//     while(current != headNode){
//         cout<<"<-"<<current->val;
//         current = current->prev;
//     }
//     cout<<"<-HEAD"<<endl;
    
// }