
/*

Harshit Gupta | 3rd June, 2021
---------------------------------

C++ program for "Given an unsorted integer array nums, find the smallest missing positive integer.
You must implement an algorithm that runs in O(n) time and uses constant extra space."

https://leetcode.com/problems/first-missing-positive/

Example 1:
    Input: nums = [1,2,0]
    Output: 3

Example 2:
    Input: nums = [3,4,-1,1]
    Output: 2

Example 3:
    Input: nums = [7,8,9,11,12]
    Output: 1

------

Solution: 

    We are going to modify the input array
    If the number '1' is missing in the array then the "First Missing Positive" is 1. Else...
    The first missing positive will be in between 1 to n+1 in an array of n. 
    Get rid of all the numbers which are negative, zeroes  or > n (n+1 will be treated separately)
    How? => We will make all the numbers that are numbers which are negative, zeroes  or > n equals to 1
    Now we are left with an array with elements >=1 and <=n only. 
    a. We can create a map with the elements in array. Then iterate from 1 to n+1 to check for the missing element in a map. This is O(n) space solution
    b. Another idea is to use index in array as a hash key and sign of the element as a hash value which is presence detector. This is O(1) space solution.
         - The array (which after clean up contains only positive numbers), check each element value elem and change the sign of element nums[elem] to negative 
             to mark that number elem is present in nums. Be careful with duplicates and ensure that the sign was changed only once.
        
    Index:   [0, 1,  2,  3, 4, 5,  6, 7, 8, 9]
    Element: [3, 4, -1, -2, 1, 5, 16, 0, 2, 0]
             [3, 4,  1,  2, 1, 5,  1, 1, 2, 1]
    
    Hash:    { 1: 6, 2: 2, 3: 1, 4: 1, 5: 1 }
    
    (b) implementation
    ------------------
    1. Check if 1 is present in the array. If not, you're done and 1 is the answer.
    2. Replace negative numbers, zeros, and numbers larger than n by 1s.
    3. Walk along the array. Change the sign of a-th element if you meet number a. Be careful with duplicates : do sign change only once. 
         Use index 0 to save an information about presence of number n since index n is not available.
    4. Walk again along the array. Return the index of the first positive element.
    5. If nums[0] > 0 return n.
    6. If on the previous step you didn't find the positive element in nums, that means that the answer is n + 1.
    
    Index:   [0, 1,  2,  3, 4, 5,  6, 7, 8, 9]
    Element: [3, 4, -1, -2, 1, 5, 16, 0, 2, 0]
             [3, 4,  1,  2, 1, 5,  1, 1, 2, 0]
             [3,-4, -1, -2,-1,-5,  1, 1, 2, 0]
    
    Index: 6 has first positive from 1 to 9 so i=6 is our First Missing Positive.

    ---

    Another solution that I can think of is create a map of all positive numbers and then iterate from 1 to n and check
    if the element is present in the map, if yes, then return true, else false. => TC: O(n), SC: O(n)


Time Complexity: O(n)
Space Complexity: O(1)

Paradigm: HashMap,

---
  NOTE: 

*/



class Solution {
    
    
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        bool found1 = false;
        for(int i=0;i<n;i++){
            if(nums[i] == 1){
                found1 = true;
                break;
            }
        }
        // If 1 is present in the array
        if (found1){
            // Make the elements which are <=0 and >n as 1.
            for(int i=0;i<n;i++){
                if(nums[i] <= 0 || nums[i] > n){
                    nums[i] = 1; 
                }
            }
            
            // Take the absolute value of the nums[i] and convert it to negative.
            // Even if it was negative already, we do it since if a nums[2] is -5, it means that 2 is present but we also have to mark nums[5] to be negative (nums[5] = -(abs(nums[5])))
            for(int i=0;i<n;i++){
                int a = abs(nums[i]);
                if(a == n)
                    nums[0] = -abs(nums[0]);
                else
                    nums[a] = -abs(nums[a]);
            }
            
            // Any number which is >0 means that the index is not referred adn was not made to change to negative. Hence, that index is our "First Missing Positive" 
            for(int i=1;i<n;i++){
                if(nums[i] > 0){
                    return i;
                }
            }
            
            // If 0 was positive, it means that "n" is our "First Missing Positive" since we used 0 to store n. (check above loop)
            if(nums[0] > 0)
                return n;
            
            // If it reached here, it means all the numbers from 1 to n were present in the array. The "First Missing Positive" is n+1
            return n+1;
        }
        // If 1 was not present in the array, it is our "First Missing Positive" 
        else{
            return 1;
        }
        
    }
};