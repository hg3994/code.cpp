
/*

Harshit Gupta | 2nd June, 2021
---------------------------------

C++ program for "Find the Minimum value in a stack in O(1) time"
https://leetcode.com/problems/min-stack/
------

Solution: We keep a stack of pairs and always keep the minimum value at that instance of time.
    When asked, we can show the top's minimum that would tell us the "minimum value" at this instance.

Time Complexity: O(1)
Space Complexity:

Paradigm:
---
  NOTE: 

*/

class MinStack {
public:
    // stack to keep integer and minimum value at level of stack
	// This will make sure we have "Minimum at all instance of stack and even if we pop a few numbers, we can tell what was the minimum at that time.."
    stack<pair<int,int>> s;
    
    MinStack() {
    }
    
	// push the number twice for an empty stack otherwise push the minimum of (min till now and this num).
    void push(int val) {
        if(s.empty()){
            s.push({val, val});
        }
        else{
            int mini = min(s.top().second, val);
            s.push({val, mini});
        }
    }
    
    void pop() {
        s.pop();
    }
    
    int top() {
        return s.top().first;
    }
    
    int getMin() {
        return s.top().second;
    }
};