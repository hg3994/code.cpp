/* 
Harshit Gupta | 18th October, 2018

C++ program for adding two numbers in a L.L and show the result in another L.L.

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


node *newnode(int key) 
{ 
    node *temp = (node*)malloc(sizeof(node)); 
    temp->data = key; 
    temp->next = NULL; 
    return temp; 
}

void printLinkedList(node *root){
    while(root!=NULL){
        cout<<root->data<<" ";
        root = root->next;
    }
    cout<<endl;
}

void addNodeInFront(node **root, int r){
    node *n = newnode(r);
    if (root!=NULL){
        n->next = *root;
    }
    else{
        n->next = NULL;
    }
    (*root) = n;
}

int addNumbersInLL(node *root1, node *root2){
    node *current1 = root1;
    node *current2 = root2;
    int num1=0,num2=0,num3=0;
    
    while(current1!=NULL){
        num1 = (num1*10)+(current1->data);
        current1 = current1->next;
    }
    
    while(current2!=NULL){
        num2 = (num2*10)+(current2->data);
        current2 = current2->next;
    }
    
    num3 = num1+num2;
    return num3;
}

int main(){
    node *root1 = newnode(1);
    root1->next = newnode(2);
    root1->next->next = newnode(3);
    
    node *root2 = newnode(8);
    root2->next = newnode(6);
    root2->next->next = newnode(7);
    
    int sum = addNumbersInLL(root1, root2);

    node *root3=NULL;
    while(sum!=0){
        int r = sum%10;
        addNodeInFront(&root3, r);
        sum = sum/10;
    }
    printLinkedList(root1);
    printLinkedList(root2);
    printLinkedList(root3);
    
    return 0;
}