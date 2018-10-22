/* 
Harshit Gupta | 22nd October, 2018

cpp.sh/2m7x4
https://www.geeksforgeeks.org/kth-largest-element-in-a-stream/

C++ program for finding the Kth largest number from a stream of numbers

Solution: We have implemented the solution using MinHeap. The k’th largest element is always at root and can be found in O(1) time.
    How to process a new element of stream?
        Compare the new element with root of heap. If new element is smaller, then ignore it. 
        Otherwise replace root with new element and call heapify for the root of modified heap. 
    
Time complexity of finding the k’th largest element is O(Logk).

Iteration:
    Size of heap is 3.
            (1 3 5)           3rd largest (1)
    7 came: 1 (3 5 7)         3rd largest (3) - bigger than the minheap's root.=> change
    2 came: 1 2 (3 5 7)       3rd largest (3) - lesser than the minheap's root.=> nochange
    0 came: 0 1 2 (3 5 7)     3rd largest (3) - lesser than the minheap's root.=> nochange
    9 came: 0 1 2 3 (5 7 9)   3rd largest (5) - bigger than the minheap's root.=> change
    .. when the element is smaller than the minHeap's root, then ignore. else add.

*/

#include <bits/stdc++.h>
using namespace std;


// Application of MinHeap
void heapify(int *heap, int k, int i){
    int left_child = 2*i+1;
    int right_child = 2*i+2;
    int smallest = i;
    
    // set smallest to the left child's index if that is smaller.
    if(heap[left_child] < heap[smallest] && left_child < k)
        smallest = left_child;
    
    // set smallest to the right child's index if that is smaller.
    if(heap[right_child] < heap[smallest] && right_child < k)
        smallest = right_child;
        
    // If parent is not smaller than the children, then we swap the parent and children.
    // heapify the rest of the affected child's subtree(left or right).
    if(smallest != i){
        swap(heap[smallest], heap[i]);
        heapify(heap, k, smallest);
    }
}

void insertIntoHeap(int *heap, int k, int n){
    // Setting the root node to 'n' so that it gets transported to its correct place with heapify() method.
    heap[0] = n;
    heapify(heap, k, 0);
    
    // Uncomment to view the heap.
    // for(int i=0;i<k;i++)
    //     cout<<heap[i]<<" ";
    // cout<<endl;
}

void KthLargestFromStream(int k){
    int heap[k];
    for(int i=0;i<k;i++)
        heap[i]=-1;
    int number_of_elements=-1;
    
    while(1){
        int n;
        cout<<"Enter the number in the stream: "<<endl;
        cin>>n;
        number_of_elements++;

        // If the number is greater than the root element(Kth largest element), then only insert it, else ignore it.
        if(n>heap[0]){
            insertIntoHeap(heap, k, n);
        }

        if(number_of_elements+1>=k){
            cout<<"Kth largest number in stream is: "<<heap[0]<<endl<<endl;
        }
        else{
            cout<<"Too soon to get kth largest number."<<endl<<endl;
        }
        
    }
}

int main() {
    int k;
    cout<<"Enter the value of K"<<endl;
    cin>>k;
    KthLargestFromStream(k);
    
	return 0;
}