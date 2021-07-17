
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

Paradigm: Stack

    Similar Questions:
        1. https://leetcode.com/problems/max-stack/submissions/
            - Same question for Maximum
            - Also implement PopMax() which will Pop the Max Value and update the other needed values.
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

// ----------------------------
// LEETCODE MAX STACK SOLUTION
// ----------------------------

class MaxStack {
public:
    // Orig Stack
    stack<pair<int, int>> st;
    
    // Stack to get temporary values during popMax
    stack<pair<int, int>> stemp;
    
    MaxStack() { }
    
    void push(int x) {
        if(st.empty())
            st.push({x,x});
        else
            st.push({x,max(st.top().second,x)});
    }
    
    int pop() {
        int x = st.top().first;
        st.pop();
        return x;
    }
    
    int top() {
        return st.top().first;
    }
    
    int peekMax() {
        return st.top().second;
    }
    
    int popMax() {
        // Get the top from stack
        // If both the top's num and top's max are equal, then this is the max and we remove it
        // Else insert this pair into another temporary stack and pop from this one
        // Keep checking till top's num and top's max become equal
        // Once they become equal, 
        //      pop tthe max element from the stack
        //      keep pushing all the elements from temporary stack to here
        // NOTE: We use the MaxStack's push method here and not st.push since we need to figure out the MAX elements for all the pushes to st again now.
        int x = st.top().first;
        int y = st.top().second;
        while(x!=y){
            stemp.push(st.top());
            st.pop();
            x = st.top().first;
            y = st.top().second;
        }
        
        st.pop();
        
        while(!stemp.empty()){
            push(stemp.top().first);
            stemp.pop();
        }
        
        return x;
    }
};

/**
 * Your MaxStack object will be instantiated and called as such:
 * MaxStack* obj = new MaxStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->peekMax();
 * int param_5 = obj->popMax();
 */