/* 
Harshit Gupta | 18th October, 2018

C++ program for finding next greater element in an array.

https://ide.geeksforgeeks.org/3w3dWfvIXz
https://www.geeksforgeeks.org/next-greater-element/

Solution:   We will use Stack to solve this in O(n) time.
    * Iterate over all the elements of the array
    * While stack isn't empty and stack's top is less than the arr[i],
        then it means that arr[i] is the NGE of s.top()
    * Push arr[i] in the stack to find it's NGE.
*/

#include <bits/stdc++.h>
using namespace std; 

void nextGreaterElement(vector <int> arr){
    stack <int> s;
    
    // Iterate over all the elements in arr.
    for(int i=0;i<arr.size();i++){

        // While stack isn't empty and stack's top is less than the arr[i],
        // then it means that arr[i] is the NGE of s.top()
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
    // vector<int> arr = {13, 7, 6, 12};
    vector<int> arr = {11, 13, 21, 3};
    nextGreaterElement(arr);
    return 0;
}