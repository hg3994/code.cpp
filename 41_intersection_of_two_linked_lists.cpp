/* 
Harshit Gupta | 9th January, 2018


C++ program for getting intersection point of two linked list.

Solution: We will find the difference in the length of the two linked lists. 
    Then, we traverse the difference number of nodes in the larger list.
    Then, we take two pointers and traverse both the lists from 
        larger one from the difference'th node.
        smaller one from the head
    Both the pointers will meet at the intersection point of two linked list.
    
NOTE: This solution is valid only if there is an intersection of both the lists.

Paradigm: Linked Lists

Time Complexity: O(n+m)
Space Complexity: O(1)

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

typedef struct node node;

int countNodesInAList(node *head){
    int count = 0;
    node *temp=head;
    while(temp!=NULL){
        count++;
        temp = temp->next;
    }
    return count;
}

node* findIntersectionOfLists(node *head1, node *head2){
    
    //Count the number of nodes in the both lists.
    int nodes_in_first = countNodesInAList(head1);
    int nodes_in_second = countNodesInAList(head2);
    
    // Declaring some variables.
    int greater_count, smaller_count, difference_count;
    node *greater_list_pointer, *smaller_list_pointer;
    
    // Get the node count of greater and smaller list.
    greater_count = nodes_in_first > nodes_in_second ? nodes_in_first: nodes_in_second;
    smaller_count = nodes_in_first < nodes_in_second ? nodes_in_first: nodes_in_second;
    difference_count = greater_count - smaller_count;
    
    // Set the greater_list_pointer and smaller_list_pointer to correct values.
    if(greater_count == nodes_in_first){
        greater_list_pointer = head1;
        smaller_list_pointer = head2;
    }
    else{
        greater_list_pointer = head2;
        smaller_list_pointer = head1;
    }
    
    // Traverse the greater list by "difference_count" number of nodes.
    while(difference_count--){
        greater_list_pointer = greater_list_pointer->next;
    }
    
    // Traverse both the lists by one step and both of them should meet at one node.
    // That node would be the intersection of both the lists.
    while(greater_list_pointer!=smaller_list_pointer){
        greater_list_pointer=greater_list_pointer->next;
        smaller_list_pointer=smaller_list_pointer->next;
    }

    return greater_list_pointer;
}

int main() 
{
    node *head1 = new node(10);
    head1->next = new node(20);
    head1->next->next = new node(30);
    head1->next->next->next = new node(40);
    head1->next->next->next->next = new node(50);
    
    node *head2 = new node(60);
    head2->next = new node(70);
    
    // intersecting both the linked lists at 40.
    // 10->20->30->40->50
    //             ↑
    //      60->70-↑
    
    head2->next->next = head1->next->next->next;
    
    node* intersecting_node = findIntersectionOfLists(head1, head2);
    cout<<intersecting_node->data<<endl;
    
    return 0; 
} 
