
/*

Harshit Gupta | 12th June, 2021
---------------------------------

C++ program for "Merge Two sorted Arrays"

https://leetcode.com/problems/merge-sorted-array/

You are given two integer arrays nums1 and nums2, sorted in non-decreasing order, 
and two integers m and n, representing the number of elements in nums1 and nums2 respectively.
Merge nums1 and nums2 into a single array sorted in non-decreasing order.

The final sorted array should not be returned by the function, but instead be stored inside 
the array nums1. To accommodate this, nums1 has a length of m + n, where the first m elements 
denote the elements that should be merged, and the last n elements are set to 0 and should 
be ignored. nums2 has a length of n.

Input: nums1 = [1,2,3,0,0,0], m = 3, nums2 = [2,5,6], n = 3
Output: [1,2,2,3,5,6]
Explanation: The arrays we are merging are [1,2,3] and [2,5,6].
The result of the merge is [1,2,2,3,5,6] with the underlined elements coming from nums1.

------

Solution: 
    1. Merge nums2 into nums1's end (which has 0s) and then sort nums1 which contains all elements.
        TC: O(n+m log n+m)
        SC: O(n+m) used for sorting

    2. Take another array nums1Copy and copy 'm' elements of nums1 into nums1Copy. 
        Now compare nums1Copy and num2 and keep the nums1 array sorted.
        TC: O(n+m)
        SC: O(n+m) used for numscopy

    3. Similar to #2 but here we start from the back of both nums1 and nums and use the 
        extra 0s of nums1 to keep the largest elements. We do not need extra space now.
        TC: O(n+m)
        SC: O(1)


Paradigm: Sort

---
  NOTE: 

*/

class Solution {
public:
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i=m-1, j=n-1, k=n+m-1;
        while(i>=0 && j>=0)
            if(nums1[i] > nums2[j])
                nums1[k--] = nums1[i--];
            else
                nums1[k--] = nums2[j--];
        while(i>=0)
            nums1[k--] = nums1[i--];
        while(j>=0)
            nums1[k--] = nums2[j--];
    }
};


// Approach 1: merge nums2 into nums1 and then sort
// TC: O(n+m log n+m), SC: O(n)
// int i=m, j=0;
// while(j<n){
//     nums1[i] = nums2[j]; i++; j++;
// }
// sort(nums1.begin(), nums1.end());


// Approach 2: Take another array nums1Copy and copy 'm' elements of nums1 into nums1Copy.
// Now compare nums1Copy and num2 and keep the nums1 array sorted.
// TC: O(n+m), SC: O(n+m)
// vector<int> nums1Copy(m);
// for(int i=0;i<m;i++)
//     nums1Copy[i] = nums1[i];

// int i=0, j=0, k=0;
// while(i<m && j<n)
//     if(nums1Copy[i] < nums2[j])
//         nums1[k++] = nums1Copy[i++];
//     else
//         nums1[k++] = nums2[j++];
// If one of the arrays end up first, then copy the rest of the second array into nums1
// while(i<m)
//     nums1[k++] = nums1Copy[i++];
// while(j<n)
//     nums1[k++] = nums2[j++];
