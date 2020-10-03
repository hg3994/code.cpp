=begin 

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

Solution: The solution to the problem comes in 4 steps:
  - Find the largest index i such that arr[i-1] >= arr[i] (0125330 -> 012'5'330, a[i]->5)
  - If no such i exists, 
    - Then the array is already sorted decending. We just need to reverse (321 -> 123)
  - Else
    - Finding the largest index j such that j>=i and arr[j]>=arr[i-1] (01'2'5330 -> 01253'3'0, a[i-1]=2, a[j]=3)
    - Swap arr[j] and arr[i-1] (0125330 -> 0135320)
    - Reverse the suffix since we want the next perm, so it has to be the smallest (013|5320 -> 013|0235)

Time Complexity: O(n)
Space Complexity: O(1)


=end

def next_permutation(arr)
  i = arr.length-1
  
  # Find the largest index i (so we start from the back) such that arr[i-1] >= arr[i] 
  # 0125330, i would be index 3 (having 5) since 5>=3>=3>=0 but 2 ! >= 5, so stop at 5. (012'5'330)
  while(i > 0 && arr[i-1]>=arr[i])
    i-=1
  end
  
  # If no such i exists, then the array is already sorted. We just need to reverse (321 is next_perm of 123)
  if i==0
    arr.reverse!
  else
    # Finding the largest index j such that j>=i and arr[j]>=arr[i-1]
    # 0125330, j would be upper_bound(smallest greater) of 2 towards its right, we choose largest if they are multiple.
    # Here 3 is present in index 4 and 5, so we choose the 3 at index 5 (01253'3'0)
    j = arr.length-1
    while arr[j] <= arr[i-1]
      j-=1
    end
    
    # Swap arr[j] and arr[i-1], # 0125330 becomes 0135320
    arr[j], arr[i-1] = arr[i-1], arr[j]
    
    # Reverse the suffix since we want the next perm, so it has to be the smallest 013|5320 becomes 013|0235
    s = arr.slice(i, arr.length-i).reverse
    arr[i...arr.length] = s
  end
end

p next_permutation [3,4,2,1]
p next_permutation [2,1,4,3]