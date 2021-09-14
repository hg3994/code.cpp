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
        - Iterate twice for circular array
        - Check for other solution here: https://leetcode.com/problems/next-greater-element-ii/solution/

    2. https://leetcode.com/problems/next-greater-element-iii/
        - Find NGE with the same digits.
        - Did it in nextpermutation problem.

    3. https://leetcode.com/problems/number-of-visible-people-in-a-queue/
        - Read the question below

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
    // vector<int> arr = {13, 7, 6, 12}; // 6->12, 7->12, 13->-1, 12->-1
    vector<int> arr = {11, 13, 21, 3}; // 11->13, 13->21, 21->-1, 3->-1
    nextGreaterElement(arr);
    return 0;
}


// -------------------
// SIMILAR QUESTION -1
// -------------------

vector<int> nextGreaterElements(vector<int>& A) {
    int n = A.size();
    vector<int> stack, res(n, -1);
    for (int i = 0; i < n * 2; ++i) {
        while (stack.size() && A[stack.back()] < A[i % n]) {
            res[stack.back()] = A[i % n];
            stack.pop_back();
        }
        stack.push_back(i % n);
    }
    return res;
}

// -------------------
// SIMILAR QUESTION -3
// -------------------
// There are n people standing in a queue, and they numbered from 0 to n - 1 in left to right order. You are given an array heights 
// of distinct integers where heights[i] represents the height of the ith person.

// A person can see another person to their right in the queue if everybody in between is shorter than both of them. More formally, 
// the ith person can see the jth person if i < j and min(heights[i], heights[j]) > max(heights[i+1], heights[i+2], ..., heights[j-1]).

// Return an array answer of length n where answer[i] is the number of people the ith person can see to their right in the queue.


// Here we need to calculate the number of elements in right which are < than my own height
// So basically its not the NGE but the distance from i till the NGE
// Another twist is there may be elements which are lesser than me but I can't see them, check Example's 1st explanation below
// Hence, we insert indices in stack and not the element.

// Input: heights = [10,6,8,5,11,9]
// Output: [3,1,2,1,1,0]
// Explanation:
//      Person 0 can see person 1, 2, and 4. (THIS IS IMPORTANT, THE ANSWER IS NOT 4 but 3 since he wont be able to see person 3)
//      Person 1 can see person 2.
//      Person 2 can see person 3 and 4.
//      Person 3 can see person 4.
//      Person 4 can see person 5.
//      Person 5 can see no one since nobody is to the right of them.

//                      [10,6,8,5,11,9]
// [10,6,8,5,11,9],     [ 0,0,0,0, 0,0]
// stack: [10]          [ 0,0,0,0, 0,0]
// stack: [10,6]        [ 1,0,0,0, 0,0]
// stack: [10,8]        [ 2,1,0,0, 0,0]
// stack: [10,8,5]      [ 2,1,1,0, 0,0]
// stack: [11]          [ 3,1,2,1, 0,0]
// stack: [11,9]        [ 3,1,2,1, 1,0]


// Approach 1: Using a stack
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& A) {
        int n= A.size();
        vector<int> res(n);
        stack<int> stack;
        
        // At all point of time, we keep updating the impact of this arr[i] onto others.
        // If it is lesser than the stack top, insert it in stack & add 1 to the prev stack top 
        //      since it can see this element
        // If it is greater than or equal to the stack top, then this is the last it 
        //      can see so add 1 to stack top and pop it out.

        for(int i=0; i<A.size(); i++){
            // This means that the new element is > than the stack top height so we add 1 to the height of the stack top 
            // since it can see the element A[i] only and nothing ahead of it. This is the Next greater element for it
            // We pop it out since there's nothing more it can see, whatever it saw+1 for this element.
            while(!stack.empty() && A[i] >= A[stack.top()]){
                res[stack.top()]++;
                stack.pop();
            }
            
            // This means that whatever the stack top is can see A[i] since A[i] is < than the height of stack top
            // So we increase the height of stack top
            if(!stack.empty()){
                res[stack.top()]++;
            }
            
            stack.push(i);
        }
        return res;
    }
};


// Approach 2: Using a vector as a stack
class Solution {
public:
    vector<int> canSeePersonsCount(vector<int>& A) {
        int n= A.size();
        vector<int> stack, res(n);
        
        for(int i=0; i<A.size(); i++){
            while(!stack.empty() && A[stack.back()] <= A[i]){
                res[stack.back()]++;
                stack.pop_back();
            }
            
            if(!stack.empty()){
                res[stack.back()]++;
            }
            
            stack.push_back(i);
        }
        return res;
    }
};