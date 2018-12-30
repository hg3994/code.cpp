/* 
Harshit Gupta | 18th November, 2018

https://ide.geeksforgeeks.org/jsT83OWEYa
https://www.geeksforgeeks.org/median-of-stream-of-running-integers-using-stl/
https://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/

C++ program for finding median in a running stream of integers.

Solution: 
    a.  Create two heaps. One max heap to maintain elements of lower half 
        and one min heap to maintain elements of higher half at any point of time.
    b.  Take initial value of median as 0.
    c.  For every newly read element, insert it into either max heap or min heap 
        and calulate the median based on the following conditions:
        - If the size of max heap is greater than size of min heap and the 
            element is less than previous median then pop the top element from 
            max heap and insert into min heap and insert the new element to max 
            heap else insert the new element to min heap. Calculate the new median 
            as average of top of elements of both max and min heap.
        - If the size of max heap is less than size of min heap and the element 
            is greater than previous median then pop the top element from min heap 
            and insert into max heap and insert the new element to min heap else 
            insert the new element to max heap. Calculate the new median as average 
            of top of elements of both max and min heap.
        - If the size of both heaps are same. Then check if current is less than 
            previous median or not. If the current element is less than previous 
            median then insert it to max heap and new median will be equal to top 
            element of max heap. If the current element is greater than previous 
            median then insert it to min heap and new median will be equal to top 
            element of min heap.

Paradigm: Priority Queues, Heaps.

Time Complexity: O(nlogn) to balance the heaps/heapify.

*/

#include <bits/stdc++.h>
using namespace std; 

void printMedians(double arr[], int n){
    
    // max heap to store the smaller half elements 
    priority_queue<double> s; 
  
    // min heap to store the greater half elements 
    priority_queue<double,vector<double>,greater<double> > g;
    
    // Insert the first element in the smaller heap and it would be the median for first element.
    double med = arr[0];
    s.push(arr[0]);
    
    cout<<med<<endl;
    
    // Calculating median after insertion of each elements from the stream
    for(int i=1;i<n;i++){
        
        // Case 1: Left side heap has more elements
        // Pushing an element would have EVEN number of elements in total, 
        // so median is average of top of min and max heaps
        
        // If the size of max heap(s) is greater than the min heap(g)
        if(s.size() > g.size()){
            // And the element is lesser than the median, then it has to be inserted in the max heap
            // But if directly inserted it will create imbalance in both heaps, 
            // so the maximum(top) of max heap(s) is moved to the min heap(g)
            // and then the element is inserted to the max heap.
            if(arr[i] < med){
                // Insert the top of max heap to min heap
                g.push(s.top());
                // Remove the top element of the max heap.
                s.pop();
                // Insert the new element in the min heap
                s.push(arr[i]);
            }
            // And the element is greater then the current median
            else{
                // Push it in the min heap. Now both heaps has equal elements.
                g.push(arr[i]);
            }
            
            // Update the median
            med = (s.top() + g.top())/ 2.0;
        }
        
        // Case 2: Right side heap has more elements.
        // Pushing an element would have EVEN number of elements in total, 
        // so median is average of top of min and max heaps
        
        // If the size of max heap(s) is lesser than the min heap(g). 
        else if(s.size() < g.size()){
            // And the element is less than the current median
            if(arr[i] < med){
                // Push it in the max heap. Now both heaps has equal elements.
                s.push(arr[i]);
            }
            
            // And the element is greater than the median, then it has to be inserted in the min heap
            // But if directly inserted it will create imbalance in both heaps, 
            // so the minimum(top) of min heap(g) is moved to the max heap(s)
            // and then the element is inserted to the min heap.
            else{
                // Insert the top of min heap to the max heap.
                s.push(g.top());
                // Remove the top element of min heap since it is already inserted in the max heap
                g.pop();
                // Insert the new element in the max heap.
                g.push(arr[i]);
            }
            
            // Update the median
            med = (s.top() + g.top())/ 2.0;
        }
        
        
        // Case 3: Both heaps have equal elements and are balanced.
        // If both the heaps has equal elements, then inserting this element 
        // would make the heaps have 'ODD' number of elements and thus the median now
        // would be only one number and not average of two numbers.
        else{
            // If the element is less than the current median, it is inserted in the max heap
            // and now since max heap has more elements, the top of max heap would be the median.
            if(arr[i] < med){
                s.push(arr[i]);
                med = (double)s.top();
            }
            
            // If the element is greater than the current median, it is inserted in the min heap
            // and now since min heap has more elements, the top of min heap would be the median.
            else{
                g.push(arr[i]);
                med = (double)g.top();
            }
        }
        
        // After all this, print the median after the ith number of the stream.
        cout<<med<<endl;
    }
}

int main() 
{ 
    // stream of integers 
    double arr[] = {5, 3, 15, 10, 20, 3}; 
    int n = sizeof(arr)/sizeof(arr[0]); 
    printMedians(arr, n); 
    return 0; 
} 
