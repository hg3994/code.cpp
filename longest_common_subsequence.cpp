/* 
Harshit Gupta | 18th October, 2018

C++ program for calculating longest increasing subsequence in O(n2) time

https://www.youtube.com/watch?v=NnD96abizww
https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/

Solution: We will use very basic dynamic Programming to solve this.
    * The trick is this recurrence relation
    if s1[i]==s[j], then 
        LCS[i][j] = 1+LCS[i-1][j-1];
    else 
        LCS[i][j] = max( LCS[i-1][j], LCS[i][j-1])

    When both are same, then we add 1 to the best that we have till now (L[i-1][j-1]) 
    because we are filling for L[i][j] and the best we have right now is L[i-1][j-1]

    When both are not same "ab" and "ac", then we take the bext of what we have:
        max (("ab", "a"),("a", "ac"))

*/

#include <bits/stdc++.h>
using namespace std; 

void longestCommonSubsequence(string s1, string s2){
    int n = s1.size();
    int m = s2.size();
    int LCS[n+1][m+1];
    
    for(int i=0;i<=n;i++){
        
        for(int j=0;j<=m;j++){
            
            if(i==0 || j==0){
                // Comparing a string with another string of length 0 
                // would have LCS of length 0.
                LCS[i][j]=0;
            }
            else if(s1[i]==s2[j]){
                // If both s[i] and s[j] are same, this means that 
                // 1 more character is common betweeen the two from what it was previously (L[i-1][j-1]).
                LCS[i][j] = 1+LCS[i-1][j-1];
            }
            else{
                // If both s[i] and s[j] are not same, then it mean that 
                // the LCS is whatever was highest by leaving one char from s1 or 
                // 1 character from s2.
                // e.g., "AGT" and "GX", then 'T' doesn't match 'X', so LCS would be 
                // max( LCS("AGT", "G"), LCS("AG", "GX"))
                LCS[i][j] = max(LCS[i-1][j], LCS[i][j-1]);
            }
            
        }
    }
    cout<<LCS[n][m]<<endl;
    
}

int main(){
    string s1 = "ABCDGH";
    string s2 = "AEDFHR";
    longestCommonSubsequence(s1, s2);
    return 0;
}