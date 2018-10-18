/* 
Harshit Gupta | 15th October, 2018

https://ide.geeksforgeeks.org/qgQwTy0Jvs
https://www.geeksforgeeks.org/trie-insert-and-search/
https://www.geeksforgeeks.org/trie-display-content/
https://www.geeksforgeeks.org/trie-delete/

C++ program for Inserting and Searching in a Trie. It also displays a Trie.

Solution: We make a trie node as root. For both the operation we use a current pointer starting from root.
        * To insert into a trie, we keep on traversing if the node is already present. 
            If not, then we make the node and traverse forward. 
            We mark the last character node with isEndOfWord=true
        * To search into a trie, we keep on checking if the current pointer is not NULL.
          If at at any point it is NULL, then we return false.
          If not, then we traverse till the end and check if isEndOfWord==true.
        * To display a trie, we use backtracking. 
          Keep on adding the elements in an array. If the isEndOfWord is true, then print it.

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

bool searchIntoTrie(TrieNode *root, string s){
    int n=s.size();
    
    // Taking a TrieNode which we will use for traversing the Trie.
    TrieNode *current = root;
    
    // Iterate over all the characters of the string to searchfor TrieNodes.
    for(int i=0;i<n;i++){
        int index = s[i]-'a';
        
        // Check if at any point if a node doesn't exist, then the string doesn't exist in trie.
        if(current->children[index]==NULL)
            return 0;
        
        // Keep moving forward...
        current = current->children[index];
    }
    
    // If isEndOfWord is set and the last node is set, then the string is present.
    if(current!=NULL && current->isEndOfWord)
        return 1;
    else
        return 0;
}

void printTrie(TrieNode *current, vector<char> arr){
    
    for(int i=0;i<ALPHABET_SIZE;i++){
        if(current->children[i]!=NULL){
            if(current->children[i]->isEndOfWord == true){
                arr.push_back((char)(i+'a'));
                
                for(int i=0;i<arr.size();i++)
                    cout<<arr[i];
                cout<<endl;
                
                printTrie(current->children[i], arr);
                arr.pop_back();
            }
            else{
                arr.push_back((char)(i+'a'));
                printTrie(current->children[i], arr);
                arr.pop_back();
            }
        }
    }

}

int main() 
{
    // Making a root Trie node.
    TrieNode *root = new TrieNode;
    insertIntoTrie(root, "harshit");
    insertIntoTrie(root, "gupta");
    insertIntoTrie(root, "harsh");
    
    if (searchIntoTrie(root, "harshit"))
        cout<<"harshit is present in Trie"<<endl;
    else
        cout<<"harshit is NOT present in Trie"<<endl;
        
    if(searchIntoTrie(root, "gupta"))
        cout<<"gupta is present in Trie"<<endl;
    else
        cout<<"gupta is NOT present in Trie"<<endl;
        
    if (searchIntoTrie(root, "harsh"))
        cout<<"harsh is present in Trie"<<endl;
    else
        cout<<"harsh is NOT present in Trie"<<endl;
    
    vector <char> arr;
    printTrie(root, arr);
        
    return 0; 
} 
