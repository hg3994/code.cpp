
/*

Harshit Gupta | 25th July, 2021
---------------------------------

Problem Statement:

Given a list of words, return the index of the 1st and last words with the prefix typed.

Example:
	0 abacus
	1 cool
	2 cat
	3 catapult
	4 cataract
	5 delta

	prefix "cat" -> 2,4
	prefix "ca" -> 2,4
	prefix "c" -> 1,4

Assumptions:
	1. All letters are lowercase english letters.
	2. The prefix letter may not be in trie.
	3. If prefix word is not in Trie, return -1,-1

https://ideone.com/82hqM4

------

Solution: 
		1. When a new node is created, we update its start and end index.
		2. When an existing node is there and we just pass from it, we update the end index since now this word
			has an ending index > than the index from which it was made.
		
	c -> 1,1
	co -> 1,1
	coo -> 1,1
	cool -> 1,1
	c -> 1,2
	ca -> 2,2
	cat -> 2,2
	c -> 1,3
	ca -> 2,3
	cat -> 2,3
	cata -> 3,3
	catap -> 3,3
	c -> 1,4
	ca -> 2,4
	cat -> 2,4
	cata -> 3,4
	catar -> 4,4

    TC: O(l) where 'l' is the length of the letter for the queries. It take one time effort to build the trie and takes 
    	O(n) time where n is the number of words there.
    SC: O(26n), one node for each letter where n is the max length of a word

Paradigm:
---
    NOTE: GOOGLE

    Similar Questions:
        1.

*/


#include <bits/stdc++.h>
using namespace std;

#define ALPHABET_SIZE 26

class TrieNode {
public:
	TrieNode* children[ALPHABET_SIZE];
	int startIndex, endIndex;
	TrieNode() {
		for(int i=0; i<ALPHABET_SIZE; i++)
			this->children[i] = NULL;
	}
};

class Trie {
public:
	TrieNode* root;
	Trie(){
		root = new TrieNode();
	}

	void insert(string word, int indexOfWord){
		TrieNode* current = root;
		// cout<<word<<endl;
		for(int i=0; i<word.size(); i++){
			int index = word[i]-'a';
			if(current->children[index]){
				current=current->children[index];
				current->endIndex = indexOfWord;
			}
			else{
				current->children[index] = new TrieNode();
				current=current->children[index];
				current->startIndex = indexOfWord;
				current->endIndex = indexOfWord;
			}
		}
	}

	vector<int> prefixFirstLastOccurance(string prefix){
		TrieNode* current = root;
		for(int i=0; i<prefix.size(); i++){
			int index = prefix[i]-'a';
			if(current->children[index]){
				current =current->children[index];
				// cout<<"  start & endIndex of "<<prefix[i]<<" :"<<current->startIndex<<" "<<current->endIndex<<endl;
			}
			else{
				return {-1, -1};
				// cout<<"-1, -1"<<endl;
			}
		}
		return {current->startIndex, current->endIndex};
		// cout<<current->startIndex<<" "<<current->endIndex<<endl;
	}

};


vector<int> firstAndLastOccuranceWith (vector<string>words, string prefix){
	Trie* t = new Trie();
	for(int i=0; i<words.size(); i++) {
		t->insert(words[i], i);
	}
	return t->prefixFirstLastOccurance(prefix);
}

// int main() {
// 	Trie* t = new Trie();
// 	vector<string>words = {"abacus", "cool", "cat", "catapult", "cataract", "zzz"};
// 	string prefix = "cata";
// 	for(int i=0; i<words.size(); i++) {
// 		t->insert(words[i], i);
// 	}
// 	t->prefixFirstLastOccurance(prefix);
// 	return 0;
// }