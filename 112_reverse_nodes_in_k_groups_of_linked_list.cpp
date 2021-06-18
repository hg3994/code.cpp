
/*

Harshit Gupta | 11th June, 2021
---------------------------------

C++ program for "Given a linked list, reverse the nodes of a linked list k at a time and return its modified list."
https://leetcode.com/problems/reverse-nodes-in-k-group/
------

Solution:     
             head-> 1->2 -> 3->4 -> 5 (k=2)
    Step#1:  head-> 2->1 -> 3->4 -> 5
    Step#2:  head-> 2->1 -> 4->3 -> 5

        1. Check if K nodes are present from the current node so that we can reverse them.
        2. Reverse the set of K nodes.
        3. After reversing each set, we have to do two more things:
             b. Connect THIS reversed set to the following node (1->3 in step#1, 3->5 in step#2)
                 This is done in the reverseKNodes() with the line (firstCurrent->next = nextNode)
             a. Connect the prev reversed set's last node to THIS reversed set (head->2 in step #1, 1->4 in step#2)
                 This is done in the reverseKGroup() with the line (lastNodeInPrevKNodeSet->next = newCurrentNode)

        We need both lastNodeInPrevKNodeSet, lastNodeInThisKNodeSet and current
        current:     This node should always point to the first node in the set which is going to be reversed so we can call reverseKNodes()
        lastNodeInThisKNodeSet: After reverseKNodes(), this node will become the last node of THIS reversed set of nodes
        lastNodeInPrevKNodeSet: This node should always point to the last node of the old reversed set of nodes so that we can connect 
                                it to the first node of the new reversed set              


Time Complexity: O(n)
Space Complexity: O(1)

Paradigm: LinkedList, Iterative
---
  NOTE: 

*/ 


class Solution {
public:
    
    // This returns true if there are K nodes available ahead of the current node, false otherwise
    bool checkForKNodesAhead(ListNode* current, int k) {
        while(k-- && current!=NULL)
            current = current->next;
        if(current == NULL)
            return false;
        else
            return true;
    }
    
    // Reverses the K nodes and return the pointer to the last node
    ListNode* reverseKNodes(ListNode* current, int k) {
        ListNode* firstCurrent = current;
        ListNode* nextNode = current->next;
        ListNode* nextNextNode;
        
        // Till we reach the Kth node, keep reversing ...
        while(k--){
            nextNextNode = nextNode->next;  // Save the nextnextNode address since while we reverse the direction, we would lose it.
            nextNode->next = current;       // Reverse the arrow
            current = nextNode;             // Move current ahead
            nextNode = nextNextNode;        // Move next Node ahead
        }
        
        // Connecting the firstCurrent(initial current) node to the nextNode which is basically connecting the first node (which is last now) to the rest of the list
        // After reversing 1->2->3->... to 3->2->1->... basically we are connecting 1->... rest of the list
        // We have to do this now because if we exit this function, nextNode will be lost and we wont ever get it
        firstCurrent->next = nextNode;
        
        // At this point, after reversal, current is the Kth node which should be connected with the previous part of the list
        return current;
    }
    
    ListNode* reverseKGroup(ListNode* head, int k) {
        // If no node OR 1 node OR k=1 return NULL
        if (head == NULL || head->next == NULL || k==1)
            return head;
        
        ListNode* current = head;
        ListNode* lastNodeInPrevKNodeSet = head;
        
        // Keep checking if we have K-1 nodes (Kth one is the current which is already there) ahead of us, to be reversed
        while(checkForKNodesAhead(current, k-1)){
            
            // Save the current pointer since we will lose current after reversing, this will be the lastNode since after reversal first node would become the last node
            ListNode* lastNodeInThisKNodeSet = current;    
            ListNode* newCurrentNode = reverseKNodes(current, k-1); // Get the new current pointer

            // Fix the head once and then for other iterations, connect the lastNode of previous reversed K set to the first of this reversed K set
            if(lastNodeInPrevKNodeSet == head)
                head = newCurrentNode;
            else
                lastNodeInPrevKNodeSet->next = newCurrentNode;
            
            lastNodeInPrevKNodeSet = lastNodeInThisKNodeSet;
            current = lastNodeInThisKNodeSet->next;
            // Updating current to point to the first node of the new set which will be reversed (Remember in the reverseKNodes func, the this was already fixed)
        }
        return head;
    }
};