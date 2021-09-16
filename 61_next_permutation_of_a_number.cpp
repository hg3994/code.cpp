/*

Harshit Gupta | 26th September, 2020
-------------------------------------

Ruby program for "Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.
If such arrangement is not possible, it must rearrange it as the lowest possible order (ie, sorted in ascending order).
The replacement must be in-place and use only constant extra memory."

https://leetcode.com/problems/next-permutation/
https://www.nayuki.io/page/next-lexicographical-permutation-algorithm
https://www.geeksforgeeks.org/find-the-next-lexicographically-greater-word-than-a-given-word/

1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
------

Solution: 
    Approach 1: 
        The solution to the problem comes in 4 steps:
      - Find the largest index i such that arr[i-1] < arr[i] (0125330 -> 012'5'330, a[i]->5) [Upward Slope]
      - If no such i exists, 
        - Then the array is already sorted decending. We just need to reverse (321 -> 123)
      - Else
        - Finding the greatest index j such that j>=i and arr[j]>arr[i-1] (01'2'5330 -> 01253'3'0, a[i-1]=2, a[j]=3)
        - Swap arr[j] and arr[i-1] (0125330 -> 0135320)
        - Reverse the suffix since we want the next perm, so it has to be the smallest (013|5320 -> 013|0235)

    Approach 2: 
        - We can also do this with next_permutation function which does the same thing.
        - It returns false when the element is greatest, otherwise true after changing 
            the number to lowest (321 ->123)

Time Complexity: O(n)
Space Complexity: O(1)

Similar Question:
  1. https://leetcode.com/problems/next-greater-element-iii/
        - Calculate the Next Greater Number for input n with the same digits
        - If it is the greatest num formed from those digits OR the answer is 
            not in Integer range (>INT_MAX), return -1
        - It returns false when the element is greatest, otherwise true after changing 
            the number to lowest (321 ->123)

*/

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = nums.size();
        int i=n-1;
        // 54'7'532
        while(i>0 && nums[i-1]>= nums[i])
            i--;
        // 54(7)532, i= index 2(7)
        if(i==0){
            reverse(nums.begin(), nums.end());
        }
        else{
            int j=n-1;
            while(j>=i && nums[j]<=nums[i-1])
                j--;
            // 5(4)7(5)32, i-1= index 1(4) , j= index 3 (5)
            
            swap(nums[j], nums[i-1]);
            // 5(5)7(4)32
            
            reverse(nums.begin()+i, nums.begin()+n);
            // 5(5)2347
        }
    }
};

// Approach 2: using library function
void nextPermutation(vector<int>& nums) {
    next_permutation(begin(nums), end(nums));
}

// ------------------------------------------------------
// Solution for Next Greater Element (Similar Question 1)
// ------------------------------------------------------

// Approach 1: Exception Handling
class Solution {
public:
    int nextGreaterElement(int n) {
        string sn = to_string(n);
        // Returns false if the number is greatest and we return -1 then
        if(next_permutation(sn.begin(), sn.end()) ){
            try {
                return stoi(sn);
            }
            catch (std::out_of_range const&) {
                return -1;
            }
        }
        else
            return -1;
    }
};

// Approach 2: Convert it to long long from string & then check if it exceeds INT_MAX
int nextGreaterElement(int n) {
    auto digits = to_string(n);
    next_permutation(begin(digits), end(digits));
    auto res = stoll(digits);
    return (res > INT_MAX || res <= n) ? -1 : res;
}