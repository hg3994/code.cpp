/* 
Harshit Gupta | 17th October, 2018

C++ program for calculating length of longest increasing subsequence length in O(n2) time

https://www.youtube.com/watch?v=CE2b_-XfVDk
https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/

Solution: We will use very basic dynamic Programming to solve this.
    * At every point, if a number arr[i] such that arr[j] < arr[i], j<i, 
        then L[i] is maximum of L[j]+1 or L[i]. j iterates from 0 to i (for all elements less than it)
        This is how we will keep track of all the numbers lesser than i and will choose the max L[] and save it in L[i].


    arr[i]  1 -5  3 -3  5
    dp[]    1  1  1  1  1
i=1, j=0    1  1  1  1  1   arr[i]=-5 < arr[j]=1
i=2, j=0    1  1  2  1  1   arr[i]=3  > arr[j]=1  so dp[i] = max(dp[j]+1, dp[i]) = max(2,1) | LIS: 1,3
     j=1    1  1  2  1  1   arr[i]=3  > arr[j]=-5 so dp[i] = max(2,2) | LIS: -5, 3
i=3, j=0    1  1  2  1  1   arr[i]=-3 < arr[j]=1
     j=1    1  1  2  2  1   arr[i]=-3 > arr[j]=-5 so dp[i] = max(2,1) | LIS: -3,-5
     j=2    1  1  2  2  1   arr[i]=-3 < arr[j]=3
i=4, j=0    1  1  2  2  2   arr[i]=5  > arr[j]=1  so dp[i] = max(2,1) | LIS: 1,5 
     j=1    1  1  2  2  2   arr[i]=5  > arr[j]=-5 so dp[i] = max(2,2) | LIS: -5,5 
     j=2    1  1  2  2  3   arr[i]=5  > arr[j]=3  so dp[i] = max(3,2) | LIS: 1,3,5
     j=3    1  1  2  2  3   arr[i]=5  > arr[j]=-3 so dp[i] = max(3,3) | LIS: 1,3,5 | -5,-3,5

LIS = 3 
    - This may be present anywhere in the dp array. In this case, it is last
        but if there are decreasing elements in the end it may be in the middle.

Similar Question:
    1. https://leetcode.com/problems/best-team-with-no-conflicts/
        - This problem can also be modified to ask "Sum" of all elements forming 
            the longest increasing subsequence.
        - In this case, we init the dp[] with arr[i] and not 1.
        - dp[i] = max(dp[j]+arr[i], dp[i]); (Add arr[i] instead of 1)

    2.  https://www.geeksforgeeks.org/longest-increasing-subarray/
        - Same question for subarrays
*/

#include <bits/stdc++.h>
using namespace std; 

void longestIncreasingSubsequence(vector<int> arr){
    int n = arr.size();
    
    // This vector stores the LENGTH of longest increasing subsequence till 'i'
    vector<int> L(n);
    int maximum_increasing_sub=0;
    
    //Initialize the array with 1 since the Longest increasing subsequence at least can be 1.
    for(int i=0;i<n;i++)
        L[i]=1;
    
    // Iterate over all elements from i=1 to n
    for(int i=1;i<n;i++){
        
        // Iterate over all the elements from j=0 to i so that we can save the maximum value in L[i]
        for(int j=0;j<i;j++){
            
            // If the element at j is less than element at i, then we check its L[] 
            // and keep it only if it is greater than what we already have from other arr[j]s.
            if(arr[j]<arr[i]){
                L[i] = max(L[j]+1, L[i]);
            }
        }
    }
    
    for(int i=0;i<n;i++){
        // cout<<L[i]<<" ";
        if(L[i]>maximum_increasing_sub)
            maximum_increasing_sub = L[i];
    }
    
    cout<<maximum_increasing_sub<<endl;
}

int main(){
    vector<int> arr = {3, 4, -1, 5, 8, 2, 3, 12, 7, 9, 10};
    longestIncreasingSubsequence(arr);
    return 0;
}


// ---------------------------------------
// LEETCODE SOLUTION FOR SIMILAR PROBLEM 1
// ---------------------------------------

class Solution {
public:
  
  int longestIncreasingSubsequence(vector<int> arr){
    int n = arr.size();

    // This vector stores the longest increasing subsequence.
    vector<int> L(n);
    int maximum_increasing_sub=0;

    //Initialize the array with 1 since the Longest increasing subsequence at least can be 1.
    for(int i=0;i<n;i++)
        L[i]=arr[i];

    // Iterate over all elements from i=1 to n
    for(int i=1;i<n;i++){

        // Iterate over all the elements from j=0 to i so that we can save the maximum value in L[i]
        for(int j=0;j<i;j++){

            // If the element at j is less than element at i, then we check its L[] 
            // and keep it only if it is greater than what we already have from other arr[j]s.
            if(arr[j]<=arr[i]){
              L[i] = max(L[i],arr[i]+ L[j]);
            }
        }
    }

    int ans=0;
    for(int i=0;i<n;i++){
        // cout<<L[i]<<" ";
        if(L[i]>maximum_increasing_sub){
            maximum_increasing_sub = L[i];
        }
    }
    return maximum_increasing_sub;
  }
  
  void pairsort(vector<int>& a, vector<int>& b, int n) { 
      vector<pair<int, int>> pairt;

      // Storing the respective array 
      // elements in pairs. 
      for (int i = 0; i < n; i++)  
      { 
        pairt.push_back(make_pair(a[i], b[i]));
      } 

      // Sorting the pair array. 
      sort(pairt.begin(), pairt.end());

      // Modifying original arrays 
      for (int i = 0; i < n; i++)  
      { 
          a[i] = pairt[i].first; 
          b[i] = pairt[i].second; 
      } 
  } 
  
  int bestTeamScore(vector<int>& scores, vector<int>& ages) {
    int n = scores.size();
    pairsort(ages, scores, n);
    return longestIncreasingSubsequence(scores);
  }
};

// ------------------------------------------------------------
// SOLUTION FOR SIMILAR PROBLEM 2 - LONGEST INCREASING SUBARRAY
// ------------------------------------------------------------

int lenOfLongIncSubArr(int arr[], int n)
{
    // 'max' to store the length of longest increasing subarray
    // 'len' to store the lengths of longest increasing subarray
    int max = 1, len = 1;
     
    // traverse the array from the 2nd element
    for (int i=1; i<n; i++)
    {
        // if current element if greater than previous element, then this element helps in building
        // up the previous increasing subarray encountered so far
        if (arr[i] > arr[i-1])
            len++;
        else {
            // check if 'max' length is less than the length of the current increasing subarray. If true,
            // then update 'max'
            if (max < len)   
                max = len;
                 
            // reset 'len' to 1 as from this element again the length of the new increasing subarray is being calculated   
            len = 1;   
        }   
    }
     
    // comparing the length of the last increasing subarray with 'max'
    if (max < len)
        max = len;
     
    // required maximum length
    return max;
}