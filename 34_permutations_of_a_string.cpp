/* 
Harshit Gupta | 7th November, 2018

https://ide.geeksforgeeks.org/L3hCgN7v7j
https://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/
https://leetcode.com/problems/permutations/
C++ program for printing all the permutations of a string

Solution: This is the Backtracking question with an approach of choose, Explore, and Un-choose.
    See the image in the Link to understand the solution.
    Also, uncomment the lines in the code to see how the string changes in each step
    to print the permutations.

Paradigm: Backtracking

Time Complexity: O(n*n!)

Similar Problems:
    1. https://leetcode.com/problems/permutations-ii/
        - Input may contain duplicate elements but the output should be unique.
        - We use a set<vector<int>> instead of v of v and then convert it into v of v to return.

*/

// Initially we have N choices, and in each choice we have (N - 1) choices, and so on. Notice that at the end when adding the list to the result list, it takes O(N).
// Second, the space complexity should also be N x N! since we have N! solutions and each of them requires N space to store elements.

class Solution {
private:
    vector<vector<int>> result;
public:
    
    void permuteHelper(vector<int> nums, int l){
        int n = nums.size()-1;
        if(l == n){
            result.push_back(nums);
            return;
        }
        for(int i=l; i<=n; i++) {
            swap(nums[i], nums[l]);
            permuteHelper(nums, l+1);
            swap(nums[i], nums[l]);
        }
    }
    
    vector<vector<int>> permute(vector<int>& nums) {
        permuteHelper(nums, 0);
        return result;
    }
};

// ------------------------------------------
// Using next_permutation()
// ------------------------------------------
vector<vector<int>> permute(vector<int>& nums) {
    sort(nums.begin(),nums.end());
    vector<vector<int>>ans;
    do{
        ans.push_back(nums);
    }while(next_permutation(nums.begin(),nums.end()));
    return ans;    
}



// ----------------------------------------------------------------------------------

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
