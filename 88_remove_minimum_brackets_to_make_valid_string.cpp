/*

Harshit Gupta | 23rd May, 2021
---------------------------------

C++ program for "Remove minimum number of brackets to make the input a valid string"
https://leetcode.com/problems/minimum-remove-to-make-valid-parentheses/

Example 1:
    Input: s = "lee(t(c)o)de)"
    Output: "lee(t(c)o)de"
    Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

Example 2:
    Input: s = "a)b(c)d"
    Output: "ab(c)d"

Example 3:
    Input: s = "))(("
    Output: ""
    Explanation: An empty string is also valid.

Example 4:
    Input: s = "(a(b(c)d)"
    Output: "a(b(c)d)"

------

Solution: We will use stack to implement the solution.
    - In the stack, we keep indexes of the ( only
    - In case we see a ), 
    -   If the stack is not empty, we check and pop the last '(' we saw since it will match with this ')'
    -   If the stack is empty, we remove this ')' and not make it a part of the final string
    - Finally, if we are left with some indexes of '(' in the stack, we try to remove those '(' 
        from the final string as well

Time Complexity: O(n)
Space Complexity: O(n): stack, other temp strings
---
  NOTE: 

*/


class Solution {
public:
    string minRemoveToMakeValid(string s) {
        int n = s.size();
        // Stack to store the indexes of the opening brackets (
        stack<int> st;
        string a;
        // We ignore the ')' which are without the matching '(' and this will reduce the indexes of the '('
        // To keep track of how many ')' we ignore, we use this variable.
        int closing_brackets_ignored=0;
        
        // Iterate over the string
        //  ( : We insert its index in stack
        //  ) : If stack is empty/ no matching ( is found, we ignore it and increase 'closing_brackets_ignored' + 1 
        //      since it will reduce the index of ( which are ahead in the string
        //      If stack is not empty, we pop the matching ( index from the stack.
        // Other: Ignore
        
        // We keep on copying the all characters (except ignored ')' ) into another string 'a'
        for(int i=0;i<n; i++){
            if(s[i]== '('){
                st.push(i-closing_brackets_ignored);
            }
            else if(s[i]==')'){
                if(st.empty()){
                    closing_brackets_ignored++;
                    continue;
                }
                else {
                    st.pop();
                }
            }
            a += s[i];
        }
        // If the stack i empty, we are sure that we have removed the unwanted ')' from the string and 
        // there's no unwanted '(' in the string as welll
        if(st.empty()){
            return a;    
        }
        // There are unwanted '(' which are yet to be removed from the string 'a'
        // The indexes of those ( are present in the stack. They must be removed since they do not have a matching )
        // At those indexes we put '*' so that we can identify the "unwanted" (
        // Now we copy the string 'a' into string 'b' without those '*'
        // Eventually we removed the unwanted the ( as well.
        else{
            vector<int> index_to_eliminate;
            // Putting * inplace of unwanted (
            while(!st.empty()){
                int index= st.top();
                index_to_eliminate.push_back(index);
                a[index]='*';
                st.pop();
            }
            
            // Copying 'a' to 'b' without the *
            string b;
            for(int i=0; i<a.size(); i++){
                if(a[i]!='*'){
                    b+=a[i];
                }
            }
            return b;
        }
        
    }
};
