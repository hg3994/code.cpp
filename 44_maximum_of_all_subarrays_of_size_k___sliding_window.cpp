/* 
Harshit Gupta | 10th January, 2019

https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k/
https://stackoverflow.com/a/31061015
https://ide.geeksforgeeks.org/oJQvit2ylo

C++ program for "Given an array and an integer k, 
    find the maximum for each and every contiguous subarray of size k."

Solution: We will use Deque to solve this:

    The key is to maintain the max element at the top of the queue(for a window) 
    and discarding:
    * the elements that are out of index of current window.
    * the useless elements where useless elements = If Current element is greater 
        than the last element of queue than the last element of queue is useless. 

    1. If Current element is greater than the last element of queue than the last element 
        of queue is useless . We need to delete that last element. (and keep deleting 
        until Current element is greater than the last element).
    2. If if current_index - k >= q.front() that means we are going out of window 
        so we need to delete the element from front of queue. 


    // Elements:    [1,3,-1,-3,5,3,6,7]
    // Indexes:     [0,1, 2, 3,4,5,6,7]
    // The deque will be made of indexes but here for example, I am creating deque of nums[i]
    
    // i = 0 -> {1}                 => 
    // i = 1 -> {3}                 => 3>1 so we remove 1 and insert 3's index
    // i = 2 -> {3, -1}     => 3    => -1<3 so we insert its index at back
    // i = 3 -> {3, -1, -3} => 3    => -3<3 so we insert its index at back
    // i = 4 -> {5}         => 5    => 5>-3,-1,3 so we pop all of these out from back and insert index of 5
    // i = 5 -> {5,3}       => 5    => 3<5 so we insert its index at back
    // i = 6 -> {6}         => 6    => 6>3,5 so we pop both out and insert 6s index
    // i = 7 -> {7}         => 7    => 7>6 so we pop out 6 and insert index of 7
    

NOTE: We are storing the index in queue not the element itself because of condition 2 above. 
    How will we keep track if 20 has passed out from the current window or not? No right?
    But we can surely keep track if an index 3 has passed from the window or not. How?
        If our current element's index is 7 and window is 3, then we know that 7-3 is 4. 
        So, elements which have index lesser than 4, can be popped from the dequeue.
        WHY pop() from front in this case?
        >> If an element at index i-1 < index i , then it is automatically deleted by cond#1
            So an element at front has to be greatest and of lowest index
---

Another solution would be to use a priority queue(max Heap). 
Keep a window of K and keep it sorted. Keep inserting the arr[i] and popping out the element 
which are left. Keep showing the maxHeap[0] to get the largest of all subarrays. 
But this will take O(n*logK) time compared to O(n) using Dequeue.

There is another DP solution which doesnt require additional space, mentioned here: 
    https://leetcode.com/problems/sliding-window-maximum/solution/

---
Paradigm: Dequeue.

Time Complexity: O(n)

*/

#include <bits/stdc++.h>
using namespace std; 


void sliding_window_maximum_all_subarrays(vector<int> arr, int k){
    // Create a Double Ended Queue that will store indexes of array elements 
    // The queue will store indexes of useful elements in every window and it will 
    // maintain decreasing order of values from front to rear in Qi, i.e.,  
    // arr[Qi.front()] to arr[Qi.rear()] are sorted in decreasing order.
    // This is done so that the maximum of the window is avilable right at the front of the queue.
    deque<int> d;

    // Process first k (or first window) elements of array
    for(int i=0;i<k;i++){
        
        // If Current element is greater than the last element of queue than the last element 
        // of queue is useless . We need to delete that last element. (and keep deleting 
        // until the last element of queue is smaller than current element).
        while(!d.empty() && arr[i]>arr[d.back()])
            d.pop_back();
            
        // Add new element at rear of queue 
        d.push_back(i);
    }
    
    // Process rest of the elements, i.e., from arr[k] to arr[n-1]
    for(int i=k;i<arr.size();i++){
        
        // The element at the front of the queue is the largest element of 
        // previous window, so print it 
        cout<<arr[d.front()]<<" ";
        
        // If Current element is greater than the last element of queue than the last element 
        // of queue is useless . We need to delete that last element. (and keep deleting 
        // until the last element of queue is smaller than current element).
        while(!d.empty() && arr[i]>arr[d.back()])
            d.pop_back();
        
        // Remove the elements which are out of this window 
        while(!d.empty() && d.front() <= i-k)
            d.pop_front();
        
        // Add new element at rear of queue     
        d.push_back(i);
    }
    
    // Print the maximum element of last window
    cout<<arr[d.front()]<<endl;
}

int main() 
{
    vector<int> arr = {12, 1, 78, 90, 57, 89, 56};
    int window_size = 3;
    sliding_window_maximum_all_subarrays(arr, window_size);
    return 0; 
} 
