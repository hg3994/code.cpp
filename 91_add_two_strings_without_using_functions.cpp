
/*

Harshit Gupta | 25th May, 2021
---------------------------------

C++ program for "Add two numbers in string format into another String without using any library function"
	Input: num1 = "11", num2 = "123"
	Output: "134"

https://leetcode.com/problems/add-strings/
------

Solution: Keep calculating the carry after each small sum and add it in the next round.

Time Complexity: O(m+n)
Space Complexity: O(1)

---
  NOTE: BOTH THE WHILE LOOPS CAN BE MERGED INTO ONE BUT I HAVE KEPT BOTH OF THEM JUST FOR THE SAKE OF BETTER READABILITY AND UNDERSTANDING!


*/

class Solution {
    
    //  1 1
    //  9 5 6
    //    7 7
    // ------
    // 10 3 3
    
public:
    string addStrings(string num1, string num2) {
        
        // Check to make sure that num1 has more digits than num2
        if (num1.size() < num2.size()){
            return addStrings(num2, num1);
        }
        
        int i=num1.size()-1; // iterator for num1 from last character till first
        int j=num2.size()-1; // iterator for num2 from last character till first
        
        string ans;
        int carry=0;
        
        // Only check for j>=0 (j's first character) since num2 is smaller digited than num1
        while(j>=0){
            
            // Get the sum of the digits
            int sum = (int)num1[i]-'0'+(int)num2[j]-'0'+carry;
            // Update the string with the sum%10 (for a sum with 2 digits: it will only concatenate the last digit only, for signle digit it will concatenate the only digit)
            ans += to_string(sum%10);
            // Update the carry (for two digited sum, it will find the carry and add, for single digit sum, carry becomes 0)
            carry = sum/10;
            
            // Move toward front
            i--; j--;
        }
        
        // Now we know that num2 is done, we just have to keep summing carry and num1 to get the result
        while(i>=0){
            int sum = (int)num1[i]-'0'+carry;
            ans += to_string(sum%10);
            carry = sum/10;
            i--;
        }
        
        
        // If there is a carry remaining in the end, add that as well
        if(carry){
            ans =ans+to_string(carry);
        }
        
        // Since we have been creating the string in reverse order, we reverse to get the actual output.
        reverse(ans.begin(), ans.end());
        return ans;
        
    }
};


// ------------------
// ONE LOOP SOLUTION 
// ------------------

class Solution {
    
    //  1 1
    //  9 5 6
    //    7 7
    // ------
    // 10 3 3
    
public:
    string addStrings(string num1, string num2) {
        string ans;
        
        int carry = 0;
        int p1 = num1.length() - 1;
        int p2 = num2.length() - 1;
        while (p1 >= 0 || p2 >= 0) {
            int x1 = p1 >= 0 ? num1[p1]-'0': 0;
            int x2 = p2 >= 0 ? num2[p2]-'0': 0;
            int value = (x1 + x2 + carry) % 10;
            carry = (x1 + x2 + carry) / 10;
            ans += to_string(value);
            p1--;
            p2--;  
        }
        
        if (carry != 0)
            ans += to_string(carry);
        
        reverse(ans.begin(), ans.end());
        return ans;
    }
};