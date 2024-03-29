/* 
Harshit Gupta | 21st October, 2018

https://ide.geeksforgeeks.org/5XQ0YmZYhp
https://www.geeksforgeeks.org/binary-heap/
https://www.geeksforgeeks.org/heap-sort/
https://leetcode.com/problems/sort-an-array/

C++ program for Heap Sort

Solution: We will use Heapification to help us do HeapSort. The solution is:
    - We make a maxHeap of the array and thus have the largest element at 0th index.
    - Then we move that index to the last and then make maxHeap of 1st n-1 elements.

    What is a maxHeap?
    >> A complete Binary tree where all the parents are greater than their right and left child. This property is recursively true for all the nodes.
        Firstly, we want to sort the array into a max_heap which is done in the 1st loop of the heapSort function(). The loop starts from n/2-1 till 0 because 
        we know that all the elements after it would be the children of some parent nodes. There is no point in having the child nodes compared to nothing 
        and then just returning the function. This makes the initial array sorted by calling heapify(). This first heapify is to be done in bottom-up manner 
        and hence we have heapify(arr,n,i) and NOT heapify(arr,n,0).

    Now, we have a maxHeap to start with. In the second loop from n-1 to 0, we are fixing the elements towards the end and then starting to make a maxHeap 
        of the (n-1) elements remaining.

    Lets try to understand the heapify() function. What does it do? It converts your normal array into a maxHeap. heapify() takes the array, its size and 
        the root node as input. Now, how to make it a maxHeap? we have the root node given to the function. We can calculate its left child and right child. 
        Comparing these, we get the largest out of these three. If root is the largest out of all three, then we are sure that the current array is already 
        a maxHeap (because we have already made the array as maxHeap in the n/2-1 loop before). If, now, then lets say the left child is maximum, then we 
        swap root and left child to make it a maxHeap and then recursively check the left child's tree to ensure it is also a maxHeap.

    heapify(0 moves in speed of 2x and hence its complexity is log(n). The swapping of maxElement to the last one and fixing it happens in a loop of O(n). 
        These are nested and hence the complexity is O(nlogn).


Time Complexity: O(nlogn)
Space Complexity: O(1)

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
    // i: STARTING INDEX of HEAPIFICATION (for everything!), n: NUM OF ELEMENTS CONSIDERED FOR HEAPIFICATION (just for range check)
    for(int i=(n/2)-1;i>=0;i--)
        heapify(arr,n,i);
    
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
        // i: NUM OF ELEMENTS CONSIDERED FOR HEAPIFICATION (just for range check), 0: ALWAYS FROM THE STARTING INDEX
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