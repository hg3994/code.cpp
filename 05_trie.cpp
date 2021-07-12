/* 
Harshit Gupta | 28th October, 2018

https://ide.geeksforgeeks.org/J84FBLsV86
https://www.geeksforgeeks.org/trie-insert-and-search/
https://www.geeksforgeeks.org/trie-display-content/
https://www.geeksforgeeks.org/trie-delete/
https://www.geeksforgeeks.org/auto-complete-feature-using-trie/
https://leetcode.com/problems/implement-trie-prefix-tree/


C++ program for Inserting, Searching and Displaying in a Trie.
    Also, implementation of Auto complete feature of a dictionary using Trie.

Solution: We make a trie node pointer root. For both the operation we use a current pointer starting from root.
        * To insert into a trie, we keep on traversing if the node is already present. 
            If not, then we make the node and traverse forward. 
            We mark the last character node with isEndOfWord=true
        * To search into a trie, we keep on checking if the current pointer is not NULL.
            If at at any point it is NULL, then we return false.
            If not, then we traverse till the end and check if isEndOfWord==true.
        * To display a trie, we use backtracking. 
            Keep on adding the elements in an array. If the isEndOfWord is true, then print it.
        * For auto complete feature of a trie, we traverse till the word already given.
            If the given word doesn't exist, then no suggestion.
            Else, we need to print all the words inside this. We can use the printTrie function for this.

Time Complexity: If you want to insert/search a key of size 'key_length'
    Insert: O(key_length)
    Search: O(key_length)

Space Complexity: O(ALPHABET_SIZE * key_length * N)
---
    Similar Questions: 
        1. https://leetcode.com/problems/implement-trie-ii-prefix-tree/
            - Implement "countWordsEqualTo" & "countWordsStartingWith" & "erase" APIs.
            - We change the TrieNode class to store the words going through it & words ending on this node.


*/

#include <bits/stdc++.h>
using namespace std; 
#define ALPHABET_SIZE 26

struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    TrieNode(){
        for(int i=0;i<ALPHABET_SIZE;i++)
            this->children[i]=NULL;
        this->isEndOfWord=NULL;
    }
};

typedef struct TrieNode TrieNode;

void insertIntoTrie(TrieNode *root, string s){
    int n=s.size();
    
    // Taking a TrieNode which we will use for traversing the Trie.
    TrieNode *current = root;
    
    // Iterate over all the characters of the string to make nodes.
    for(int i=0;i<n;i++){
        int index = s[i]-'a';
        
        // Check for the children index. Make a new node, if one doesn't exist already.
        if(current->children[index]==NULL)
            current->children[index] = new TrieNode;
        
        // Keep moving forward...
        current = current->children[index];
    }
    current->isEndOfWord = true;
}

void searchIntoTrie(TrieNode *root, string s){
    int n=s.size();
    
    // Taking a TrieNode which we will use for traversing the Trie.
    TrieNode *current = root;
    
    // Iterate over all the characters of the string to searchfor TrieNodes.
    for(int i=0;i<n;i++){
        int index = s[i]-'a';
        
        // Check if at any point if a node doesn't exist, then the string doesn't exist in trie.
        if(current->children[index]==NULL){
            cout<<s<<" is NOT present in Trie"<<endl;
            return;
        }
        // Keep moving forward...
        current = current->children[index];
    }
    
    // If isEndOfWord is set and the last node is set, then the string is present.
    if(current!=NULL && current->isEndOfWord)
        cout<<s<<" is present in Trie"<<endl;
    else
        cout<<s<<" is NOT present in Trie"<<endl;
}

void printTrie(TrieNode *current, vector<char> arr){
    
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(current->children[i]!=NULL){

            // Keep on adding the elements in an array. 
            arr.push_back((char)(i+'a'));

            // If the isEndOfWord is true, then print it.
            if(current->children[i]->isEndOfWord == true){
                
                for(int i=0;i<arr.size();i++)
                    cout<<arr[i];
                cout<<endl;
            }

            // Recur for its children
            printTrie(current->children[i], arr);
            
            // Backtracking
            arr.pop_back();
        }
    }
}

void autoCompleteSuggestions(TrieNode *root, string s){
    TrieNode *current = root;
    int n = s.size();
    cout<<endl;
    
    // We traverse till the word(s) already given in the trie
    for(int i=0;i<n;++i){
        if(current->children[s[i]-'a']!=NULL){
            current=current->children[s[i]-'a'];
        }

        // If the given word doesn't exist, then no suggestion.
        else{
            cout<<"The string "<<s<<" doesn't exist in Trie. No Suggestions."<<endl;
            return;
        }
    }
    
    cout<<"autoCompleteSuggestions for "<<s<<" are: "<<endl;
    vector <char> arr (s.begin(), s.end());
    
    // Print the word if that is present in the trie.
    if(current->isEndOfWord == true){
        cout<<s<<endl;
    }
    
    // We need to print all the words(children) inside the trie from this node.
    printTrie(current,arr);

}

int main() 
{
    // Making a root Trie node.
    TrieNode *root = new TrieNode;
    insertIntoTrie(root, "hello");
    insertIntoTrie(root, "dog");
    insertIntoTrie(root, "hell");
    insertIntoTrie(root, "cat");
    insertIntoTrie(root, "a");
    insertIntoTrie(root, "hel");
    insertIntoTrie(root, "help");
    insertIntoTrie(root, "helps");
    insertIntoTrie(root, "helping");
    insertIntoTrie(root, "harshit");
    insertIntoTrie(root, "harshitgupta");
    
    searchIntoTrie(root, "harshit");
    searchIntoTrie(root, "gupta");
    searchIntoTrie(root, "harshitgupta");
    
    vector <char> arr;
    cout<<endl<<"The elements in trie are:"<<endl;
    printTrie(root, arr);
    
    autoCompleteSuggestions(root,"hel");

    return 0; 
} 


// -------------------------------------
// LC IMPLEMENTATION BELOW
// -------------------------------------

#define ALPHABETSIZE 26

class TrieNode {
public: 
    TrieNode* children[ALPHABETSIZE];
    bool isEndOfWord;
    TrieNode(){
        for(int i=0; i<ALPHABETSIZE; i++)
            this->children[i] = NULL;
        this->isEndOfWord = false;
    }
};


class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    /** Inserts a word into the trie. */
    void insert(string word) {
        TrieNode* current = root;
        
        for(int i=0; i<word.size(); i++){
            int index = word[i] - 'a';
            if(current->children[index] == NULL){
                TrieNode* newNode = new TrieNode;
                current->children[index] = newNode;
            }
            current = current->children[index];
        }
        current->isEndOfWord = true;
    }
    
    /** Returns if the word is in the trie. */
    bool search(string word) {
        TrieNode* current = root;
        
        for(int i=0; i<word.size(); i++){
            int index = word[i] - 'a';
            
            if(current->children[index] == NULL)
                return false;
            current = current->children[index];
        }
        return current->isEndOfWord == true;
    }
    
    /** Returns if there is any word in the trie that starts with the given prefix. */
    bool startsWith(string prefix) {
        TrieNode* current = root;
        for(int i=0; i<prefix.size(); i++){
            int index = prefix[i]-'a';
            if(current->children[index] == NULL)
                return false;
            current = current->children[index];
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */


// --------------------------------------------
// LC 2nd Question BELOW:
// --------------------------------------------
#define ALPHABET_SIZE 26
class TrieNode {
public:
    TrieNode* children[ALPHABET_SIZE];
    int end;
    int start;
    TrieNode() {
        for(int i=0;i<ALPHABET_SIZE; i++){
            this->children[i] = NULL;
        }
        this->end = 0; // to store the words ending at this node.
        this->start = 0; // to store the words going through this node.
    }
};

class Trie {
public:
    TrieNode* root;
    Trie() {
        root = new TrieNode();
    }
    
    // Update the start at every node insertion & end at the last node.
    void insert(string word) {
        TrieNode* current = root;
        for(int i=0; i<word.size(); i++){
            int index = word[i]-'a';
            if(current->children[index]){
                current = current->children[index];
                current->start = current->start+1;
            }
            else{
                current->children[index] = new TrieNode;
                current = current->children[index];
                current->start = current->start+1;
            }
        }
        current->end = current->end+1;
    }
    
    // Return the "end" by just traversing the word
    int countWordsEqualTo(string word) {
        TrieNode* current = root;
        for(int i=0; i<word.size(); i++){
            int index = word[i]-'a';
            if(current->children[index]){
                current = current->children[index];
            }
            else{
                return 0;
            }
        }
        return current->end;
    }
    
    // Return the "start" after traversing the word.
    int countWordsStartingWith(string prefix) {
        TrieNode* current = root;
        for(int i=0; i<prefix.size(); i++){
            int index = prefix[i]-'a';
            if(current->children[index]){
                current = current->children[index];
            }
            else{
                return 0;
            }
        }
        return current->start;
    }
    
    // Keep decreasing the 'start' at every node and 'end' for the final node.
    // TODO: Delete the node if start=0 & end=0 for the final node.
    void erase(string word) {
        TrieNode* current = root;
        for(int i=0; i<word.size(); i++){
            int index = word[i]-'a';
            current = current->children[index];
            current->start = current->start - 1;
        }
        current->end -= 1;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * int param_2 = obj->countWordsEqualTo(word);
 * int param_3 = obj->countWordsStartingWith(prefix);
 * obj->erase(word);
 */