=begin 

Harshit Gupta | 28th September, 2020
-------------------------------------

Ruby program for "You are given equations in the format A / B = k, where A and B are variables represented as strings, and k is a real number (floating-point number). 
	Given some queries, return the answers. If the answer does not exist, return -1.0."

https://leetcode.com/problems/evaluate-division/

Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
Explanation: 
Given: a / b = 2.0, b / c = 3.0
queries are: a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
return: [6.0, 0.5, -1.0, 1.0, -1.0 ]
------

Solution: 


Time Complexity: O(m.n) ('m' being number of queries, 'n' is number of input eq.)
Space Complexity: O(n)


=end


def calc_equation(equations, values, queries)
  h = {}
  
  # Building the graph from equations
  equations.each_with_index do |e, i|
    dividend = e[0]
    divisor = e[1]
    quotient = values[i]
    h[dividend] ||={}
    h[divisor] ||={}
    h[dividend][divisor] = quotient
    h[divisor][dividend] = 1/quotient
  end
  
  # Evaluate each query via backtracking (DFS)
  # Verify if there exists a path from dividend to divisor 
  results = []
  queries.each_with_index do|q, i|
    dividend = q[0]
    divisor = q[1]
    if (h[dividend] == nil || h[divisor] == nil)
      results[i] = -1.0
    elsif dividend == divisor
      results[i] = 1.0
    else
      visited = {}
      results[i] = backtrack_evaluate(h, dividend, divisor, 1, visited)
    end
  end
  return results
end


def backtrack_evaluate h, current_node, target_node, accumulated_product, visited
  # puts "backtrack: #{h}, current_node: #{current_node},  target_node: #{target_node}, ap: #{accumulated_product}, v: #{visited}"
  visited[current_node] = true
  ret = -1.0
  
  neighbors = h[current_node]
  if (neighbors[target_node] != nil)
    ret = accumulated_product * neighbors[target_node]
    # puts "ret: #{ret}"
  else
    neighbors.each do |k, v|
      if visited[k]
      else
        ret = backtrack_evaluate h, k, target_node, accumulated_product * v, visited
        if ret != -1.0
          break
        end
      end
    end
  end
    
  visited.delete(current_node)
  return ret
end

# Input: equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
# Output: [6.00000,0.50000,-1.00000,1.00000,-1.00000]
calc_equation [["a","b"],["b","c"]],  [2.0,3.0], [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
