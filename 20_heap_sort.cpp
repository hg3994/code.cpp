/* 
Harshit Gupta | 21st October, 2018

https://ide.geeksforgeeks.org/5XQ0YmZYhp
https://www.geeksforgeeks.org/binary-heap/
https://www.geeksforgeeks.org/heap-sort/

C++ program for Heap Sort

Solution: We will use Heapification to help us do HeapSort. The solution is:
    - We make a maxHeap of the array and thus have the largest element at 0th index.
    - Then we move that index to the last and then make maxHeap of 1st n-1 elements.

Time Complexity: O(nlogn)

*/

#include <bits/stdc++.h>
using namespace std; 

void heapify(int *arr, int n, int i){
    // n is the number of elements to be considered for the list. \
        List will get short as array keeps on getting sorted and fixing the later values. \
        Present in this function, just to check if the childs' range \
        isn't getting out of bound (greater than n) and reaching the fixed part.
        
    // i is the starting node of the heapification process. \
        The affected nodes from i are the ones where we would \
        want to call heapify() recursively.
    // heapify is firstly called for making array a maxheap and there we stared with middle, so i is important \
        for the function. But, after it, when we actually sort, we always call heapify with 0.
    // Obviously, during the recursions, we would change this 'i' from 0 .. so this needed in the function.

    
    int left_child = 2*i+1;
    int right_child = 2*i+2;
    int largest = i;
    
    // set largest to the left child's index if that is greater.
    if(left_child<n && arr[left_child] > arr[largest]){
        largest = left_child;
    }
    
    // set largest to the right child's index if that is greater.
    if(right_child<n && arr[right_child] > arr[largest]){
        largest = right_child;
    }
    
    // If parent is not greater than the children, then we swap the parent and children
    // heapify the rest of the affected child's subtree(left or right)
    if(i!=largest){
        swap(arr[i], arr[largest]);
        heapify(arr,n,largest);
    }
    
}

void heapSort(int *arr, int n){
    
    // Heapify the array so that it becomes a maxHeap first.
    // NOTE that we are starting from the middle element, heapifying it and then moving towards the first element
    // This is done so that we get maximum element at first index and make a MAX HEAP.
    // We can't start from first index and then move towards middle since that won't result in the MAX HEAP (think about it)
    for(int i=(n/2)-1;i>=0;i--){
        heapify(arr,n,i);
    }
    
    // - Here the actual sorting happens.
    // - We move the first node of the maxHeap to the last one and 
    //   then call heapify on the rest on n-1 elements starting from the root index.
    // - So basically after getting a random node at the first index(after swapping), 
    //   we are going to place it in the right place. 
    // - We already know that the max Node would be one of the left 
    //   or the right child of the node which we moved to last, 
    //   so then random node compares with them and thus gets swapped 
    //   downstream to its perfect position in the maxHeap.
    // - Again we would have max at a[0] for the next loop and thus it continues..
    for(int i=n-1;i>=1;i--){

        // Swap the first and ith character since 0th number is the max.
        swap(arr[0], arr[i]);

        // Sending i here even if arr[i] is fixed, the reason is that in the 
        // heapify() function, <n is used and not <=n, so i is fine.
        heapify(arr,i,0);
    }
    
    // Print the vector
    for(int i=0;i<n;i++)
        cout<<arr[i]<<" ";
    cout<<endl;
}

int main(){
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr)/sizeof(arr[0]);
    heapSort(arr, n);
    return 0;
}