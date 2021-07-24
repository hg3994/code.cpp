
/*

Harshit Gupta | 24th July, 2021
---------------------------------

Problem Statement:
    Given an array nums, you are allowed to choose one element of nums and change it by any value in one move.
    Return the minimum difference between the largest and smallest value of nums after perfoming at most 3 moves.

2 3 4 5
2 2 2 2 => 0
    
0 1 5 10 14
0 1 1 1  1  => 1
    
0 1 1 4 6 6 6
6 6 6 4 6 6 6 => 2
    
1 5 6 14 15
5 5 6 6  6 => 1

------

Solution: 

    1.  Initially set the disclude window of size 3 to the last 3 elements of A, then slide the disclude window by 3. 
        Since A is sorted, we know the element at the ith index is the minimum element under consideration and the 
        element at the jth index is the maximum element under consideration. 

        This approach is more useful for a ingeneral K and not the fix value '3'

        [[1 5] 6 14 15] min_diff = 4
        [1 [5 6] 14 15] min_diff = 1
        [1 5 [6 14] 15] min_diff = 8
        [1 5 6 [14 15]] min_diff = 1
        
        [6 5 6 6 6] - Final array

    TC: O(nlogn)+O(n)
    SC: O(1)


    2. We have 4 plans:
        kill 3 biggest elements
        kill 2 biggest elements + 1 smallest elements
        kill 1 biggest elements + 2 smallest elements
        kill 3 smallest elements

        A = [1,5,6,13,14,15,16,17]
        n = 8

        Case 1: kill 3 biggest elements

            All three biggest elements can be replaced with 14
            [1,5,6,13,14,15,16,17] -> [1,5,6,13,14,14,14,14] == can be written as A[n-4] - A[0] == (14-1 = 13)

        Case 2: kill 2 biggest elements + 1 smallest elements

            [1,5,6,13,14,15,16,17] -> [5,5,6,13,14,15,15,15] == can be written as A[n-3] - A[1] == (15-5 = 10)

        Case 3: kill 1 biggest elements + 2 smallest elements

            [1,5,6,13,14,15,16,17] -> [6,6,6,13,14,15,16,16] == can be written as A[n-2] - A[2] == (16-6 = 10)

        Case 4: kill 3 smallest elements

            [1,5,6,13,14,15,16,17] -> [13,13,13,13,14,15,16,17] == can be written as A[n-1] - A[3] == (17-13 = 4)

        Answer is minimum of all these cases!

    TC: O(nlogn)
    SC: O(1)  

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/


class Solution {
public:
    int minDifference(vector<int>& nums) {
        int n = nums.size();
        if (n <= 4)
            return 0;
        sort(nums.begin(), nums.end());
        int i=0, j=n-4, min= INT_MAX;
        
        while(0 <= j && j<=n-1){
            // just because we have sorted, we can calc min like this.
            min = std::min(min, nums[j]-nums[i]);
            j++;
            i++;
        }
        return min;
        
    }
};


// Solution 2: 

   int minDifference(vector<int>& A) {
        int n = A.size();
        if (n < 5) return 0;
        sort(A.begin(), A.end());
        return min({A[n - 1] - A[3], A[n - 2] - A[2], A[n - 3] - A[1], A[n - 4] - A[0]});
    }