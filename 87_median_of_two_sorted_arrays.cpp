
/*

Harshit Gupta | 22nd May, 2021
---------------------------------

C++ program for "Median of two sorted Arrays"
https://leetcode.com/problems/median-of-two-sorted-arrays/
https://www.youtube.com/watch?v=LPFhl65R7ww
------

Solution: 
    1. Traverse both sorted arrays to create another sorted-merged array. 
        Choose the middle element from it to calculate the median

    Time Complexity: O(n)
    Space Complexity: O(n)

    2. Using Binary Search find appropriate cuts in both arrays X and Y such that 
        - The LEFT[X,Y] and RIGHT[X,Y] created. All elements in LEFT <= All elements in RIGHT 
        - The elements in LEFT[] =~ Elements in RIGHT[]

        More explanation below

    Time Complexity: O(logn)
    Space Complexity: O(1)

---
  NOTE: 

*/




class Solution {
    
    // We want to find a CUT in both vectors such that 
    //  - All elements towards the left of the CUT <= All elements towards the right of the CUT
    //  - Number of Elements in LEFT ~= Number of Elements in RIGHT (For odd cases, LEFT has 1 more)
    
    // nums1: [1,3,8,9,15] , nums2: [7,11,18,19,21,25], x:length of nums1, y: length of nums2
    // The CUT/PARTITION we want to find in both arrays are:
    // nums1: [1,3,8,9 , 15] , nums2: [7,11 , 18,19,21,25]
    //                 |                    |  
    // ARRAY ON LEFT: [1,3,8,9] + [7,11] <  ARRAY ON RIGHT [15]+[18,19,21,25]
    // The only tough job now is to know both the cuts and then we can find the median by looking 
    // and analyzing the 4 important elements 9, 11, 15, 18 and the length (odd/even)
    
    // To find the CUTS:
    // We iterate over the smaller length array and choose the middle as the CUT ((0+x)/2)
    // Considering the length of it, we find the CUT in nums2[] as well (x+y+1)/2 - CUTX
    //      Total length / 2 - Cut X  -- would make a cutY such that # elements in LEFT ~= # elements RIGHT
    // Now consider the 4 important elements
    //      - For nums1: LEFT Arrays's MAX element : leftX
    //      - For nums1: RIGHT Arrays's MIN element : rightX
    //      - For nums2: LEFT Arrays's MAX element : leftY
    //      - For nums2: RIGHT Arrays's MIN element : rightY
    // leftX <= RightY && leftY <= RightX and then we are sure that the CUT is PERFECT! (Ex: Above)
    
        // If leftX > RightY, it means we are far ahead and the CUT should be a bit before (towards left)
        // Ex: X: [10,20 , 30,40], Y: [1,2 , 3,4]
        //               |                |
        // leftX: 20, RightY: 3 => So we want to move the CUT in X towards left, obviously to maintain the length
        // the CUT in Y will move towards right automatically.

        // If leftY > RIghtX, it means we are far behind and the CUT should be a bit further in X (towards right)
        // and obviously the CUT in Y would move towards the left
        // Ex: X: [1,3 , 8,9,15] , Y: [7,11,18,19 , 21,25], x:length of nums1, y: length of nums2
        //             |                          |
        // RightX: 8, leftY: 19 => So we want to move the CUT in X towards the right.
    
    // Once the CUTS are known, we can find the median like this:
    // If the array length is odd: LEFT[] has one more element than RIGHT[]
    //      median = max(LeftX,leftY)
    // If the array length is even: LEFT[] and RIGHT[] are equal length.
    //      median: AVERAGE OF max(LeftX, LeftY) , min(RightX,RightY)
    
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {   
        // In case the size of the firsy array is smaller, call again by interchanging the vectors.
        // We want nums1 to be smaller. This way we will achieve complexity of O(log(min(x,y))
        // otherwise it will be O(log(x/y)) (NOT THE MIN)
        if (nums1.size() > nums2.size()){
            return findMedianSortedArrays(nums2, nums1);
        }
        int x = nums1.size();
        int y = nums2.size();     
        
        
        // These two pointers will keep the while loop running till we find the accurate CUT in X and Y
        int low = 0;
        int high = x;
        
        while(low <= high){
            // Find the Partition in X & Y
            int partX = (low+high)/2;
            int partY = (x+y+1)/2 - partX;
            
            // In array X, after the partition we chose PartX, Get the values of LeftX & RightX
            // If we are at a cliff edge, choose INT_MIN oR INT_MAX
            int LeftX = (partX==0)? INT_MIN : nums1[partX-1];
            int RightX = (partX==x)? INT_MAX : nums1[partX];
            
            // In array Y, after the partition we chose PartY, Get the values of LeftY & RightY
            // If we are at a cliff edge, choose INT_MIN oR INT_MAX
            int LeftY = (partY==0)? INT_MIN : nums2[partY-1];
            int RightY = (partY==y)? INT_MAX : nums2[partY];
            
            // If the Partitions are perfect, we calculate the MEDIAN and return!
            if (LeftX <= RightY && LeftY <= RightX){
                if( (x+y)%2 == 0){
                    return (double) (max(LeftX, LeftY)+min(RightX,RightY))/2;
                }
                else{
                    return (double) max(LeftX, LeftY);
                }
            }
            // Partitions were not correct, we need partX to move a bit towards the left
            else if (LeftX > RightY){
                high = partX-1;
            }
            // Partitions were not correct, we need partX to move a bit towards the right
            else{
                low = partX+1;
            }
        }
        // Flow never reaches here if the vectors are sorted. It must have a VALID CUT!
        return -1;
    }
};