=begin 

Harshit Gupta | 19th September, 2020
-------------------------------------

Ruby program for "Best Time to Buy and Sell Stock to make most profit"
Say you have an array for which the ith element is the price of a given stock on day i.
If you were only permitted to complete at most one transaction (i.e., buy one and sell one share of the stock), design an algorithm to find the maximum profit.


https://leetcode.com/problems/best-time-to-buy-and-sell-stock/

Solution: In formal terms, we need to find max({prices[j]} - {prices[i]}), for every i and j such that j > i.
	We can obviously use Brute Force to get all combinations of price differences and that would give us the max profit. Time Complexity: O(n2)
	---
	A better solution is to loop (for every i from 0:n) and:
	- Calculate miniumum value of the stock till now (0 to i)
	- Calculate the maximum profit value of the stock till now (0 to i)
	
	Profit each day would be the difference of the stock value and minimum value till now
	Maximum Profit would be the maximum of all such numbers

	If we keep on calculating this "maximum profit till now", then this number at the end of the array
		would give us "most money one could make"

https://repl.it/repls/OurDirtyBytecode

=end

def max_profit(prices)

	# initialize the variables
  min_price_till_now = prices[0]
  max_profit_till_now = 0
  
  # iterate over all the stock prices from day 1 to day n.
  prices.each do |p|

  	# Calculate the minimum price of the stock from day 1 till now.
    if p < min_price_till_now
        min_price_till_now = p 
    end

    # Calculate the maximum profit till now.
    # p-min_price_till_now = profit made today and if that is greater than maximum profit we made till today,
    #                        update that number to the profit we made today
    if (p-min_price_till_now) > max_profit_till_now
        max_profit_till_now = p-min_price_till_now
    end

  end

  return max_profit_till_now
end


result = max_profit [7,1,5,3,6,4]
puts result			# 5   Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit = 6-1 = 5.
             		# 		Not 7-1 = 6, as selling price needs to be larger than buying price.

