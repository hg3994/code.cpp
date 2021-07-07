
/*

Harshit Gupta | 6th July, 2021
---------------------------------

Given a rows x cols binary matrix filled with 0's and 1's, 
find the largest rectangle containing only 1's and return its area.
https://leetcode.com/problems/maximal-rectangle/
------

Solution: 
    Read this to find largest rectangle in Histogram : https://leetcode.com/problems/largest-rectangle-in-histogram/discuss/1320113/c-explained-stack-on

    1. We just iterate row by row and try to create a histogram like thing in an array
     - If the value is a 0, we make the height 0, if it is 1, we addit to the prior height
    2. At each point, we find the max Area of rectangle in histogram - in O(n) time.
    3. The max of all areas is the largest rectangle in the matrix.

TC: O(n2)
SC: O(n)

Paradigm: DP, Stack
---
  NOTE: 

*/


class Solution {
public:
    int maximalRectangle(vector<vector<char>>& matrix) {
        if(matrix.size() == 0)
            return 0;
        int m = matrix.size();
        int n = matrix[0].size();
        int area = 0;
        int maxArea = 0;
        vector<int> dp(n,0);
        
        // Iterate and try to create a histogram till m'th row.
        // Get max rectangle of that histogram
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if (matrix[i][j] == '0')
                    dp[j] = 0;
                else
                    dp[j] += 1;
            }
            area = maxAreaInHistogram(dp);
            maxArea = max(area, maxArea);
        }
        return maxArea;
    }
    
    int maxAreaInHistogram(vector<int> arr){
        stack<int> st;
        int area, maxArea=-1;
        int i;
        for(i=0; i<arr.size();){
            if(st.empty() || arr[st.top()] <= arr[i]){
                st.push(i);
                i++;
            }
            else {
                int top = st.top();
                st.pop();
                if (st.empty())
                    area = arr[top] * i;
                else 
                    area = arr[top] * (i - st.top() - 1);
                
                maxArea = max(maxArea, area);
            }
        }
        while(!st.empty()){
            int top = st.top();
            st.pop();
            if (st.empty())
                area = arr[top] * i;
            else
                area = arr[top] * (i - st.top() - 1);
            maxArea = max(area, maxArea);
        }
        return maxArea;
    }
    
};