/* 
Harshit Gupta | 18th October, 2018

C++ program for finding next greater element in an array.

https://ide.geeksforgeeks.org/3w3dWfvIXz
https://www.geeksforgeeks.org/next-greater-element/
https://leetcode.com/problems/next-greater-element-i/

Solution:   We will use Stack to solve this in O(n) time.
    * Iterate over all the elements of the array
    * While stack isn't empty and stack's top is less than the arr[i],
        then it means that arr[i] is the NGE of s.top(), so print it and pop() from the stack.
    * Push arr[i] in the stack to find it's NGE.
    * If some elements remains in the stack, they don't have a NGE.

Paradigm: Stack

Similar Questions:
    1. https://leetcode.com/problems/next-greater-element-ii/
        - Assume the given arr is a circular arr which means you could search circularly 
            to find its next greater number.
        - Elements can be duplicate so we will store the index of the elements
        - For elements that remain in the stack, iterate over the array and find the NGE
        - Check for other solution here: https://leetcode.com/problems/next-greater-element-ii/solution/

    2. https://leetcode.com/problems/next-greater-element-iii/
        - Find NGE with the same digits.
        - Yet to implement.

*/

#include <bits/stdc++.h>
using namespace std; 

void nextGreaterElement(vector <int> arr){
    stack <int> s;
    
    // Iterate over all the elements in arr.
    for(int i=0;i<arr.size();i++){

        // While stack isn't empty and stack's top is less than the arr[i],
        // then it means that arr[i] is the NGE of s.top()
        // THIS IS THE MOST IMPORTANT PART OF IT:
        //      1. while to be used and not IF
        //      2. Checking stack empty should be before the other cond.
        while(!s.empty() && arr[i]>s.top()){
            cout<<s.top()<<"-->"<<arr[i]<<endl;
            s.pop();
        }
        
        // Need to push this element irrespective of the fact that 
        // it was greater or less than s.top()
        s.push(arr[i]);
        
    }
    
    // Get the NGE of the remaining elements in the array
    while(!s.empty()){
        cout<<s.top()<<"-->-1"<<endl;
        s.pop();
    }
}

int main(){
    // vector<int> arr = {13, 7, 6, 12}; // 6->!2, 7->12, 13->-1, 12->-1
    vector<int> arr = {11, 13, 21, 3}; // 11->13, 13->21, 21->-1, 3->-1
    nextGreaterElement(arr);
    return 0;
}