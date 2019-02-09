/* 
Harshit Gupta | 31st October, 2018

http://cpp.sh/8npdt
https://www.geeksforgeeks.org/reverse-a-linked-list/

C++ program for inserting(front,end) an element, searching an element, and deleting (key,index) in a Linked List.
    Reverse a LL.

Solution: 
    To add new element to the front, point new node to the head's node. 
        Then make head point to the new node.
    To add new element to the end, keep traversing till current->next is NULL 
        and then add the node at the end.
    To search an element, keep traversing till current->next is NULL 
        and check for the elements.
    To delete an element at index n, keep traversing till you reach the index
        and then prev->next = current->next
    To delete an element with key 'k', keep traversing till you find the element,
        and then prev->next = current->next

NOTE: We need to handle the cases of 1st node deletion separately.

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
    cout<<"Added the node with data: "<<data<<" in the end."<<endl;
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
    cout<<"Added the node with data: "<<data<<" in the front."<<endl;
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

void deleteNodeOnIndex(node **head, int index){
    int fixed_index = index;
    node *current = *head;
    node *prev = *head;
    
    // Handle deleting the 1st node separately.
    if(index == 0){
        cout<<"Deleted element: "<<(*head)->data<<" at index: "<<fixed_index<<endl;
        (*head) = (*head)->next;
    }
    else{
        // Keep moving closer towards the index keeping the prev and current pointers
        while(index--){
            prev = current;
            current = current->next;
            
            // If at any point of time, current is NULL, 
            // then it means the index specified is more than the length of the LL.
            if(current==NULL){
                cout<<"Couldn't delete!! Please specify an index within the range"<<endl;
                return;
            }
        }
        cout<<"Deleted element: "<<prev->next->data<<" at index: "<<fixed_index<<endl;
        
        // This statement actually deletes the node.
        prev->next = current->next;
    }
}


void deleteNodeWithKey(node **head, int key){
    node *current = (*head);
    node *prev = (*head);
    
    // Keep traversing till we reach the end
    while(current->next!=NULL){
        
        // If the key is found
        if(current->data == key){
            
            // if the key is in the first index, then deal with the head.
            if(current == (*head)){
                (*head) = (*head)->next;
            }
            
            // else, the delete the key.
            else{
                prev->next = current->next;
            }
            cout<<"Deleted node with key: "<<key<<endl;
            return;
        }
        
        // Keep moving forward..
        else{
            prev = current;
            current = current->next;
        }
    }
    
    // If we reached the end, and couldn't find the element, then it doesn't exist.
    if(current->next==NULL){
        cout<<"Key "<<key<<" not found in the Linked List"<<endl;
    }
}

void reverseLL(node **head){
    // We need three pointers to reverse a LL namely: previous, current and following.
    node *previous = NULL; // This will store the previous node. By default it should be one behind the current node.
    node *current = (*head); // This will store the current node.
    node *following = (*head); // This will store the next node.

    // Till my current node becomes NULL, I got to keep reversing the arrows.
    while((current) != NULL){

        // Store the address of the actual next node in the 'following' variable 
        // since we will change the actual next and make it point to the previous node.
        following = current->next;
        
        // Reverse the arrow from front to behind. Make it point to the previous node.
        current->next = previous;

        // Move the previous to current since the operation on previous node is done.
        previous = current;

        // Thank God we stored the next node in the 'following' variable. 
        // I know how to move the current variable forward now by making it point to current.
        current = following;
    }

    // After the current points to NULL, we know the list is over. All we have to do is make head point to the
    // last node. The last node is pointed by prev since current becomes NULL and previous is the node before
    // it.. which should be the last node.
    (*head) = previous;
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
    
    cout<<"----------------------"<<endl;
    
    insertNodeInTheEnd(&head, 10);
    insertNodeInTheEnd(&head, 20);
    insertNodeInTheEnd(&head, 30);
    printLL(&head);
    
    cout<<"----------------------"<<endl;
    
    insertNodeInTheFront(&head, 5);
    insertNodeInTheFront(&head, 2);
    printLL(&head);
    
    cout<<"----------------------"<<endl;
    
    searchElementInLL(&head, 20);
    searchElementInLL(&head, 5);
    
    cout<<"----------------------"<<endl;
    
    deleteNodeOnIndex(&head, 0);
    printLL(&head);
    deleteNodeWithKey(&head, 10);
    printLL(&head);
    deleteNodeWithKey(&head, 29);
    printLL(&head);
    
    cout<<"----------------------"<<endl;

    reverseLL(&head);
    printLL(&head);

    // OUTPUT:

    // No LL found with head!
    // Linked List is Empty, couldn't find an element!
    // ----------------------
    // Added the node with data: 10 in the end.
    // Added the node with data: 20 in the end.
    // Added the node with data: 30 in the end.
    // HEAD->10->20->30->NULL
    // ----------------------
    // Added the node with data: 5 in the front.
    // Added the node with data: 2 in the front.
    // HEAD->2->5->10->20->30->NULL
    // ----------------------
    // Found 20 at index: 4
    // Found 5 at index: 2
    // ----------------------
    // Deleted element: 2 at index: 0
    // HEAD->5->10->20->30->NULL
    // Deleted node with key: 10
    // HEAD->5->20->30->NULL
    // Key 29 not found in the Linked List
    // HEAD->5->20->30->NULL
    // ----------------------
    
    return 0; 
} 
