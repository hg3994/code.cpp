
/*

Harshit Gupta | 16th July, 2021
---------------------------------

Problem Statements:

1. https://leetcode.com/problems/two-sum/
	- Given an arr of ints and a target, return indices of the two numbers such that they add up to target.
	- Using map to store the INDEXES of elements and when the target-num[i] is already present,
		it means that both num[i] and num[target-i] are present and they add up to target
	- TC: O(n), SC: O(n)

2. https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    - The input array is sorted here. Can we use this property?
    - Check the approach 2 which uses the two pointer approach just because the input is sorted

3. https://leetcode.com/problems/two-sum-iii-data-structure-design/
    - Two Sum on a stream of Integers
    - Design a data structure that accepts a stream of integers and checks 
        if it has a pair of integers that sum up to a particular value.

4. https://leetcode.com/problems/two-sum-less-than-k/
    - Given an array nums of integers and integer k, return the maximum sum such that 
        there exists i < j with nums[i] + nums[j] = sum and sum < k. 
    -   Input: nums = [34,23,1,24,75,33,54,8], k = 60
        Output: 58
        Explanation: We can use 34 and 24 to sum 58 which is less than 60.
    - Elements are always in the range 1-1000. (Ring any bells? Counting Sort?)

5. https://leetcode.com/problems/two-sum-bsts/
    - Given the roots of two binary search trees, root1 and root2, return true if and only if there is a 
        node in the first tree and a node in the second tree whose values sum up to a given integer target
    - Traverse the first tree, and store the complements (target - val) of all node values in a hashset.
    - Traverse the second tree and check if any of its elements exists in the hashset. 
        If yes - return True. If no - return False.

6. https://leetcode.com/problems/two-sum-iv-input-is-a-bst/
    - Given the root of a Binary Search Tree and a target number k, return true if there exist 
        two elements in the BST such that their sum is equal to the given target.
    - Approach 1: While traversing keep storing the elements in a map and then when if 
        we see k-(root->val), then we return
    - Approach 2: Inorder Traversal of a BST gives a sorted list, then we apply 2 pointer approach
        mentioned in the 2nd question.

7. https://leetcode.com/problems/count-good-meals/submissions/
    - Given an array find the sum of all pair of elements which sum to any power of 2
    - This is the same TwoSum problem but here the target is not one but can be multiple powers of 2
        so we have to test it for all the powers of two as targets.
    - 0 <= arr[i] <= 2^20 so check for at max 20th power of 20
    - Mod the answer by 1000000009

------
Paradigm: HashMaps
---
  NOTE: 

*/


// ----------------------
// LC Problem 1: Two Sum
// ----------------------
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        vector<int> ans;
        
        for(int i=0;i<nums.size(); i++){
            int complement = target-nums[i];
            if(map.count(complement)){
                ans.push_back(map[complement]);
                ans.push_back(i);
                return ans;
            }
            else{
                map[nums[i]]=i;
            }
        }
        return ans;
    }
};


// ---------------------------------------
// LC Problem 2: Two Sum with Sorted Input
// ---------------------------------------


// Approach 1: Using Hashmaps
// TC: O(n), SC: O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        unordered_map <int, int>  map;
        for(int i=0;i<numbers.size(); i++){
            if(map.count(target-numbers[i])){
                vector<int> v;
                v.push_back(map[target-numbers[i]]+1);
                v.push_back(i+1);
                return v;
            }
            else{
                map[numbers[i]] = i;
            }
        }
        vector<int> v;
        return v;
    }
};


// Approach 2: Have two pointers low=0 & high=n-1
// Depending on what they add upto keep increasing 1 till we reach the sum
// TC: O(n), SC: O(1)
class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        int low = 0, high = numbers.size() - 1;
        while (low < high) {
            int sum = numbers[low] + numbers[high];
            if (sum == target)
                return {low + 1, high + 1};
            else if (sum < target)
                ++low;
            else
                --high;
        }
        return {-1, -1};
    }
};


// -------------------------------
// Two Sum in a stream of Integers
// -------------------------------

class TwoSum {
  private: 
    unordered_map<long long int,long long int> mp;  
  
  public:
  TwoSum() {
  }

  // Add the number to the map & increase its freq by 1
  // O(1)
  void add(int number) {
      mp[number]++;
  }

  // Find if there exists any pair of numbers which sum is equal to the value. 
  // O(n)
  bool find(int value) {

    for(auto i : mp){
        int complement = value-i.first;
        if (mp.count(complement)){
            // If the value and its complement are same, the freq must be atleast 2
            if(complement == i.first){ 
                if(i.second > 1)
                    return true;
                else
                    continue;
            }
            return true;
        }
    }
    return false;
  }

};

// -----------------------
// Max Two Sum Less than K
// -----------------------

// Approach 1: Sort the integers and use two pointers to see the maximum sum < k
// TC: O(nlogn), SC: O(nlogn) whatever sort uses
class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int left =0, right= nums.size()-1;
        int max_sum = 0; // less than k
        while(left < right){
            int sum =  nums[left]+nums[right];
            if(sum < k){
                max_sum = max(sum, max_sum);
                left++;
            }
            else {
                right--;
            }
        }
        return max_sum == 0 ? -1 : max_sum;
    }
};

// Approach 2: Counting Sort (Elements are from 1 to 1000 so using this property)
// TC: O(n+m) where m is the range (here 1000), SC: O(m)
class Solution {
public:
    int twoSumLessThanK(vector<int>& nums, int k) {
        vector<int> count(1001, 0);
        for(auto n: nums)
            count[n]++;
        int answer = -1;
        int left = 1, right = 1000;
        while(left <= right){
            int sum = left+right;
            if( sum >= k || count[right] == 0)
                right --;
            else {
                if(left == right){
                    // coz the element has to be present twice now
                    if(count[left] > 1) 
                        answer = max(answer, sum);
                }
                else if (count[left] > 0){
                        answer = max(answer, sum);
                }
                left++;
            }
        }
        return answer;
    }
};


// -------------------
// Two Sum in two BSTs
// -------------------
// TC: O(n1+n2) n1, n2 nodes in two trees
// SC: O(n1+n1+n2) n1 for hashset, n1+n2 for recursive stack
class Solution {
public:
    unordered_map<int, int> map;
    
    // Traverse the first tree, and store the complements (target - val) 
    // of all node values in a hashset.
    void fillMap(TreeNode* node, int target){
        if(node == NULL)
            return;
        fillMap(node->left, target);
        map[target-(node->val)]++;
        fillMap(node->right, target);
    }
    
    // Traverse the second tree and check if any of its elements exists in the hashset. 
    // If yes - return True. If no - return False.
    bool checkForElements(TreeNode* node){
        if(node == NULL)
            return false;
        return map.count(node->val) || checkForElements(node->left) || checkForElements(node->right); 
    }
    
    bool twoSumBSTs(TreeNode* root1, TreeNode* root2, int target) {
        fillMap(root1, target);
        return checkForElements(root2);
    }
};

// ------------------------
// Two Sum - Input is a BST
// ------------------------
// TC: O(n), SC: O(n)

class Solution {
public:
    unordered_map<int, bool> map;
    
    bool traverse(TreeNode* root, int k){
        if(root == NULL)
            return false;
        if(map.count(k-(root->val)))
            return true;
        map[root->val] = true;
        return findTarget(root->left, k) || findTarget(root->right, k);
    }
    
    bool findTarget(TreeNode* root, int k) {
        return traverse(root, k);
    }
};


// ----------------------------------------------------------------------
// Count sum of all Pairs of Integers in arr which add up to a power of 2
// ----------------------------------------------------------------------
// TC: O(22n)
class Solution {
public:
    
    // 1 2 4 8 16 32 64 128 256 512 1024 2048 4096 8192 16384 32768 65536 131072 262144 524288 1048576 
    int countPairs(vector<int>& arr) {
        int mod = 1000000007;
        unordered_map<int, int> map;
        int ans=0, n=arr.size();
        
        // Iterate over all the numbers.
        for(int i=0; i<n; i++){
            int power = 1;
            // Iterate 22 times for different powers of 2 from 2^0=1 till 2^21
            for(int j=0; j<22; j++){
                // Check if the difference of power of 2 and arr[i] exists in the map already
                // If it exists, then add the frequency
                if(map.count(power-arr[i])){
                    ans += map[power-arr[i]];
                    ans %= mod;
                }
                // Increase the power by 2X so that the loop checks for the next pow of 2
                power*=2;
            }
            // Increment the freq of arr[i] in map now.
            // By doing this now, we are not counting the pairs twice EX: (1,3) and (3,1) for power=4
            // When arr[i] = 1, then 3 was not present in map so pow=4, it will say Not present in map.
            // When arr[i] = 3, and pow=4, then it will say that map[4-3] is present already ans inc by 1.
            map[arr[i]]++;
        }
        return ans;
    }
};