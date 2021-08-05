/* 
Harshit Gupta | 31st October, 2018

http://cpp.sh/6sdt3

C++ program for inserting(front,end) an element, searching an element, 
    and deleting (key,index) in a Linked List.


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
    To delete the n'th node from the last, we take two pointers i and j, move j ahead by 'n' nodes, then move both together till j reaches last node.
        and then i->next = i->next->next
    To reverse a Linked List, we can do it in two ways:
        - Iterative: Keep reversing the arrows one at a time and traverse till the end
        - Recursive: Traverse till the end and then while we backtrack, reverse the arrows

Similar Questions:
    1. https://leetcode.com/problems/reverse-linked-list/
    2. https://leetcode.com/problems/reverse-linked-list-ii/ : Reverse Nodes in between i and j index
    3. https://leetcode.com/problems/reverse-nodes-in-k-group/ : Reverse Nodes in K groups (Solved in 112_..)

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

void deleteNthFromEnd(node** head, int n) {
    struct node *i = *head;
    struct node *j = *head;
    int temp = n;
    
    // Traverse to the n'th node [1,2,3,4,5], and n=2, then j points to 3 (index 2)
    while(temp--)
      j = j->next;
    
    // Handle deleting the 1st node separately.
    // If j is at NULL, this means that n is the size of the list, we need to delete the first node.
    // We make head point to the 2nd node directly.
    if (j==NULL){
      *(head) = i->next; 
    }
    
    // If j is not NULL, this means we still need to find the last nth node.
    // We keep moving both the pointers ahead till j reaches the last node (j->next!= NULL)
    else{ 
        
      while(j->next!=NULL){
        j = j->next;
        i = i->next;
      }
    
      // When j reaches the last node, i reaches the last n+1 th node and we delete the nth node.
      // [1,2,3,4,5], n=2, i=0, j=2
      // [1,2,3,4,5], n=2, i=1, j=3
      // [1,2,3,4,5], n=2, i=2, j=4 (j->next=NULL)
      // [1,2,3,5], n=2, i=2, i->next = i->next->next
      i->next = i->next->next;
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
    
    deleteNthFromEnd(&head, 1);
    deleteNthFromEnd(&head, 2);
    printLL(&head);
    cout<<"----------------------"<<endl;
    return 0; 
} 



// -----------------------------------------
// REVERSE LINKED LIST IMPLEMENTATION BELOW:
// -----------------------------------------

class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        return reverseListIterative(head); // O(1) space.
        // return reverseListRecursive(head); // O(n) space.
    
    }
    
    // ITERATIVE
    ListNode* reverseListIterative(ListNode* head) {
        // If no node, return NULL
        if (head == NULL)
            return head;
        
        // Define the nodes needed 
        // we want to keep changing the current->nextNode direction to nextNode->current
        // Since we would lose the nextNode's next, we also want to store that, we use nextNextNode to store it before we lose it.
        ListNode* current = head;
        ListNode* nextNode = current->next;
        ListNode* nextNextNode;
        
        // The current node after reversal would point to NULL since this will be the last node.
        current->next = NULL;
        
        // Till we reach the last node(current would be last node)
        while(nextNode != NULL){
            nextNextNode = nextNode->next;  // Save the nextnextNode address since while we reverse the direction, we would lose it.
            nextNode->next = current;       // Reverse the arrow
            current = nextNode;             // Move current ahead
            nextNode = nextNextNode;        // Move next Node ahead
        }
        // Finally point head to the last node (which is 'current' now after the loop)
        head = current;
        
        return head;
    }
    
    // RECURSIVE
    ListNode* reverseListRecursive(ListNode* head) {
        // Make sure that the list is atleast 2 nodes
        if(head == NULL || head->next==NULL)
            return head;
        
        // Get the lastNode after traversing everything
        ListNode* lastNode = traverse(head, head->next);
        // head's next (first node of the old list) should be NULL. This has to be done here since if we do it before or after, then we lose the old LL's first node
        head->next = NULL;
        // make head point to the last node.
        head = lastNode;
        
        return head;
    }
    
    // Function to traverse the list till the end
    ListNode* traverse(ListNode* current, ListNode* nextNode){
        // If we reach the last node, current is one behind, we reverse the arrows/direction and return the last node since it has to be attached to the head
        if(nextNode->next == NULL){
            nextNode->next = current;
            return nextNode;
        }
        // Get the lastNode and keep returning it so that it reaches the main function.
        // Traverse the next set of nodes (basically move ahead in the list towards the end)
        ListNode* lastNode = traverse(nextNode, nextNode->next);
        // REVERSE THE DIRECTION (Most important)
        nextNode->next = current;
        
        return lastNode;
    }
};



// ------------------------------------------------------------------
// REVERSE LINKED LIST BETWEEN ith AND jth INDEX IMPLEMENTATION BELOW:
// ------------------------------------------------------------------
// Consider 1->2->3->4->5 as example, we need to reverse index 2 to 5
// Reversed List: 1->4->3->2->5

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if(head==NULL || right==left)
            return head;
        
        int count = right-left;     // Num of nodes to be reversed
        
        ListNode* current = head;   // This will the current node.
        
        // This node will always point to the node before the "reversed" set of nodes. 
        // This node is important because this has to be pointed to the last node after reversal
        // prev = 1 for the example considered.
        ListNode* prev = head;      
        
        // This node will point to the first current from where we start the reversal. 
        // We need this node because this node would be the last reversed node so we need to connect it with the nodes further
        ListNode* first_current = head;
        
        left--;
        while(left--){
            prev = current;
            current = current->next;
        }
        first_current = current;
        
        ListNode* nextNode = current->next;
        ListNode* nextNextNode;
        
        while(nextNode != NULL && count--){
            nextNextNode = nextNode->next;  // Save the nextnextNode address since while we reverse the direction, we would lose it.
            nextNode->next = current;       // Reverse the arrow
            current = nextNode;             // Move current ahead
            nextNode = nextNextNode;        // Move next Node ahead
        }
        
        // Now current would point to the last node which has been reversed
        // nextNode would point to the node ahead of it OR NULL if current if the last node (right == last node)
        // 2->3->4 has now been converted to 4->3->2, now we need to stich it into the list

        // We need first current node to point to the nextNode so that after reversal of nodes, we connect with the later part of the nodes 
        // (which are after the reversal part) to the first node (which after reversal became the last node)
        first_current->next = nextNode;            
        // 4->3->2->5
        
        // THIS IS VERY IMPORTANT AND TRICKY. THIS IS THE ONLY TRICK IN THIS PROBLEM
        // The issue is how do we identify if we have to update the head to current OR prev->next to current ??
        // For this, we check that if prev->next is already updated to the nextNode, then head->current
        // If not, then we know that there is a prev node whose next is to be assigned to the current node
        if (prev->next == nextNode){
            head = current;
        }
        else{
            prev->next = current;
        }
        // 1->4->3->2->5
        
        return head;
    }
};