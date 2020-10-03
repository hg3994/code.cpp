=begin 

Harshit Gupta | 21st September, 2020
-------------------------------------

Ruby program for "Add two numbers (in LL) to create another LL having its sum"
You are given two non-empty linked lists representing two non-negative integers. 
The digits are stored in reverse order and each of their nodes contain a single digit. Add the two numbers and return it as a linked list.
You may assume the two numbers do not contain any leading zero, except the number 0 itself.

https://leetcode.com/problems/add-two-numbers/

Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 0 -> 8
------
Explanation: 342 + 465 = 807.

Solution: 

  We calculate the numbers in the given Linked lists with help of recursion. 
  The numbers are stored in reverse order and so we can use the position of node(level) to create the number.
  We have the level of each node and then we multiply the number in node with 10^level to get the actual number.
    2 -> 4 -> 3
    2*(0^10) + 4*(1^10) + 3 (2^10)
    2 + 40 + 300
    342

  We just have to create a new List with the number as SUM of two numbers in reverse order.
  - We will do num%10 to get the unit digit and then create a node.
  - We will get the remaining number by removing the unit digit and then dividing the number by 10 (num = num - num%10 ; num = num / 10)
  - We do the same thing with the remaining number.
    807
    7 + 00 + 800
    7*(0^10) + 0*(1^10) + 8*(2^10)

  We keep maintaining the list through recursion and then finally send it to main()

https://repl.it/repls/PoisedVisibleApplicationpackage#main.rb

=end


# Definition for singly-linked list.
class ListNode
  attr_accessor :val, :next
  def initialize(val = 0, _next = nil)
    @val = val
    @next = _next
  end
end

# Calculate the number from the list
def calculate_num l, level
  # Till the end of the LL
  if l.next != nil
    # prev num + my own evaluation
    return (calculate_num l.next, level+1)+(l.val*(10**level))
  else
    # this would be reached only by the last node
    return l.val*(10**level)
  end
end

# Create a LL from a number
def create_list num, l

  # Ensure that the number is still valid
  if num%10 != nil
    # Create a new node
    l_new = ListNode.new num%10, nil

    # l is nil for the first iteration from parent calling function.
    if l==nil
      # it does not have a "next" so assign the new node to l. This is the first node.
      l = l_new
    else
      # for all other nodes, attach the new node to the last of the LL
      l.next = l_new
    end
    
    # Since a node with num%10 is already created and attached, remove that and get the remaining number.
    num = num - num%10
    num = num / 10

    # If the num is 0, then everything is already done. The list L is created.
    if num == 0
        return l
    else
        # Create the remaining nums, sending the new node because it has already a link to L and 
        # in the next iteration, l_new.next should attach more stuff (if any...)
        create_list num, l_new
        return l
    end
  end
end


def add_two_numbers(l1, l2)
  # Get the actual number from the list above (should obviously be the nums we created)
  n1 = calculate_num(l1, 0)
  n2 = calculate_num(l2, 0)

  # create a list of the sum.
  result_list = create_list n1+n2, nil

  return result_list
end


# Given these two lists in the question
l1 = create_list 342, nil
l2 = create_list 465, nil
r1 = add_two_numbers l1,l2

puts r1.inspect # #<ListNode:0x0000555e8972fb90 @val=7, @next=#<ListNode:0x0000555e8972fb40 @val=0, @next=#<ListNode:0x0000555e8972fac8 @val=8, @next=nil>>>
