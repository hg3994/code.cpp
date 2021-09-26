
/*

Harshit Gupta | 16th June, 2021
---------------------------------

C++ program for "Remove Invalid Parentheses"

Given a string s that contains parentheses and letters, 
    remove the minimum number of invalid parentheses to make the input string valid.
Return all the possible results. You may return the answer in any order.

Example 1:
    Input: s = "()())()"
    Output: ["(())()","()()()"]

Example 2:
    Input: s = "(a)())()"
    Output: ["(a())()","(a)()()"]

Example 3:
    Input: s = ")("
    Output: [""]


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

Similar Questions:
    1. https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/
        - Exact same problem but we need to return just any one answer but here we need all of them.
        - solved in 88_
    2. https://leetcode.com/problems/generate-parentheses/
        - Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
        - Input: n = 3
        - Output: ["((()))","(()())","(())()","()(())","()()()"]

NOTE: 

*/

/*

For every bracket we have two choices:
    Either it can be considered a part of the final expression OR
    It can be ignored i.e. we can delete it from our final expression.

Such kind of problems where we have multiple options and we have no strategy or metric of deciding greedily 
which option to take, we try out all of the options and see which ones lead to an answer. These type of problems 
are perfect candidates for the programming paradigm, Recursion.

Algorithm
1. Initialize an array that will store all of our valid expressions finally.
2. Start with the leftmost bracket in the given sequence and proceed right in the recursion.
3. The state of recursion is defined by the index which we are currently processing in the original expression. 
    Let this index be represented by the character i. Also, we have two different variables left_count and right_count 
    that represent the number of left and right parentheses we have added to our expression till now. These are the 
    parentheses that were considered.
4. If the current character i.e. S[i] (considering S is the expression string) is neither a closing or an opening 
    parenthesis, then we simply add this character to our final solution string for the current recursion.
5. However, if the current character is either of the two brackets i.e. S[i] == '(' or S[i] == ')', then we have two 
    options. We can either discard this character by marking it an invalid character or we can consider this bracket 
    to be a part of the final expression.
6. When all of the parentheses in the original expression have been processed, we simply check if the expression 
    represented by expr i.e. the expression formed till now is valid one or not. The way we check if the final expression 
    is valid or not is by looking at the values in left_count and right_count. For an expression to be valid 
    left_count == right_count. If it is indeed valid, then it could be one of our possible solutions.
        a. Even though we have a valid expression, we also need to keep track of the number of removals we did to get this 
            expression. This is done by another variable passed in recursion called rem_count.
        b. Once recursion finishes we check if the current value of rem_count is < the least number of steps we took to form 
            a valid expression till now i.e. the global minima. If this is not the case, we don't record the new expression, 
            else we record it.

One small optimization that we can do from an implementation perspective is introducing some sort of pruning in our algorithm. 
    Right now we simply go till the very end i.e. process all of the parentheses and when we are done processing all of them, 
    we check if the expression we have can be considered or not.
We have to wait till the very end to decide if the expression formed in recursion is a valid expression or not. Is there a way 
    for us to cutoff from some of the recursion paths early on because they wouldn't lead to a solution? The answer to this is 
    Yes! The optimization is based on the following idea.
For a left bracket encountered during recursion, if we decide to consider it, then it may or may not lead to an invalid final 
    expression. It may lead to an invalid expression eventually if there are no matching closing bracket available afterwards. 
    But, we don't know for sure if this will happen or not.
However, for a closing bracket, if we decide to keep it as a part of our final expression (remember for every bracket we have 
    two options, either to keep it or to remove it and recurse further) and there is no corresponding opening bracket to match 
    it in the expression till now, then it will definitely lead to an invalid expression no matter what we do afterwards.
    e.g. ( (  ) ) )
    In this case the third closing bracket will make the expression invalid. No matter what comes afterwards, this will give 
        us an invalid expression and if such a thing happens, we shouldn't recurse further and simply prune the recursion tree.
    That is why, in addition to having the index in the original string/expression which we are currently processing and the 
        expression string formed till now, we also keep track of the number of left and right parentheses. Whenever we keep a 
        left parenthesis in the expression, we increment its counter. For a right parenthesis, we check if right_count < left_count. 
        If this is the case then only we consider that right parenthesis and recurse further. Otherwise we don't as we know it will 
        make the expression invalid. This simple optimization saves a lot of runtime.

*/

// Approach 1: Simple Recursion (TC: O(2^N) but gives TLE)
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

/*
The one thing all these valid expressions have in common is that they will all be of the same length i.e. 
as compared to the original expression, all of these expressions will have the same number of characters removed.

What if we could determine this count?
    What if in addition to determining this count of characters to be removed, we could also determine the number of 
    left parentheses and number of right parentheses to be removed from the original expression to get any valid expression?

    This would cut down the computations immensely and the runtime would plummet as a result. The reason for this is, 
    if we knew how many left and right parentheses are to be removed from the original expression to get a valid expression, 
    we would cut down on so many unwanted recursive calls.

    Imagine the original expression to be 1000 characters with only 3 misplaced ( parentheses and 2 misplaced ) parentheses. 
    In our previous solution we would end up trying to remove each one of left and right parentheses and try to reach a valid 
    expression in the end whereas we should only be trying out removing 3 ( brackets and 2 ) brackets.

    This is the exact number of ( and ) that have to be removed to get a valid expression. No more, no less.

    Let us look at how we can find out the number of misplaced left and right parentheses in a given expression first and 
    then we will slightly modify our original algorithm to incorporate these counts as well.

    1. We process the expression one bracket at a time starting from the left.
    2. Suppose we encounter an opening bracket i.e. (, it may or may not lead to an invalid expression because there can be 
        a matching ending bracket somewhere in the remaining part of the expression. Here, we simply increment the counter 
        keeping track of left parentheses till now. left += 1
    3. If we encounter a closing bracket, this has two meanings:
        a. Either there was no matching opening bracket for this closing bracket and in that case we have an invalid 
            expression. This is the case when left == 0 i.e. when there are no unmatched left brackets available. In such 
            a case we increment another counter say right += 1 to represent misplaced right parentheses.
        b. Or, we had some unmatched opening bracket available to match this closing bracket. This is the case when 
            left > 0. In this case we simply decrement the left counter we had i.e. left -= 1
    4. Continue processing the string until all parentheses have been processed.
    5. In the end the values of left and right would tell us the number of unmatched ( and ) parentheses respectively.
    
Now that we have these two values available that tell us the total number of left i.e. ( and right i.e. ) parentheses that 
have to be removed to make the invalid expression valid, we will modify our original algorithm discussed in the previous 
session to avoid unwanted recursions.

Algorithm
    The overall algorithm remains exactly the same as before. The changes that we will incorporate are listed below:

    1. The state of the recursion is now defined by five different variables:
        index which represents the current character that we have to process in the original string.
        left_count which represents the number of left parentheses that have been added to the expression we are building.
        right_count which represents the number of right parentheses that have been added to the expression we are building.
        left_rem is the number of left parentheses that remain to be removed.
        right_rem represents the number of right parentheses that remain to be removed. Overall, for the final expression 
            to be valid, left_rem == 0 and right_rem == 0.
    2. When we decide to not consider a parenthesis i.e. delete a parenthesis, be it a left or a right parentheses, we have 
        to consider their corresponding remaining counts as well. This means that we can only discard a left parentheses if 
        left_rem > 0 and similarly for the right one we will check for right_rem > 0.
    3. There are no changes to checks for considering a parenthesis. Only the conditions change for discarding a parenthesis.
    4. Condition for an expression being valid in the base case would now become left_rem == 0 and right_rem == 0. Note that 
        we don't have to check if left_count == right_count anymore because in the case of a valid expression, we would have 
        removed all the misplaced or invalid parenthesis by the time the recursion ends. So, the only check we need if 
        left_rem == 0 and right_rem == 0.

The most important thing here is that we have completely gotten rid of checking if the number of parentheses removed is lesser 
than the current minimum or not. The reason for this is we always remove the same number of parentheses as defined by 
left_rem + right_rem at the start of recursion.

*/
// Approach 2: Smarter Recursion. Limited Backtracking.
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


// ---------------------------------------
// SIMILAR PROBLEM 2: generate-parentheses
// ---------------------------------------

// Approach: 1 
class Solution {
    // n=1
    //      ()
    // n=2
    //      ()(), (()), ()()  ====> ()(), (())
    // n=3
    //      ()(()), (()()), ((())), (()()), (())(), ()()(), (())() ====> ((())), (())(), ()(()), (()()), ()()()

    // Generate the brackets for each level from 1 till n
    // We keep updating the set of brackets. 
    // We start with 1=() and then we add a pair of braces '()' into every place of every string of the set.
    // For n=2 () => ()(), (()), ()() => Converting this to a set then it becomes ()(), (())
    // For n=3, [()(), (())]    => ()(()), (()()), ((())), (()()), (())(), ()()(), (())() 
    //                          => changing to a set ((())), (())(), ()(()), (()()), ()()()
    
public:
    vector<string> generateParenthesis(int n) {
        unordered_set<string> s;
        s.insert("()");
        for(int i=2; i<=n; i++){
            unordered_set<string> new_st;
            for (auto elem: s) {
                for(int j=0; j<elem.size(); j++){
                    string new_s = elem.substr(0,j)+"()"+elem.substr(j,elem.size());
                    new_st.insert(new_s);
                }
            }
            s = new_st;
        }
        vector<string> v(s.begin(), s.end());
        return v;
    }
};


// Approach 2: 
// In JAVA
// TC: https://leetcode.com/problems/generate-parentheses/solution/
class Solution {
    public List<String> generateParenthesis(int n) {
        List<String> ans = new ArrayList();
        backtrack(ans, new StringBuilder(), 0, 0, n);
        return ans;
    }

    public void backtrack(List<String> ans, StringBuilder cur, int open, int close, int max){
        if (cur.length() == max * 2) {
            ans.add(cur.toString());
            return;
        }

        if (open < max) {
            cur.append("(");
            backtrack(ans, cur, open+1, close, max);
            cur.deleteCharAt(cur.length() - 1);
        }
        if (close < open) {
            cur.append(")");
            backtrack(ans, cur, open, close+1, max);
            cur.deleteCharAt(cur.length() - 1);
        }
    }
}