
/*

Harshit Gupta | 1st July, 2021
---------------------------------

C++ program for "FLAMES Game"

Name1: elizabetha
Name2: alexander

Common Letters: a, e, l
Remaining Letters: x,n,d,r,i,z,b,t,h = 9
F L A M E S F L A  M  E  S
1 2 3 4 5 6 7 8 9 10 11 12

9 is A= Affection so return it

https://ideone.com/ObYTYO
------

Solution: 

TC: O(n)
SC: O(n)

Paradigm: Set
---
  NOTE: Agoda

*/

#include <bits/stdc++.h>
using namespace std;

string flamescalculator(string s1, string s2){
	unordered_map<int, string> flames_map = {
		{0, "frienship"},
		{1, "love"},
		{2, "Affection"},
		{3, "Marriage"},
		{4, "Enemy"},
		{5, "Sibling"}
	};
	
	set<char> set1;
	set<char> set2;
	
	for(int i=0;i<s1.size();i++)
		set1.insert(s1[i]);
	for(int i=0;i<s2.size();i++)
		set2.insert(s2[i]);
	
	vector<char> intersectionSet;
	vector<char> unionSet;
	vector<char> diffSet;
	
	set_intersection(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(intersectionSet));
	set_union(set1.begin(), set1.end(), set2.begin(), set2.end(), back_inserter(unionSet));
	set_difference(unionSet.begin(), unionSet.end(), intersectionSet.begin(), intersectionSet.end(), back_inserter(diffSet));
	
	if(diffSet.size()%6 == 0)
		return flames_map[5];
	else
		return flames_map[diffSet.size()%6 - 1];
	
	// for(auto s: intersectionSet)
	// 	cout<<s<<" ";
	// cout<<endl;
	
	// for(auto s: unionSet)
	// 	cout<<s<<" ";
	// cout<<endl;
	
	// for(auto s: diffSet)
	// 	cout<<s<<" ";
	// cout<<endl;
}

int main() {
	string s = flamescalculator("elizabetha", "alexander");
	cout<<s<<endl;
	return 0;
}




// Another beautiful solution

import java.util.*;

public class Harshit {
    static String[] flamingo = {
        "friendship",
        "love",
        "affection",
        "marriage",
        "enemy",
        "ssss"
    };

    public static String flames(String yin, String yang) {
        int[] yins = new int[26];
        int[] yangs = new int[26];
        int mod = 0;
        for(char c:  yin.toCharArray()) 
        	yins [c - 'a']++;
        for(char c: yang.toCharArray()) 
        	yangs[c - 'a']++;

        for(int i = 0; i < 26; ++i) 
        	mod += ((yins[i] == 0 ^ yangs[i] == 0) ? yins[i] + yangs[i] : 0);
        
        return flamingo[mod % 6 - 1];
    }

    public static void main(String[] args) {
        System.out.println(flames("alexander", "elisabeth"));
    }
}
