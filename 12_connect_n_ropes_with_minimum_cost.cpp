/* 
Harshit Gupta | 19th October, 2018

C++ program for "There are given n ropes of different lengths, 
                we need to connect these ropes into one rope. 
                The cost to connect two ropes is equal to sum of their lengths. 
                We need to connect the ropes with minimum cost."

Solution:   On trying out a few examples (read GFG) and thinking we see that 
    we get the best solution with Greedy Approach. 
    If we select the minimum two elements and add them, 
    then in this way we get the smallest number add up multiple times. 
    If we select any other number, then a larger number is getting selected 
    and added multiple times. This is the insight for this problem.

Implementation: This is the best and finest example for implementation of priority_queues.
        * We use a priority_queue to keep the elements sorted in increasing order.
        * Take the two minimum elements and pop them. But add the sum of these two 
            till we are left with just one node. This node will contain the min cost.

http://www.cplusplus.com/reference/queue/priority_queue/priority_queue/
http://www.cplusplus.com/reference/algorithm/make_heap/
http://www.cplusplus.com/reference/algorithm/push_heap/
http://www.cplusplus.com/reference/algorithm/pop_heap/

*/

#include <bits/stdc++.h>
using namespace std; 

int getMinimumRopeCost(vector<int> ropes){
    
    // Making one priority queue(MIN HEAP). We could also have used make_heap on the ropes vector.
    // Notice that "greater" is used, by default it is "less"
    priority_queue<int, vector<int>, greater<int> > pq(ropes.begin(), ropes.end());
    
    // We will use this to store the result.
    int res = 0;
    
    // Loop till we reach only one node in a Heap.
    while(pq.size()>1){
        
        // get the two smallest elements.
        int first = pq.top();
        pq.pop();
        int second = pq.top();
        pq.pop();
        
        res += first+second;
        // Push the sum of two in the p.queue.
        pq.push(first+second);
    }
    return res;
}

int main(){
    vector<int> ropes = {4,3,2,6};
    int val = getMinimumRopeCost(ropes);
    cout<<val<<endl;
    return 0;
}