/*

Harshit Gupta | 24th May, 2021
---------------------------------

C++ program for "Count number of subarrays with sum=k"
https://leetcode.com/problems/subarray-sum-equals-k/

Example 1:
    Input: nums = [1,1,1], k = 2
    Output: 2

Example 2:
    Input: nums = [1,2,3], k = 3
    Output: 2

------

Solution: Explained below
    - We can't use Sliding window here since it deals with negative numbers as well.
    - Sliding Window cant be used for arrays involving negative numbers.
    - We use Prefix sum with HashMaps.

Time Complexity: O(n)
Space Complexity: O(n)
---

  NOTE: 
    1. The 2nd Similar Problem "Maximum size of Subarray with Sum = K" seems similar to 
        3rd Similar Problem "Minimum size Subarray with Sum >= K" which is solved with Sliding Window but this one is solved with Prefix 
        Sum Index in Hashmaps. The difference is because this one has asked for subarray length
        for sum==k but the other one asked for sum>=k.

        Since the sum is open-ended, we use sliding window, When the sum is fixed=k, then we can use hashmaps and find
        exactly that sum-k is present or not and then calc the leng. For the prob #3, the sum is openended and hence
        sum-k will now make sense there.

        Another thing is that problem deals with only positive integers but here we can have Positive/Negative Integers.


  Similar Problem: 
    1. https://leetcode.com/problems/binary-subarrays-with-sum
        - Exact Same problem
    2. https://leetcode.com/problems/maximum-size-subarray-sum-equals-k/
        - Out of all the subarrays of size k, here we need to find the length of the 
            maximum subarray with the sum.
        - In the prev question, we were saving the freq because we wanted the number of times we have sum=k
        - Instead of saving the freq in map, here, we would need to save the indexes since we need to calc
            the length of the maximum subarray with the sum=k.
        - length of the max subarray will be calc by .. last time the sum-k was made at index map[sum-k]
            and now the diff between that index and this index i will be the len of the this subarray which
            makes a sum k.
    3. https://leetcode.com/problems/minimum-size-subarray-sum/
        - Minimum length of subarray with sum>=K
        - Solved using Sliding Window in 125_..
*/


//  arr:    [1,2,2,1,3, 5] , sum=4
//  Psum:   [1,3,5,6,9,14] => just showing, we don't need to store it.

// i=0, ans=0, sum=1, {1=>1}                    (-3 is not present in map)
// i=1, ans=0, sum=3, {1=>1, 3=>1}              (-1 is not present in map)
// i=2, ans=1, sum=5, {1=>1, 3=>1, 5=>1}        (1 is present in map, update ans)
//                                              If 5 is current sum and I have seen 1 before, then in between those it will make sum=4
// i=3, ans=1, sum=6, {1=>1, 3=>1, 5=>1, 6=>1}  (2 is not present in map)
// i=4, ans=2, sum=9, {1=>1, 3=>1, 5=>1, 6=>1, 9=>1}  (9-4 is present in map, update ans)
// i=5, ans=2, sum=14,{1=>1, 3=>1, 5=>1, 6=>1, 9=>1, 14=>1}  (14-4=10 is not present in map)

// The example above doesn't show the importance of keeping FREQ in map, maybe I need to modify it.
// But it will be clearly visible when negative elements would be involved and when a sum-k=X can be formed
// at different indexes and then we would need to add it 'FREQ' number of times in the ans.

class Solution {
public:
    
    // We iterate over the array and keep calculating the cumulative sum
    // We keep a map which tells us the number of times we have encountered a particular sum
    // We update the map with the frequency of the 'sum' variable (+1)
    // We check for the frequncy of "sum-k" for each particular sum, and add the freq of "sum-k" to ans.
    // Just because we are summing like prefix sum continously, we are sure that we are doing it for subarray
    // and not for subsequence.

    int subarraySum(vector<int>& nums, int k) {

        int ans=0;
        int sum=0;
        unordered_map<int, int> m = {{0,1}}; // Sum 0 can be made 1 number of times.
        // We store 0->1 since if we have arr[i] = k, and it should be added as arr[i] is a subarray of size=1
        // with sum=k. Then arr[i]-k = k-k = 0, and we should add 1 in ans for it. Hence, 0->1
        
        for(int i=0;i<nums.size(); i++){
            // Keep updating 'sum' variable which contains the cumulative sum
            sum += nums[i];
            
            // If (sum-k) is present in the map, then it means that current_sum-k has already been found
            // m[sum-k] times so add that to the answer
            // (Difference between 'sum-k' and sum is 'k')
            if(m.count(sum-k)){
                ans += m[sum-k];
            }
            
            // Update the map with the frequency of "sum" and increase it by 1.
            m[sum]++;
        }
        
        return ans;
    }
};



// -----------------------------------------------------
// Similar Question :2  MAXIMUM SIZE SUBARRAY WITH SUM=K
// -----------------------------------------------------

// [-2, -1, 2, 1], k=1
// [-2, -3,-1, 0] <- sum
// When i=2, nums[i]=2 and sum=-1, sum-k=-2, it has seen it before @ index 0 (saved in map)
// this means that the sum of elements between that and here is K, find the len and check if it max
// When i=3, nums[i]=1, sum=0, sum-k=-1, and it has seen it before @ index 2 (saved in map)
// this means that the sum of elements between that and here is K, find the len and check if it max

class Solution {
public:
    int maxSubArrayLen(vector<int>& a, int k){
        int ans=0, sum=0;
        // We store the sum and the location(i) of that sum so that we can calculate the len of subarray
        unordered_map<int,int> mp;
        mp[0]=-1;
        // We need mp[0]=-1 because if we encounter arr[i]=k, then k-k=0, then the subarray which has sum=k 
        // is from 0th index till ith index. The length is i+1. We can get it by i-arr[0] = i-(-1) = i+1
        // Basically anytime we encounter a sum S, that sum is valid from 0 till i and then max length is i+1
        
        for(int i=0;i<a.size();i++){
            // cumulative sum
            sum+=a[i];

            // if sum-k is present, then it means we have seen it before @ map[sum-k]
            // the sum of elements between that element and this i is 'k'
            // lets check if this subarray of len(i-map[sum-k]) is the max that we have seen till now
            if(mp.count(sum-k)){
                ans=max(ans,i-mp[sum-k]);
            }

            // Consider sum S was seen at index i before and now we saw this sum again, should we update i?
            // No, because for example, if we see this sum S again at index i1 and i2. (i < i1 < i2)
            // If we update it at i1, then for i1, the dist would now be i2-i1 but it could have been
            // as big as i2-i which will be greater than i2-i1 and I am interested in max length.
            if(!mp.count(sum)){
                mp[sum]=i;
            }
        }
        
        return ans;
    }
};