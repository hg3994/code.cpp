
/*

Harshit Gupta | 1st June, 2021
---------------------------------

C++ program for "Convert a Decimal Integer to Roman Form"
https://leetcode.com/problems/integer-to-roman/
------

Solution: Explained below. Using recursion.

Time Complexity: O(n)
Space Complexity:

Paradigm: Recursion
---
  NOTE: 

*/


class Solution {
public:
    // A vector of already known pairs...
    vector<pair<int,string>> imp = {{1,"I"},{4,"IV"},{5,"V"},{9,"IX"},{10, "X"},{40,"XL"},{50,"L"},
        {90,"XC"},{100,"C"},{400,"CD"},{500,"D"},{900,"CM"},{1000,"M"},{4000,"MMMM"}};
    
    
    // This will actually convert a num to roman
    string roman(int num){
        string a;
        // Search for a lower bound value of the num and call the function again for the difference to be converted
        for(int i=0;i<imp.size(); i++){
            // if the number's coversion is already available return it.
            if(imp[i].first == num){
                return imp[i].second;
            }
            // If the number has larger, then take the last value and get the string form of it.
            // Get the roman for the remaining difference...
            if(imp[i].first > num){
                a = imp[i-1].second;
                if(num-imp[i-1].first != 0){
                    a += roman(num-imp[i-1].first);
                }
                return a;
            }
        }
        return "can never come here";
    }
    
    string intToRoman(int num) {
        string s;
        
        // This will store the value for the power of 10. How much pow of 10 should we take. It will keep increasing in every iteration
        int p = 0;
        // We'll convert the numbers in pieces. For eg., 217 -> 7 then 10 then 200 and then append them to form the final string.
        // The only trick comes up when it ends with 0 e.g., 210 -> 10 then 200 , 3400 -> 400 , then 3000
        // Till the number becomes 0, keep converting...
        while(num!=0){
            // Get the unit digit number & remove it in next line
            int rem = num%10;
            num = num/10;
            // If remainder is 0, we cant call roman on it since it will evaludate to 0 and there's no conversion of 0 in roman. We ignore it.
            if(rem == 0){
                p++;
                continue;
            }
            // Convert the num to roman and prepend it in ans;
            s = roman(rem*pow(10,p))+s;
            p++;
        }
        return s;
    }
};