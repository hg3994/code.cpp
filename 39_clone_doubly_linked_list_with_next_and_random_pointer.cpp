/* 
Harshit Gupta | 24th November, 2018

https://ide.geeksforgeeks.org/wmqcpaFPzD
https://www.geeksforgeeks.org/clone-linked-list-next-random-pointer-o1-space/
https://leetcode.com/problems/copy-list-with-random-pointer/

C++ program for cloning a doubly linked list with a next and random pointer

Solution: 
    a. Create the copy of node 1 and insert it between node 1 & node 2 in 
        original Linked List, create the copy of 2 and insert it between 2 & 3.. 
        Continue in this fashion, add the copy of N after the Nth node
    b. Now fix the random pointers of the duplicate nodes like this:
        original->next->random = original->random->next; (more detail in implementation)
        (This works because original->next is nothing but copy of original and 
         Original->random->next is nothing but copy of random.)
    c. Now restore the original and copy linked lists by detaching one from the other (fixing next pointers)
        original->next = original->next->next;
        copy->next = copy->next->next;
    d. Save the starting of the cloned list and iterate over it. All the random and next pointers
        are pointing correctly to the cloned list now. Both original and cloned are detached now.

Paradigm: Doubly Linked List

Time Complexity: O(n)

Space Complexity: O(1)

*/

#include <bits/stdc++.h>
using namespace std; 

// Structure of linked list Node 
struct Node { 
    int data; 
    Node *next,*random; 
    Node(int x) { 
        data = x; 
        next = random = NULL; 
    } 
}; 

void printDLL (Node *start){
    Node *current = start;
    cout<<"  HEAD -->";
    while(current!=NULL){
        cout<<" Node's Data: "<<current->data<<" Random's Data: "<<current->random->data<<" -->";
        current = current->next;
    }
    cout<<" NULL"<<endl;
}

Node *clone(Node *start){
    Node *current = start;
    Node *temp;
    
    // Insert additional node after every node of the DLL.
    while(current!=NULL){
        
        // Store the address of the next since it will get lost in the next step
        temp = current->next;
        
        // Add the additional duplicate node after the node
        // Also make the added node's next point to the node which was the next previously.
        current->next = new Node(current->data);
        current->next->next = temp;
        
        // Move two nodes ahead (since the additional node is added now)
        current = temp; // == current->next->next
    }
    
    // Get the current pointer to the starting point.
    current = start;
    
    // Fix the random pointers of the duplicate/added nodes.
    while(current!=NULL){
        
        // random of the duplicate nodes = nodes' random's next;
        // Why current->random->next and not current->random?
        //    because current->random will point to the original node and its next will point to another duplicate node.
        //    we want the duplicate node's random to point to the correct duplicate node (not the original node)
        if(current->random != NULL)
            current->next->random = current->random->next;
        
        // Move ahead two nodes.
        current = current->next->next;
    }
    
    // Now we want to adjust the next of nodes such that both original
    // and duplicates are detached and can be treated as clone of one another.
    // They should be traversible independently without depending on each other.
    // Currently, original's next -> duplicate node & duplicate's next -> original node
    
    // Get the starting point of both the nodes.
    Node *original = start;
    Node *copy = start->next;
    
    // We want to return the cloned list's start, so saving it.
    temp = copy; 
    
    // Make the original and cloned list separate.
    while(original!=NULL){
    
        // Make original's next point to its real next which is original->next->next
        // to detatch the duplicate node.
        original->next = original->next->next;
        
        // Make duplicate's next point to its real next which is copy->next->next to detatch the original node
        // Note that for last node the copy->next->next won't exist, so handled it separately.
        copy->next = copy->next?copy->next->next:copy->next;
        
        // move the original and copy two nodes at a time.
        original = original->next;
        copy = copy->next;
    }
    
    // Return the start to the cloned list (which is detached from original list now)
    return temp;
}

int main() 
{
    Node* start = new Node(1); 
    start->next = new Node(2); 
    start->next->next = new Node(3); 
    start->next->next->next = new Node(4); 
    start->next->next->next->next = new Node(5); 
    
    // 1's random points to 3 
    start->random = start->next->next; 
  
    // 2's random points to 1 
    start->next->random = start; 
  
    // 3's and 4's random points to 5 
    start->next->next->random = start->next->next->next->next; 
    start->next->next->next->random = start->next->next->next->next; 
  
    // 5's random points to 2 
    start->next->next->next->next->random = start->next; 
  
    // Where there is only one node with random pointing to itself
    // Node* start = new Node(1); 
    // start->random = start;
  
    cout << "Original list : \n"; 
    printDLL(start);
    
    cout << "Cloned list : \n"; 
    Node *cloned_list = clone(start); 
    printDLL(cloned_list);
    
    cout << "Original list after cloning: \n"; 
    printDLL(start);
    
    return 0; 
} 

// -----------------
// LEETCODE SOLUTION
// -----------------

/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    
    
    Node* copyRandomList(Node* head) {
        if(head == NULL)
            return NULL;
        
        // 1. start and insert duplicate nodes in between
        Node* current = head;
        Node* temp;
        while(current != NULL){
            temp = current->next;
            current->next = new Node(current->val);
            current->next->next = temp;
            
            current = temp;
        }
        
        // 2. Fix random pointers in added nodes
        current = head;
        while(current!= NULL){
            if(current->random != NULL)
                current->next->random = current->random->next;
            current = current->next->next;
        }
        
        // 3. Detach the original and copied nodes
        current = head;
        Node* clone_current = current->next;
        Node* copied_cloned_start = clone_current;
        while(current!=NULL){
            current->next = current->next->next;
            clone_current->next = clone_current->next ? clone_current->next->next : clone_current->next;
            current = current->next;
            clone_current = clone_current->next;
        }
        return copied_cloned_start;
    }
};

// void printDLL (Node *start){
//     Node *current = start;
//     cout<<"  HEAD -->";
//     while(current!=NULL) {
//         cout<<" Node's Data: "<<current->val; // " Random's Data: "<<current->random->val<<" -->";
//         current = current->next;
//     }
//     cout<<" NULL"<<endl;
// }