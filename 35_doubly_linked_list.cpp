/* 
Harshit Gupta | 10th November, 2018

https://ide.geeksforgeeks.org/LGAMkAEXIl
https://www.geeksforgeeks.org/doubly-linked-list/

C++ program for inserting, searching and deleting an element in a doubly linked list

Solution: 
    To insert new node in the end, traverse till the last node and then 
        make its next point to the newNode. Make newnode's prev point to the last node.
    To insert new node in the front, detect the 1st node and attach the new node.
    To insert a new node after the Nth node, traverse till the Nth node and then
        plug in the node between two nodes. current->next, current->next->prev would point 
        to the new node now. Similarly newnode->next and newnode->prev would point to the nodes.
    To search a node in the DLL, keep moving till we find the node.
    To delete an element with a Key, keep searching for the node with the key will the last.
        Take special consideration for first and last element.
    To delete an element at an index, keep moving forward at the index and delete the element.
        Take special consideration for first and last element.
        
Paradigm: Doubly Linked List

*/

#include <bits/stdc++.h>
using namespace std; 

struct node{
    int data;
    struct node *next;
    struct node *prev;
    
    node(int data){
        this->data = data;
        this->next = NULL;
        this->prev = NULL;
    }
};
typedef struct node node;

void deleteNodeWithKey(node **head, int key){
    node *current = *head;
    
    if(*head==NULL)
        return;
    
    // Check if the first node has the key.    
    if((*head)->data == key){
        (*head) = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
        cout<<"Deleted the node with the key: "<<key<<" from the DLL."<<endl;
    }
    else{
        
        // Keep traversing will the end of the list
        while(current!=NULL){
            
            // If the node with the key is found, delete it.
            if(current->data==key){
                
                // If it is the last node, then we won't consider fixing the prev index 
                // of the node preceeding the element since preceeding is NULL
                if(current->next!=NULL)
                    current->next->prev = current->prev;
                    
                // Delete the current node.
                current->prev->next = current->next;
                free(current);
                cout<<"Deleted the node with the key: "<<key<<" from the DLL."<<endl;
                return;
            }
            
            // Else keep on moving forward.. searching..
            else{
                current = current->next;
            }
        }
        cout<<"Couldn't find a node with the key: "<<key<<" in the DLL."<<endl;
    }
    
}

void deleteNodeWithIndex(node **head, int index){
    node *current = *head;
    int original_index = index;
    
    if(*head==NULL || index==0)
        return;
    
    // If the index is 1, then delete the node and make head point to the correct place.
    if(index==1){
        (*head) = (*head)->next;
        free((*head)->prev);
        (*head)->prev = NULL;
        cout<<"Deleted the node with at index: "<<original_index<<" from the DLL."<<endl;
    }
    
    else{
        
        // Move to the correct index
        while(--index && current!=NULL){
            current = current->next;
        }
        
        // If the index is greater than the length of the list, return.
        if(current==NULL){
            cout<<"Index "<<original_index<<" is greater than the length of the DLL. Ensure that the index is valid"<<endl;
            return;
        }
        
        // If it is the last node, then we won't consider fixing the prev index 
        // of the node preceeding the element since preceeding is NULL
        if(current->next!=NULL)
            current->next->prev = current->prev;
        
        // Delete the current node.
        current->prev->next = current->next;
        free(current);
        cout<<"Deleted the node with at index: "<<original_index<<" from the DLL."<<endl;
        return;
    }
}

// Passing the address of the head pointer since we may want the head to change.
void insertNodeAfterNthNode(node **head, int n, int data){
    node *newNode = new node(data);
    node *current = *head;
    
    // Deal with the case where n=0 since *head has to be changed here.
    if(n==0){
        
        // If there is no node then we only need to make head point to the new node.
        if(*head==NULL){
            (*head) = newNode;
        }
        
        // If there is a node pointed by head then we:
        //   Make the next pointer of newnode to the node pointed by head,
        //   Make the prev pointer of the node pointed by head point to the newNode,
        //   Make the head point to the new node.
        else{
            newNode->next = (*head);
            (*head)->prev = newNode;
            (*head) = newNode;
        }
    }
    
    // Deal with cases where n!=0 since head doesn't have to change.
    else{
        
        // Traverse till the value of n
            // --n since for n=1 we are already at the correct place so no need of traversal
            // The reason behind this is we are already at the 1st node,so pre decrement.
            // Also, if n is larger than the length of the list, then we can't do curr=curr->next.
        while(--n && current!=NULL){
            current = current->next;
        }

        // If n is larger than the length, return
        if(current==NULL){
            cout<<"Nth node doesn't exist in the DLL, so couldn't add the node. Please enter a valid N"<<endl;
            return;
        }
        
        // Point the prev pointer of the next node to the newNode.
        // This won't be done for the last node so do it only if (current->next!=NULL)
        if(current->next!=NULL)
            current->next->prev = newNode;
        
        // Set the next and prev pointers of the new node.
        newNode->next = current->next;
        newNode->prev = current;
        
        // Get the new node in the DLL.
        current->next = newNode;
    }
}

// Passing the address of the head pointer since we may want the head to change.
void insertNodeAtFront(node **head, int data){
    node *newNode = new node(data);
    
    // If DLL is empty, simply add the node
    if(*head==NULL){
        *head = newNode;
    }
    
    // Otherwise, detact the previous 1st node and attach this one.
    else{
        newNode->next = (*head);
        (*head)->prev = newNode;
        (*head) = newNode;
    }
    
}

// Passing the address of the head pointer since we may want the head to change.
void insertNodeAtEnd(node **head, int data){
    // We don't want to lose the head node while moving forward.
    node *current = *head;
    
    // Make a new node to join it in the end.
    node *newNode = new node(data);
    
    // If the head is NULL, then this is the first node.
    // We can't use current here since we want to change the head pointer here.
    if(*head == NULL){
        *head = newNode;
    }
    
    // This means, we already have a node in the DLL.
    // So, we will traverse with help of 'current' pointer till the last node(current->next==NULL)
    // Then append the new node in the its next pointer.
    // Also, make the new node's prev point to the last node.
    else{
        while((current)->next!=NULL){
            current = (current)->next;
        }
        (current)->next = newNode;
        newNode->prev = (current);
    }
}


void searchNodeInDLL(node *head, int key){
    int index = 1;
    
    // Till we reach the end of the DLL, keep moving
    while(head!=NULL){
        
        // If the data is found, return.
        if(head->data == key){
            cout<<"Node with key: "<<key<<" found at index: "<<index<<endl;
            return;
        }
        
        // If not found, move forward and increase the index.
        else{
            head = head->next;
            index++;
        }
    }
    cout<<"Node "<<key<<" not present in the DLL."<<endl;
    return;
}

// We passed head and not &head to this method since we don't want head to change.
// We just want to traverse the DLL in both directions.
void printDLL(node *head){
    node *current = head;
    node *previous;
    
    // Traversal
        cout<<"HEAD<->";
        while(current!=NULL){
            cout<<current->data<<"<->";
            previous = current;
            current = current->next;
        }
        cout<<"NULL"<<endl;
    
    // Reverse Traversal
        cout<<"NULL<->";
        while(previous!=NULL){
            cout<<previous->data<<"<->";
            previous = previous->prev;
        }
        cout<<"HEAD"<<endl;
    cout<<"-----------------------"<<endl;
}

int main() 
{
    node *head=NULL; // HEAD->NULL
    insertNodeAtFront(&head, 7); // HEAD<->7<->NULL
    insertNodeAtEnd(&head, 10); // HEAD<->7<->10<->NULL
    insertNodeAtEnd(&head, 20); // HEAD<->7<->10<->20<->NULL
    insertNodeAtEnd(&head, 30); // HEAD<->7<->10<->20<->30<->NULL
    printDLL(head);
    
    insertNodeAtFront(&head, 5); // HEAD<->5<->7<->10<->20<->30<->NULL
    insertNodeAtFront(&head, 2); // HEAD<->2<->5<->7<->10<->20<->30<->NULL
    printDLL(head);
    
    insertNodeAfterNthNode(&head, 0, 99); // HEAD<->99<->2<->5<->7<->10<->20<->30<->NULL
    insertNodeAfterNthNode(&head, 5, 90); // HEAD<->99<->2<->5<->7<->10<->90<->20<->30<->NULL
    printDLL(head);
    
    searchNodeInDLL(head, 30);
    searchNodeInDLL(head, 99);
    searchNodeInDLL(head, 7);
    searchNodeInDLL(head, 23);
    
    cout<<"-----------------------"<<endl;
    
    deleteNodeWithKey(&head, 99); // HEAD<->2<->5<->7<->10<->90<->20<->30<->NULL
    printDLL(head);
    deleteNodeWithKey(&head, 30); // HEAD<->2<->5<->7<->10<->90<->20<->NULL
    printDLL(head);
    deleteNodeWithKey(&head, 10); // HEAD<->2<->5<->7<->90<->20<->NULL
    printDLL(head);
    deleteNodeWithKey(&head, 23); // HEAD<->2<->5<->7<->90<->20<->NULL
    printDLL(head);
    
    deleteNodeWithIndex(&head, 1); // HEAD<->5<->7<->90<->20<->NULL
    printDLL(head);
    deleteNodeWithIndex(&head, 4); // HEAD<->5<->7<->90<->NULL
    printDLL(head);
    deleteNodeWithIndex(&head, 2); // HEAD<->5<->90<->NULL
    printDLL(head);
    deleteNodeWithIndex(&head, 8); // HEAD<->5<->90<->NULL
    printDLL(head);
    
    
    return 0; 
} 
