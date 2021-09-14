/*

Harshit Gupta | 28th September, 2020
-------------------------------------

Ruby program for "You are given equations in the format A / B = k, where A and B are variables represented 
  as strings, and k is a real number (floating-point number). 
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
    1. Weighted Graph and product of path between two nodes
        1. We could reformulate the equations with the graph data structure, where each variable
             can be represented as a node in the graph, and the division relationship between
             variables can be modeled as edge with direction and weight.
        2. The direction of edge indicates the order of division, and the weight of edge 
             indicates the result of division.
        3. Example:  a/b=2, b/c=3
                  a/b=2     b/c=3
               a-------->b-------->c
               a<--------b<--------c
                 b/a=1/2   c/b=1/3
        4. In the above example, for finding a/c we could find a path between them, we can conclude 
            that the result of a/c is 2*3=6 
        5. We can reinterpret the problem as "given two nodes, we are asked to check if there exists a 
            path between them. If so, we should return the cumulative products along the path as the result."
        6. Special Case 1: If the nodes does not exists, then no path exist
           Special Case 2: If the origin and destination are same node, then a/a=1, so return 1.

    TC: O(MN)
        First of all, we iterate through the equations to build a graph. Each equation takes O(1) time 
            to process. Therefore, this step will take O(N) time in total.
        For each query, we need to traverse the graph. In the worst case, we might need to traverse 
            the entire graph, which could take O(N). Hence, in total, the evaluation of queries could 
            take O(M⋅N).
    SC: O(N): graph, Visited, Backtracking recursion all take O(n) space.
    
    ----

    2. Union Find:
        1. TODO: Do this from the link if you get some time.

*/

// Approach 1: Weighted Graph and product of path between two nodes
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        
        // 1. Build the Weighted Graph(map of map) from equations
        // Graph: {a: {b: 2}, b: {a: 0.5, c: 3}, c: {b: 0.33}}
        unordered_map<string, unordered_map<string, double>> graph;
        
        for(int i=0; i<equations.size(); i++) {
            vector<string> equation = equations[i];
            string dividend = equation[0];
            string divisor = equation[1];
            double quotient = values[i];
            
            unordered_map<string, double> inmap;
            if(!graph.count(dividend))
                graph[dividend] = inmap;
            if(!graph.count(divisor))
                graph[divisor] = inmap;
            
            graph[dividend][divisor] = quotient;
            graph[divisor][dividend] = 1/quotient;
        }
        
        // 2. Evaluate each query by DFS by checking if there exists a path from dividend to divisor
        vector<double> results(queries.size());
        for(int i=0; i<queries.size(); i++){
            vector<string> query = queries[i];
            string Qdividend = query[0];
            string Qdivisor = query[1];
            // Special Case 1: No nodes exist
            if(!graph.count(Qdividend) || !graph.count(Qdivisor))
                results[i] = -1.0;
            // Special Case 2: Dividend and Divisor are same.
            else if (Qdividend == Qdivisor)
                results[i] = 1.0;
            else {
                unordered_set<string> visited;
                results[i] = backtrackEvaluate(graph, Qdividend, Qdivisor, 1, visited);
            }
        }
        return results;
    }
    
    // This function looks for the targetNode in the neighbours of the currentNode
    // If the targetNode is a neighbour of the currentNode, return the accumulated Product
    // Else for each neighbour, do the same thing by calling this function.
    double backtrackEvaluate(unordered_map<string, unordered_map<string, double>>& graph, string& currentNode, string& targetNode, double accProduct, unordered_set<string>& visited) {
        
        // Mark the current Node visited
        visited.insert(currentNode);
        
        double ret = -1.0;
        unordered_map<string, double> neighbours = graph[currentNode];
        
        // If the target node is an adjacent node of the currentNode, then return the product
        if(neighbours.count(targetNode)){
            ret = accProduct * neighbours[targetNode];
        }
        // Else Look for the target node in all the neighbours one by one, if they are visited, skip it
        // Otherwise call the same function with the updated product on the neighbour node.
        else {
            for(auto n: neighbours){
                string Nnode    = n.first;
                double Nweight  = n.second;
                if(visited.count(Nnode))
                    continue;
                ret = backtrackEvaluate(graph, Nnode, targetNode, accProduct*Nweight, visited);
                if(ret != -1.0)
                    break;
            }
        }
        
        // Remove from the visited array
        visited.erase(currentNode);
        return ret;
    }
};