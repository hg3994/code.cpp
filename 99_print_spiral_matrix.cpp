
/*

Harshit Gupta | 4th June, 2021
---------------------------------

C++ program for "Printing Matrix in Spiral Manner"
https://leetcode.com/problems/spiral-matrix/

Input: matrix = [   [1,2,3],
                    [4,5,6],
                    [7,8,9] ]
Output: [1,2,3,6,9,8,7,4,5]

Input: matrix = [   [1,2,3,4],
                    [5,6,7,8],
                    [9,10,11,12]    ]
Output: [1,2,3,4,8,12,11,10,9,5,6,7]

------

Solution: 
    - Imagine 4 rods (m_start, m_end) in rows (n_start, n_end) in columns
    - Just keep walking on the rods
    - Once walked, bring the rods closer to each other and keep doing this till they overlap
    - NOTE: When m_start and m_end are overlapping, do not traverse the same thing left->right 
            and then right->left. Similarly, for n_start and n_end

Time Complexity: O(n)
Space Complexity:

Paradigm: Arrays, Matrix
---
  NOTE: 

*/

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        
        int m = matrix.size();
        int n = matrix[0].size();
        
        // 4 rods starting
        int m_start = 0;
        int m_end   = m-1;
        int n_start = 0;
        int n_end   = n-1;
        
        vector<int> ans;
            
        while(m_start <= m_end && n_start <= n_end){
            
            for(int i=n_start;i<=n_end;i++){
                ans.push_back(matrix[m_start][i]);
            }

            for(int i=m_start+1; i<=m_end-1; i++){
                ans.push_back(matrix[i][n_end]);
            }
            
            if (m_start != m_end){
                for(int i=n_end; i>=n_start; i--){
                    ans.push_back(matrix[m_end][i]);
                }
            }
            
            if (n_start != n_end){
                for(int i=m_end-1; i>=m_start+1; i--){
                    ans.push_back(matrix[i][n_start]);
                }
            }
            
            m_start++; m_end--;
            n_start++; n_end--;
        }
        return ans;
    }
};