/* 
Harshit Gupta | 7th November, 2018

https://ide.geeksforgeeks.org/L3hCgN7v7j
https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

C++ program for printing all the permutations of a string

Solution: This is the Backtracking question with an approach of choose, Explore, and Un-choose.
    See the image in the Link to understand the solution.
    Also, uncomment the lines in the code to see how the string changes in each step
    to print the permutations.

Paradigm: Backtracking

Time Complexity: O(n*n!)

*/

#include <bits/stdc++.h>
using namespace std; 

void swap(char *a, char *b){
    // Uncomment to see how the swaps happen. 
    // Note that this will get called for both normal swap and backtracking swap.
    // cout<<"Swapping: "<<(*a)<<" and "<<(*b)<<endl;
    char t=*a;
    *a=*b;
    *b=t;
}

void permutations(string s, int l, int r){
    // Uncomment to see how the string changes
    // cout<<"String: "<<s<<" l: "<<l<<" r: "<<r<<endl;
    
    // If starting reaches the ending index, then print the string.
    if(l==r){
        cout<<s<<endl;
        return;
    }
    
    // Iterating from the starting index to the ending index.
    for(int i=l;i<=r;i++){
        swap(&s[i], &s[l]); // Swap this character with the first starting index char.
        permutations(s,l+1,r); // Fix this one and go for the next character.
        swap(&s[i], &s[l]); // Backtrack.
    }
}

int main() 
{
    string s = "abc";
    int n = s.size();
    permutations(s,0,n-1);
    return 0; 
} 
