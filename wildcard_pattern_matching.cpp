/* 
Harshit Gupta | 20th October, 2018

https://ide.geeksforgeeks.org/YZEyle1e1V
https://www.geeksforgeeks.org/wildcard-pattern-matching/

C++ program for "Given a text and a wildcard pattern, implement wildcard pattern matching 
    algorithm that finds if wildcard pattern is matched with text. 
    The matching should cover the entire text (not partial text)."

Solution: Explained in detail in this link: https://www.geeksforgeeks.org/wildcard-pattern-matching/

Time Complexity: O(n2)

Paradigm: Dynamic Programming

*/

#include <bits/stdc++.h>
using namespace std; 

void wildcardMatching(string text, string pattern){
    int n = pattern.size();
    int m = text.size();
    
    // Create a dp table
    bool dp[n+1][m+1];
    
    // Two strings of 0 length would always match.
    dp[0][0]=1;
    
    // If pattern is nothing, but we have text, then it will not match(false)
    for(int i=1;i<m+1;i++)
        dp[0][i] = 0;  
    
    // If text is nothing, but we have pattern, then it will not match(false) 
    // exception is '*' which we have handled below
    for(int i=1;i<n+1;i++)
        dp[i][0] = 0;
        
    // Only '*' can match with an empty string.
    // This will handle patterns like: "*****ab" because they match till those 5 stars.
    for(int i=1;i<n+1;i++){
        if(pattern[i-1]=='*'){
            dp[i][0] = dp[i-1][0];
        }
    }
    
    
    for(int i=1;i<n+1;i++){
        for(int j=1;j<m+1;j++){
            // i-1 and j-1 used because dp[][] starts with 0 meaning empty strings but
            // out text and pattern have a character at '0', so starting the loop from 1,
            // we have to compensate that here.
            if(text[j-1] == pattern[i-1] || pattern[i-1]=='?'){
                dp[i][j] = dp[i-1][j-1];
            }
            else if(pattern[i-1]=='*'){
                dp[i][j] = dp[i-1][j] || dp[i][j-1];
            }
            else{
                dp[i][j] = 0;
            }
        }
    }

    // Uncomment to print the dp[][] table
    // for(int i=0;i<n+1;i++){
    //     for(int j=0;j<m+1;j++){
    //         cout<<dp[i][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    
    if (dp[n][m]==1)
        cout<<"True"<<endl;
    else
        cout<<"False"<<endl;
}

int main(){
    string str = "baaabab"; 
    string pattern = "*****ba*****ab"; //true
    // string pattern = "ba*****ab"; // true
    // string pattern = "ba*ab"; // true
    // string pattern = "a*ab"; // false
    // string pattern = "a*****ab"; //false
    // string pattern = "*a*****ab"; 
    // string pattern = "ba*ab****"; //true
    // string pattern = "****"; 
    // string pattern = "*"; 
    // string pattern = "aa?ab"; 
    // string pattern = "b*b"; 
    // string pattern = "a*a"; 
    // string pattern = "baaabab"; 
    // string pattern = "?baaabab"; 
    // string pattern = "*baaaba*"; 
    
    wildcardMatching(str, pattern);
    return 0;
}