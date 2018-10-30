/* 
Harshit Gupta | 30th October, 2018

https://ide.geeksforgeeks.org/Eug4UrhF9c

C++ program for inserting(front,end) an element, 
    searching an element in a Linked List.

Solution: 
    To add new element to the front, point new node to the head's node. 
        Then make head point to the new node.
    To add new element to the end, keep traversing till current->next is NULL 
        and then add the node at the end.
    To search an element, keep traversing till current->next is NULL 
        and check for the elements.

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
    int data;
    struct node *next;
    node(int data){
        this->data = data;
        this->next = NULL;
    }
};

void insertNodeInTheEnd(node **head, int data){
    node *current = *head;
    
    // If head is NULL, then add a new node to the head.
    if(current==NULL){
        *head = new node(data);
    }
    
    // If head is not NULL, then trverse the element till the current's next is NULL
    // Add a new node in the current
    else{
        while(current->next!=NULL){
            current=current->next;
        }
        current->next = new node(data);
    }
}

void insertNodeInTheFront(node **head, int data){
    
    // If head is NULL, then add a new node to the head.
    if(*head==NULL){
        *head = new node(data);
    }
    
    else{
        // Make a new node
        node *temp = new node(data);
        
        // Assign the node's next to the value which head is pointing
        temp->next = (*head);
        
        // Point head towards the new node
        (*head) = temp;
    }
}

void searchElementInLL(node **head, int key){
    node *current = *head;
    
    // If node is NULL, then no element is present in the list.
    if(*head == NULL){
        cout<<"Linked List is Empty, couldn't find an element!"<<endl;
    }
    
    else{
        int i=1;
        
        // Keep searching the LL and if found, return the index.
        while(current->next!=NULL){
            if(current->data==key){
                cout<<"Found "<<key<<" at index: "<<i<<endl;
                return;
            }
            else{
                i++;
                current = current->next;
            }
        }
        cout<<"Couldn't find the element "<<key<<" in the Linked List"<<endl;
    }
}

void printLL(node **head){
    node *current = *head;
    if(current==NULL){
        cout<<"No LL found with head!"<<endl;
    }
    else{
        cout<<"HEAD->";
        while(current!=NULL){
            cout<<current->data<<"->";
            current=current->next;
        }
        cout<<"NULL"<<endl;
    }
}

int main() 
{
    node *head = NULL;
    printLL(&head);
    searchElementInLL(&head, 23);
    
    insertNodeInTheEnd(&head, 10);
    insertNodeInTheEnd(&head, 20);
    insertNodeInTheEnd(&head, 30);
    printLL(&head);
    
    insertNodeInTheFront(&head, 5);
    insertNodeInTheFront(&head, 2);
    printLL(&head);
    
    searchElementInLL(&head, 20);
    searchElementInLL(&head, 5);
    
    return 0; 
} 
