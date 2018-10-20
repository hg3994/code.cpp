/* 
Harshit Gupta | 20th October, 2018

https://www.geeksforgeeks.org/rearrange-characters-string-no-two-adjacent/
https://ide.geeksforgeeks.org/tqd1ushUdK

C++ program for Rearranging characters in a string such that no two adjacent characters are same.

Solution: The idea is to put highest frequency character first (a greedy approach). 
    We use a priority queue (Or Binary Max Heap) and put all characters 
    and ordered by their frequencies (highest frequency character at root). 
    We one by one take highest frequency character from the heap and add it to result. 
    After we add, we decrease frequency of the character and we temporarily 
    move this character out of priority queue so that it is not picked next time.

Implementation: 
    1. Build a Priority_queue or max_heap, pq that stores characters and their frequencies.
        Priority_queue or max_heap is built on the bases of frequency of character.
    2. Create a temporary Key that will used as the previous visited element 
        (previous element in resultant string. Initialize it { char = ‘#’ , freq = ‘-1’ })
    3. While pq is not empty.
        - Pop an element and add it to result.
        - Decrease frequency of the popped element by ‘1’
        - Push the previous element back into the priority_queue if it’s frequency > ‘0’
        - Make the current element as previous element for the next iteration.
    4. If length of resultant string and original, print “not possible”. Else print result.


*/

#include <bits/stdc++.h>
using namespace std; 

#define MAX_CHAR 26

struct Key{
    int freq;
    char ch;
    
    // function for priority_queue to store Key 
    // according to freq 
    // https://stackoverflow.com/questions/15601973/stl-priority-queue-of-c-with-struct
    bool operator<(const Key &k) const
    { 
        return freq < k.freq; 
    }
};

typedef struct Key key;

void reArrangeString(string s){
    int n = s.size();
    
    // Have a direct addressing table for storing the freq of characters in an array. 
    int direct_address_table[MAX_CHAR]= {0};
    
    // Store the frequencies
    for(int i=0;i<n;i++){
        direct_address_table[s[i]-'a']++;
    }
    
    // The priority queue which will store the elements of type: 
    // 'key' with 'freq' for ordering
    priority_queue <key> pq;
    
    // Push the 'keys' into the pq.
    for(char c='a';c<='z';c++){
        if(direct_address_table[c-'a']>0)
            pq.push({direct_address_table[c-'a'], c});
    }
    
    string ans="";
    
    // We have this key for storing the previous popped node. 
    // We have to push it back right?
    key prev = {-1, '#'};
    
    // Till my pq is empty
    while(!pq.empty()){
        
        // Take the element with the highest freqency and pop it. 
        // Store it in my answer string and decrease its frequency.
        key k =pq.top();
        pq.pop();
        ans += k.ch;
        (k.freq)--;
        
        // Push the last popped character if it has a valid freqency.
        if(prev.freq > 0)
            pq.push(prev);
        
        // Store the popped key in this variable so that
        // it can be pushed in for the next time.
        prev = k;
    }
    
    // If its not a valid string, then their lengths won't match since 
    // a character would remain with more freqency and the loop will exit.
    // The ans variable would thus have length less than the original string.
    if(s.size() != ans.size())
        cout<<"Not a valid string: "<<ans<<endl;
    else
        cout<<"String: "<<ans<<endl;
}

int main(){
    string s = "aaaabbc";
    reArrangeString(s);
    return 0;
}