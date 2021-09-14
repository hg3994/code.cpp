
/*

Harshit Gupta | 14th August, 2021
---------------------------------

Problem Statement:
	We are given an array asteroids of integers representing asteroids in a row.
	For each asteroid, the absolute value represents its size, and the sign represents its direction 
		(positive meaning right, negative meaning left). Each asteroid moves at the same speed.

	Find out the state of the asteroids after all collisions. If two asteroids meet, the smaller one will explode. 
	If both are the same size, both will explode. Two asteroids moving in the same direction will never meet.


Example 1:
	Input: asteroids = [5,10,-5]
	Output: [5,10]
	Explanation: The 10 and -5 collide resulting in 10. The 5 and 10 never collide.

Example 2:
	Input: asteroids = [8,-8]
	Output: []
	Explanation: The 8 and -8 collide exploding each other.

Example 3:
	Input: asteroids = [10,2,-5]
	Output: [10]
	Explanation: The 2 and -5 collide resulting in -5. The 10 and -5 collide resulting in 10.

Example 4:
	Input: asteroids = [-2,-1,1,2]
	Output: [-2,-1,1,2]
	Explanation: The -2 and -1 are moving left, while the 1 and 2 are moving right. Asteroids moving the same direction never meet, so no asteroids will meet each other.


https://leetcode.com/problems/asteroid-collision/
------

Solution: 
		1. There are few things to think about. What are the cases.. When there will be collision.. When not.. What happens when there is a collision
		2. Putting all the cases together:
					
			10   5   : push a[i] in ans (same direction)
			5    10  : push a[i] in ans (same direction)
			-10  5   : push a[i] in ans (opp direction, never gonna hit)
			-5   10  : push a[i] in ans (opp direction, never gonna hit)
			-5   -10 : push a[i] in ans (same direction)
			-10  -5  : push a[i] in ans (same direction)
			5    -10 : collision, ans.pop_back() & start again with new ans.back()
			10   -5  : collision, discard a[i]

			5    5   : push a[i] in ans
			5    -5  : collision, discard a[i] & ans.pop_back() both
			-5   5   : push a[i] in ans
			-5   -5  : push a[i] in ans

		3. Only three cases need to handled differently, rest are fine with just ans.push_back(a[i])

			Case 1: 	5    -10 : collision, ans.pop_back() & start again with new ans.back()
			Case 2: 	5    -5  : collision, discard a[i] & ans.pop_back() both
			Case 3: 	10   -5  : collision, discard a[i]

		4. All the three cases are when and.back() > 0 && a[i] < 0, then we check the sizes for separate cases (Case 1,2,3).
		5. Case 3 need not be handled since not handling it will do nothing and eventually it will discard a[i]
		6. If you think of ans, we are using it as a stack since we push and pop from the back. Using a stack for intermediate results
			will use extra memory.
    
    Time Complexity: O(N), where N is the number of asteroids. Our stack pushes and pops each asteroid at most once.
	Space Complexity: O(1) for Approach 1 (since not stack is used)
					  O(N). We use a stack to keep track of the intermediate results. In the worst case, the states do not 
					  	evolve at the end, i.e. we need O(N) space where N is the number of input asteroids.


Paradigm: Stack
---
    NOTE: 
    	1. Asked in Flipkart.

    Similar Questions:
        1.

*/



// Approach 1: Using a vector and use it as a Stack.
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        if(asteroids.size() == 0)
		    return {};
        
        vector<int> ans= {asteroids[0]};
        int n = asteroids.size();
        
        for(int i=1; i<n; i++){
            
            // If the two stones are collideable
            if(ans.size()>0 && (ans.back()>0 && asteroids[i]<0) ){
                
                // Case 1: If asteroid size > ans back size, they will collide & we keep colliding.
                if(abs(asteroids[i]) > abs(ans.back())){
                    ans.pop_back();
                    i--; // so that again the same check happens for the same asteroid[i]
                }
                // Case 2: If asteroid size == ans back size, they will collide & both will be discarded
                else if(abs(asteroids[i]) == abs(ans.back())){
                    ans.pop_back();
                }
            }
            // If they are not collideable, we just push it in the ans.
            else {
                ans.push_back(asteroids[i]);
            }
        }
        return ans;
    }
};


// Approach 2: Using a stack
class Solution {
public:
    vector<int> asteroidCollision(vector<int>& asteroids) {
        if(asteroids.size() == 0)
		    return {};
        
        vector<int> ans;
        stack<int> st;
        st.push(asteroids[0]);
        int n = asteroids.size();
        
        for(int i=1; i<n; i++){
            
            // If the two stones are collideable
            if(st.size()>0 && (st.top()>0 && asteroids[i]<0) ){
                
                // If asteroid size > st pop size, they will collide & keep colliding.
                if(abs(asteroids[i]) > abs(st.top())){
                    st.pop();
                    i--; // so that again the same check happens for the same asteroid
                }
                // If asteroid size == st pop size, they will collide & both will be discarded
                else if(abs(asteroids[i]) == abs(st.top())){
                    st.pop();
                }
            }
            // If they are not collideable, we just push it in the st.
            else {
                st.push(asteroids[i]);
            }
        }
        while(!st.empty()){
            ans.push_back(st.top());
            st.pop();
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};