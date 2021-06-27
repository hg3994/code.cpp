
/*

Harshit Gupta | 16th June, 2021
---------------------------------

C++ program for "Remove Invalid Parentheses"

Given a string s that contains parentheses and letters, 
    remove the minimum number of invalid parentheses to make the input string valid.
Return all the possible results. You may return the answer in any order.
https://leetcode.com/problems/remove-invalid-parentheses/

------

Solution: 

    Please read the solution from https://leetcode.com/problems/remove-invalid-parentheses/solution/. 
    It's amazing!
    
    1. BackTracking
    2. Limited Backtracking

    Strongly recommend to read 1. before 2.

TC: O(2^N)
SC: O(N)

Paradigm:
---
  NOTE: 

*/

// Approach 2
class Solution {
public:
    
    unordered_set<string> validExpressions = {};
    
    void recurse(string s, int index, int leftCount, int rightCount, int leftRem, int rightRem, string expression){
        // If we reached the end of the string, just check if the resulting expression is
        // valid or not and also if we have removed the total number of left and right
        // parentheses that we should have removed.
        if(index == s.size()) {
            if(leftRem == 0 && rightRem == 0)
                validExpressions.insert(expression);
        }
        else {
            char currentCharacter = s[index];
            
            // The discard case. Note that here we have our pruning condition.
            // We don't recurse if the remaining count for that parenthesis is == 0.
            if(currentCharacter == '(' && leftRem>0 )
                recurse(s, index+1, leftCount, rightCount, leftRem-1, rightRem, expression);
            else if(currentCharacter == ')' && rightRem>0)
                recurse(s, index+1, leftCount, rightCount, leftRem, rightRem-1, expression);
                
            
            // If the current character is neither an opening bracket nor a closing one,
            // If the current character is (
            // If the current character is ) && rightCount < leftCount
            //      Simply add it to the expression, recurse & backtrack
            expression += currentCharacter;
            if(currentCharacter != '(' && currentCharacter != ')' )
                recurse(s, index+1, leftCount, rightCount, leftRem, rightRem, expression);
            else if(currentCharacter == '(')
                recurse(s, index+1, leftCount+1, rightCount, leftRem, rightRem, expression);
            else if (rightCount < leftCount) // Just for this condition, we have been sending the leftCount and rightCount variables, so that we dont waste time in bad recursions.
                recurse(s, index+1, leftCount, rightCount+1, leftRem, rightRem, expression);
            expression.pop_back();
        }
    }
    
    vector<string> removeInvalidParentheses(string s) {
        // Count the number of unmatched left and right brackets and this will be the number 
        // of brackets to be removed.
        int leftUnmatched = 0, rightUnmatched = 0;
        for(int i=0; i<s.size(); i++){
            if(s[i] == '(')
                leftUnmatched++;
            else if(s[i] == ')'){
                if(leftUnmatched == 0)
                    rightUnmatched++;
                else if(leftUnmatched > 0)
                    leftUnmatched--;
            }
        }
        recurse(s, 0, 0, 0, leftUnmatched, rightUnmatched, "");
        vector<string> v(validExpressions.begin(), validExpressions.end());
        return v;
    }
};

// Approach 1
class Solution {
public:
    
    unordered_set<string> validExpressions = {};
    int minimumRemoved = INT_MAX;
    
    void recurse(string s, int index, int leftCount, int rightCount, string expression, int removedCount){
        // If we reached the end of the string
        if(index == s.size()) {
            // if the current expression is valid
            if(leftCount == rightCount){
                if(removedCount <= minimumRemoved){
                    if(removedCount < minimumRemoved){
                        validExpressions = {};
                        minimumRemoved = removedCount;
                    }
                    validExpressions.insert(expression);
                }
            }
        }
        else{
            char currentCharacter = s[index];
            // If the current character is neither an opening bracket nor a closing one,
            // simply recurse further by adding it to the expression & then backtrack
            if(currentCharacter != '(' && currentCharacter != ')' ){
                // add
                expression += currentCharacter;
                // recurse
                recurse(s, index+1, leftCount, rightCount, expression, removedCount);
                // backtrack
                expression.pop_back();
            }
            else{
            // Considering to delete the bracket
                    // Recurse to delete the current char and move forward
                recurse(s, index+1, leftCount, rightCount, expression, removedCount+1);
                
            // Considering to keep the bracket so follow: add, recurse, backtrack
                // add
                expression += currentCharacter;
                //recurse
                if(currentCharacter == '(')
                    recurse(s, index+1, leftCount+1, rightCount, expression, removedCount);
                else if (rightCount < leftCount)
                    recurse(s, index+1, leftCount, rightCount+1, expression, removedCount);
                //backtrack
                expression.pop_back();
                
            }
        }
    }
    
    vector<string> removeInvalidParentheses(string s) {
        recurse(s, 0, 0, 0, "", 0);
        vector<string> v(validExpressions.begin(), validExpressions.end());
        return v;
    }
};