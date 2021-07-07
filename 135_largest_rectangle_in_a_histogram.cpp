
/*

Harshit Gupta | 6th July, 2021
---------------------------------

Given an array of integers heights representing the histogram's bar height where the 
width of each bar is 1, return the area of the largest rectangle in the histogram.

https://leetcode.com/problems/largest-rectangle-in-histogram/
------


Solution: 
    1. We take a stack and iterate over the heights array
    2. If we have an empty stack or increasing/equal value compared to stack top, just push the index in the stack and move on.
    3. If we have decreasing value at any point of time, we pop the elements from stack and keep calculating the area and maxArea.
    4. If the iteration completes and we still have items remaining in the stack, we calculate their area till stack is empty.

Consider Example:
              _
        _   _| |
       | |_| | |_
       |_|_|_|_|_|
Value:  2 1 2 3 1
Index:  0 1 2 3 4

i = 0, maxArea = -1, st = []     => Since stack is empty, we push the index 0 in it.
i = 1, maxArea = 2, st = [0]     => arr[st.top]=arr[0]=2 > arr[1]=1 so we pop it and calculate the area = 2*1 = 2
i = 1, maxArea = 2, st = []      => Note that i still remains 1 and we see stack is empty so we insert it & increase i.
i = 2, maxArea = 2,st = [1]      => arr[st.top]=arr[1]=1 <= arr[2]=2 so we insert it in stack & increase i
i = 3, maxArea = 2,st = [1,2]    => arr[st.top]=arr[2]=2 <= arr[3]=3 so we insert it in stack & increase i
i = 4, maxArea = 2,st = [1,2,3]  => Now arr[st.top]=arr[3]=3 > arr[4]=1 so we pop it and calc area = 3*(4-2-1) = 3
i = 4, maxArea = 3,st = [1,2]    => Now arr[st.top]=arr[2]=2 > arr[4]=1 so we pop it and calc area = 2*(4-1-1) = 4, i remains 4
i = 4, maxArea = 4,st = [1]      => arr[st.top]=arr[1]=1 <= arr[1]=1 so we insert it in stack & increase i. i=5 1st loop exits
i = 5, maxArea = 4,st = [1,1]    => Now we pop it and calc area = 1*(5-1-1) = 3
i = 5, maxArea = 4,st = [1]      => Now we pop it and calc area = 1*(5) = 5
i = 5, maxArea = 5,st = []       => Stack is empty so loop exits

TC: O(n)
SC: O(n) for stack

https://www.youtube.com/watch?v=ZmnqCZp9bBs

Paradigm:
---
  NOTE: 

*/


// --------------------------------------------------------

class Solution {
public:
    int largestRectangleArea(vector<int>& arr) {
        stack<int> st; // stack to store indexes
        int area, maxArea = -1;
        int i;
        // Iterate over the arr but do not increment i here since we only want to increment it in one case.
        for(i=0; i<arr.size();){
            // If arr[i] is an increasing/equal to stack top, push this index as well, also increase i+=1
            if(st.empty() || arr[st.top()] <= arr[i] ){
                st.push(i);
                i++;
            }
            // If arr[i] is decreasing/smaller than stack top, keep popping and calculating the area.
            // We do not increase i here and just pop(), so eventually the outer for loop will take care of 
            // keep "popping" till stack is empty or arr[i] >= stack top
            else {
                int top = st.top();
                st.pop();
                if(st.empty())
                    area = arr[top] * i;
                else
                    area = arr[top]* (i-st.top()-1);
                maxArea = max(area, maxArea);
            }
        }
        
        // once we reach the end and we still have elements in stack, we calculate the area for them as well.
        while(!st.empty()) {
            int top = st.top();
            st.pop();
            if(st.empty())
                area = arr[top] * i;
            else
                area = arr[top]* (i-st.top()-1);
            maxArea = max(area, maxArea);
        }
        
        return maxArea;
    }
};