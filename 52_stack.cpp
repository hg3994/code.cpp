/* 
Harshit Gupta | 9th February, 2019

https://ide.geeksforgeeks.org/PdKP0THUPx
https://www.geeksforgeeks.org/reverse-a-stack-using-recursion/

C++ program for reversing, sorting a stack.

Solution: 

Reverse a Stack using recursion
===============================
	We can recurse through popping items from the stack till we reach the empty stack and then push the 
	items back again. But, while pushing the items back again, we will ensure that the item that we are going to push
	needs to be at the bottom of the stack. If we ensure this for all the instances of recursion, our work is done.
	Why is it done? Because the instance of the top element will come at the last so tht is pushed at the 
	bottommost part. The instance which had the second top variable will come at the second last, so at that point
	it is pushed in the bottom most part, but the last one pushes its own variable after it at the bottom most
	and the variable of seconf top becomes second bottom. Similarly, this happens for all the instances .. and 
	if we have a deeper look, then this is what we want to achieve. Reversing a stack done. 

	Time Complexity: O(n2)
		reverse(n) = reverse(n-1) + insertAtBottom(nth Item)
			Now insert at bottom itself is O(n).
			To calculate reverse(n) you need to calculate reverse(1) to reverse(n-1).
			Therefore, total complexity is O(n^2).


Sort a Stack using recursion
============================
	We can recurse through popping items from the stack till we reach the empty stack and then push the 
	items back again. But, while pushing the items back again, we will ensure that the item that we are going to push
	needs to be pushed in the sorted order. If we ensure this for all the instances of recursion, our work is done.
	Why is it done? Because we are always pushing the element in its correct place and this is how at all point
	of time, we will have a sorted stack. Eventually, the later instances of recursions will get called first and 
	they will maintain a sorted stack till we get to the first instance of recursion, which will similarly place the
	element to its correct place. The sorting of the variables in the instances of recursion happens at the time of 
	insertion into the stack, so this is similar to insertion sort.

	Time Complexity: O(n2)
		sortStackRecursion(n) = sortStackRecursion(n-1) + pushInSortedOrder(nth Item)
			Now insert in sorted order itself is O(n).
			To calculate sortStackRecursion(n) you need to calculate sortStackRecursion(1) to sortStackRecursion(n-1).
			Therefore, total complexity is O(n^2).


Sort a Stack using a temporary stack
====================================	
	We iterate and keep on popping the elements from the stack and pushing the elements to the tempStack maintaining
	the tempStack in a sorted way. If we pop an element which is somewhere in between in the tempStack, then push
	it back to the original stack. (e.g., If we want to push 15 in a tempStack of [20,10], then we pop 20 
	and push it in the original stack). We push the popped item from the original stack only at its correct place.

	Complexity: O(n2)
		In every iteration, I am pushing something in the tempStack. Lets say my element was the last one and the
		element was the smallest, then I would have to push all the items of tempStack to the original stack.
		This is the worst case and this can happen with all the elements. For every element, I may have to pushback (n-1)
		elements back to the original stack and fix 1 element in the tempStack. This is the reason why the complexity 
		is O(n2)

Paradigm: Recursion, Stack

*/

#include <bits/stdc++.h>
using namespace std; 

// Global stack so that it is accessible to all the methods.
stack<int> s;

// This functions prints the stack in top to bottom manner
// CAUTION: whatever stack you pass to this function will be empty since everything is popped
void printStack(stack<int> dup){
  while(!dup.empty()){
    int w = dup.top();
    cout<<w<<" ";
    dup.pop();
  }
  cout<<endl;
}

// ---------------------------------
// SORT STACK WITH A TEMPORARY STACK
// ---------------------------------

// s1: [2,1,4,3] 	sortedSt: []
// s1: [2,1,4] 		sortedSt: [3]
// s1: [2,1]   		sortedSt: [3,4]
// s1: [2,4,3] 		sortedSt: [1]
// s1: [2,4] 		sortedSt: [1,3]
// s1: [2]   		sortedSt: [1,3,4]
// s1: [4,3]   		sortedSt: [1,2]
// s1: [4]   		sortedSt: [1,2,3]
// s1: []   		sortedSt: [1,2,3,4]
void sortStackUsingTemporaryStack(){
	
	stack<int> tempStack; // This stack would have the sorted values. (SORTED STACK)
	stack<int> s1 = s; // Duplicate since I want to preserve s

	// Till the stack is empty, we loop
	while(!s1.empty()){

		// Get the top element and pop it.
		int t = s1.top();
		s1.pop();

		// Iterate over the temp array to find the correct place of 't'. 
		// If we have incorrect values in the temp stack, (not sorted w.r.t to 't'), then
		// we push that value back to the original stack and pop it from the tempStack.
		while(!tempStack.empty() && tempStack.top() > t){
			s1.push(tempStack.top());
			tempStack.pop();
		}

		// Now we push the element 't' at its correct place in the tempStack.
		tempStack.push(t);
	}

	// Print the sorted tempStack.
	printStack(tempStack);

}

// --------------------
// SORT STACK RECURSION
// --------------------
void pushInSortedOrder(int t){
	// We want to move the element 't' to its correct place in the stack through this function.

	// If the stack is empty, then push the element anyway.
	if(s.empty()){
		s.push(t);
	}
	else{

		// Check if the top element is smaller than the element 't', 
		// then push it since the stack below is already sorted.
		if(s.top()<t){
			s.push(t);
		}
		else{
			// Pop the element and then call this recursively to find its correct place.
			int a = s.top();
			s.pop();
			pushInSortedOrder(t);

			// Push the popped element 'a' after the element 't' is added in its correct place.
			s.push(a);
		}
	}
}

void sortStackRecursion(){
	//  Till the stack is empty, we loop
	if(!s.empty()){

		// Get the top element and pop it.
		int t = s.top();
		s.pop();

		// Call it again so that all the elements get popped and then we push the elements one by one in sorted order.
		sortStackRecursion();

		// We will reach here first when we have the stack empty and from that point we will push it in a sorted way 
		// through this method.

		// Example: For all the instances of recursion, we will get a value 't' and this method will ensure that it is 
		// pushed to its correct place. At all point of time, we will have the stack sorted. E.g., Lets say the stack is
		// [40 30 20 10] and we want to insert 25, then it will pop 40 and 30. Then, push 25, then push 30 and 40 back
		// The resultant stack would look like: [40 30 25 20 10]
		pushInSortedOrder(t);
	}
}

// ---------------
// REVERSE A STACK
// ---------------

void pushAtBottom(int t){
	// Here, we want to pop whatever is already in the stack and move 't' to the bottommost part. then restore/push
	// everything back.

	// We keep on popping till stack is empty and if the stack is empty, then push the element 't', 
	// This is done because whatever be the stack, we want 't' to be at the bottommost part.
	if(s.empty()){
		s.push(t);
	}
	else{
		// Keep on popping the elements till we make it empty and then push 't'
		int a = s.top();
		s.pop();

		// Recursion which ensures that stack becomes empty at some point and I push 't'
		pushAtBottom(t);

		// Push the popped element 'a' since we have already pushed 't' at the bottommost part now.
		s.push(a);
	}
}

// Function to reverse the stack
void reverseStack(){

	// Till the stack is empty, we loop
	if(!s.empty()){

		// Get the top element and pop it.
		int t = s.top();
		s.pop();

		// Call it again so that all the elements get popped and then we insert the top element 't' at the bottom.
		reverseStack();

		// Inserting the element 't' at the bottom. If we ensure this happens in every instance of recursion, 
		// we know that the top element 't' is going to get inserted at the bottom of stack.
		// Since the top element of stack is called first, its recursion instance comes last and so it will be 
		// at the bottommost part of the stack. With me?

		// Example: in the given stack 40 is at top, so it is popped first but due to recursion, the that instance where
		// t is 40 comes at the last and so 40 is inserted at the 'last' in the bottommost part of stack.
		pushAtBottom(t);
	}
}




int main() 
{
	// stack s is defined globally.

	s.push(10);
	s.push(20);
	s.push(30);
	s.push(40);

	// Make a duplicate stack to print the stack present now.
	cout<<"Stack: "<<endl;
  stack<int> dup1 = s; printStack(dup1);

	reverseStack();

	cout<<"Reverse Stack: "<<endl;
	// Make a duplicate stack to print the stack present now.
	stack<int> dup2 = s; printStack(dup2);

	// ----------------------------------------------------------

	s.push(5);
	s.push(70);
	s.push(15);
	s.push(35);

	sortStackRecursion();
	
	cout<<"Sorted Stack: "<<endl;
	stack<int> dup3 = s; printStack(dup3);

	// ----------------------------------------------------------

	s.push(55);
	s.push(7);
	s.push(45);
	s.push(22);

	cout<<"Sorted Stack using temporary stack: "<<endl;
	sortStackUsingTemporaryStack();

	// ----------------------------------------------------------

  return 0; 
} 
