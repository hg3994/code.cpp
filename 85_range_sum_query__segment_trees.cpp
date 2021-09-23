
/*

Harshit Gupta | 19th May, 2021
---------------------------------

C++ program for 

    Given an integer array nums, handle multiple queries of the following types:
    - Update the value of an element in nums.
    - Calculate the SUM of the elements of nums between indices left and right inclusive where left <= right.

    Example 1:
    Input
    ["NumArray", "sumRange", "update", "sumRange"]
    [[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
    Output
    [null, 9, null, 8]

https://leetcode.com/problems/range-sum-query-mutable/
https://www.youtube.com/watch?v=ZBHKZF5w4YU

------

Solution: 
    1. One way to solve would simply be by a for loop and it will do the SUM in O(n) time and UPDATE in O(1) time.
    2. Another way would be solve using Segment Trees which would do the SUM in O(logn) and UPDATE in O(logn) time. 
        However, we will have to build a Segment Tree first which will require O(n) time.

    https://leetcode.com/problems/range-sum-query-mutable/solution/


    #SegmentTree #Segment #Trees #MergeSort

Time Complexity: Sum: O(logn), Update: O(logn)
Space Complexity: O(n) for the segment tree

---
  NOTE: 

  Similar Questions: 
    1. https://leetcode.com/problems/range-sum-query-immutable/
        - Calculate the sum of the elements of nums between indices left and right inclusive
        - No update query, only sum needs to queried.
        - We can pre-calculate the result since it wont ever change ina  prefix sum.

*/

// nums:[-1, 4, 2, 0]

// Segment Tree for the Above Array:

//      5                   [0,3]
//    /   \
//    3    2          [0,1]      [2,3]
//   / \   /\
// -1  4  2  0    [0,0] [1,1] [2,2] [3,3]

// Segment Tree Represented as: [5, 3, 2, -1, 4, 2, 0]
// Each node at 'k' can access their child at 2k+1, 2k+2
// Each node can access its parent at (k-1)/2

class NumArray {
public:
    // Check the constructor for the initialization of these variables.
    vector<int> seg; // Segment Tree to be stored in a vector.
    int n; // Length of the segment tree vector. 
    

    // Function to build the Segment Tree
    // This function will fill up the child values first
    // (left == right) will satisfy for the leaf values and they will be updated in segment tree
    // seg[pos]=seg[2*pos+1]+ seg[2*pos+2]; -> This will help populate all other intermediate nodes
    // as well as the root node with the "sum" of their child nodes.
    // Finally we have a segment tree which has all 'nodes' with sum values of their child.
    void buildTree(vector<int>& nums, int pos, int left, int right){
        if (left == right){
            seg[pos] = nums[left]; 
            return;
        }
        int mid = (left+right)/2;
        buildTree(nums, 2*pos+1, left, mid);
        buildTree(nums, 2*pos+2, mid+1, right);
        seg[pos]=seg[2*pos+1]+ seg[2*pos+2];
    }

    // Function to update a node in the segment tree
    // When a node is updated, then the change in the node value has to be propagated to the root
    // left, right -> represents the range of the node of segment tree. (Ex: [0, n-1] -> root)
    // pos       -> represents "position" in the segment tree data structure (Ex: 0 -> root)
    // Using left, right and pos -> we have all the information on the segment tree
    // Node at 'pos' in segment tree will have children at 2pos+1(left) and 2pos+2(right)

    // If index is less than left or more than right, then it is out of bound 
    //      for this node's range so we ignore it and return (This makes the algo O(logn))
    // If left==right==index, then we found the index, 
    //      update the value of the segment tree node & return
    // Otherwise, we need to find the index and we do this by checking child nodes (2pos+1, 2pos+2)
    //      update the segment tree pos with the updated child values' sum.
    //      This would help propagate the updated value of the chid indexes to the parent (through recursion)
    void updateUtil(int pos, int left, int right, int index, int val) {
        // no overlap
        if(index <left || index >right) return;
        
        // total overlap
        if(left==right){
            if(left==index)
                seg[pos]=val;
            return;
        }

        // partial overlap
        int mid=(left+right)/2;
        updateUtil(2*pos+1,left,mid,index,val); // left child
        updateUtil(2*pos+2,mid+1,right,index,val); // right child
        seg[pos]=seg[2*pos+1]+seg[2*pos+2];
    }

    // Function to get the sum from the range [qlow, qhigh]
    // low, high -> represents the range of the node of segment tree. (Ex: [0, n-1] -> root)
    // pos       -> represents "position" in the segment tree data structure (Ex: 0 -> root)
    // Using low, high and pos -> we have all the information on the segment tree
    // Node at 'pos' in segment tree will have children at 2pos+1(left) and 2pos+2(right)
    
    // While searching for the range, there will be three cases: (Ex: arr: [-1, 4, 2, 0])
    //  - Total Overlap:    Return the value. (Ex: qlow, qhigh: 0,3 and low, high: 1,2)
    //  - No Overlap:       Return 0. (Ex: qlow, qhigh: 0,1 and low, high: 2,3)
    //  - Partial Overlap:  Search for it in both the child nodes and their ranges.
    //                      (Ex: Searching for 1,2 and node range is 0,1)
    int rangeUtil(int qlow, int qhigh, int low, int high, int pos){
        if (qlow <= low && qhigh>= high){ // total overlap
            return seg[pos];
        }
        if (qlow > high || qhigh < low) { // no overlap
            return 0;
        }
        // partial overlap
        int mid = low+(high-low)/2;
        return (rangeUtil(qlow, qhigh, low, mid, 2*pos+1) + rangeUtil(qlow, qhigh, mid+1, high, 2*pos+2));
    }
    
    // Constructor for initializing the variables.
    NumArray(vector<int>& nums) {
        if(nums.size() > 0){
            n = nums.size();
            seg.resize(4*n,0);  // Maximum size of a segment tree for an array of size n is 4n
            buildTree(nums, 0, 0, n-1); // Build the segment tree
            // Print Segment Tree
            // for(int i=0;i<4*n;i++)
            //     cout<<seg[i]<<" ";
            // cout<<endl;
        }
    }
    
    // Update the segment Tree recurively using updateUtil
    void update(int index, int val) {
        if(n==0)return;
        updateUtil(0,0,n-1, index, val);
    }
    
    // Get the sum for a specific range for the segment Tree
    int sumRange(int left, int right) {
        if(n==0)return 0;
        return rangeUtil(left, right, 0, n-1, 0); 
        // query from left to right while segment tree is now at 'root' (pos=0) and range(0, n-1)
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

// ------------------------------------------------------------------------

// ------------------
// SIMILAR QUESTION 1
// ------------------

// Approach 2: Prefix Sum
// Time complexity : O(1) time per query, O(n) time pre-computation. Since the cumulative sum is cached, each sumRange query can be calculated in O(1) time.
// Space complexity : O(n) for prefixSum
// Runtime: 16ms
class NumArray {
public:
    vector<int> prefixSum;
    NumArray(vector<int>& nums) {
        prefixSum.resize(nums.size()+1, 0);
        for(int i=0; i<nums.size(); i++)
            prefixSum[i+1] = prefixSum[i]+nums[i];
    }
    
    int sumRange(int left, int right) {
        return prefixSum[right+1] - prefixSum[left];
    }
};


/*
    Approach 1: Normal Addition
    Time complexity : O(n) time per query. Each sumRange query takes O(n) time.
    Space complexity : O(1). Note that data is a reference to nums and is not a copy of it.
    Runtime: 270ms
*/

class NumArray {
public:
    vector<int> v;
    NumArray(vector<int>& nums) {
        v = nums;
    }
    
    int sumRange(int left, int right) {
        int ans=0;
        for(int i=left; i<=right; i++)
            ans += v[i];
        return ans;
    }
};
