/* 
Harshit Gupta | 19th October, 2018

C++ program for detecting and removing a loop in a linked list

https://ide.geeksforgeeks.org/3uQAwagHxo
https://www.geeksforgeeks.org/detect-loop-in-a-linked-list/
https://www.geeksforgeeks.org/detect-and-remove-loop-in-a-linked-list/

Solution: * To detect a loop, we take two pointers: a fast and a slower one, 
    the fast moves 2 nodes a time and the slower one moves one node a time.
    If they meet, we have a loop, else not.
    * To remove the loop, we will have to reach the last node of the loop and make it point to NULL.
        - Find the number of nodes in the loop.
        - Take a pointer at head and another at a dist of 'k' from head.
        - Move both one node a time and they will meet at the starting node of loop.
        - Get to the ending node of the loop from there.
        - Make it NULL.

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
    int data;
    struct node* next;
    node(int data){
        this->data = data;
        this->next = next;
    }
};

typedef struct node node;

void removeLoop(node *loop_node, node *head){
    node *ptr1 = loop_node;
    node *ptr2 = loop_node;
    int length_of_loop = 1;
    
    // Get the number of nodes in the loop
    while(ptr2->next!=ptr1){
        ptr2 = ptr2->next;
        length_of_loop++;
    }
    
    ptr1 = head;
    ptr2 = head;
    // Keep one pointer at head and move another at 'length_of_loop'th node.
    while(length_of_loop--){
        ptr2 = ptr2->next;
    }
    
    // Move both one node at a time till they meet at the starting index of the loop.
    while(ptr1!=ptr2){
        ptr1 = ptr1->next;
        ptr2 = ptr2->next;
    }
    
    // Get to the last node of the loop.
    while(ptr2->next!=ptr1){
        ptr2 = ptr2->next;
    }
    
    // Make the last index of the loop as NULL.
    ptr2->next = NULL;
    
}

void detectLoopInALinkedList(node *head){
    node *slow = head;
    node *fast = head->next;
    
    // Move both the pointers till they either become same(loop) or fast reaches NULL(no loop).
    while(slow!=fast && fast!=NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    if(fast==NULL){
        cout<<"No loop found"<<endl;
    }
    else{
        cout<<"Loop found. Removing it!"<<endl;
        removeLoop(slow,head);
    }
}

void printLinkedList(node *head){
    while(head!=NULL){
        cout<<head->data<<" ";
        head = head->next;
    }
}

int main(){
    node *head= new node(10);
    head->next = new node(20);
    head->next->next = new node(30);
    head->next->next->next = new node(40);
    head->next->next->next->next = new node(50);
    head->next->next->next->next->next = head->next;
    
    detectLoopInALinkedList(head);
    printLinkedList(head);
    return 0;
}