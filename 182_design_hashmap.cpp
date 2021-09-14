
/*

Harshit Gupta | 16th August, 2021
---------------------------------

Problem Statement:
    Design a HashMap without using any built-in hash table libraries.

    Implement the MyHashMap class:

    MyHashMap() initializes the object with an empty map.
    void put(int key, int value) inserts a (key, value) pair into the HashMap. If the key already exists in the map, update the corresponding value.
    int get(int key) returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key.
    void remove(key) removes the key and its corresponding value if the map contains the mapping for the key.
------

Solution: 

    TC: 
    SC:

Paradigm:
---
    NOTE: 

    Similar Questions:
        1.

*/

class MyHashMap {
    // A vector OF "doubly linked list of pairs"
    vector<list<pair<int,int>>> map;
    // For accessing elemens of vector like: map[key % m_size];
    size_t m_size = 10000;

public:
    
    MyHashMap() {
        map.resize(m_size);
    }
    
    void put(int key, int value) {
        auto &list = map[key % m_size];
        // Update if already present key
        for (auto & val : list) {
            if (val.first == key) {
                val.second = value;
                return;
            }
        }
        // Push it in list if the key was not present.
        list.emplace_back(key, value);
    }
    
    int get(int key) {
        const auto &list = map[key % m_size];
        for (const auto & val : list) {
            if (val.first == key) {
                return val.second;
            }
        }
        return -1;
    }
    
    void remove(int key) {
        auto& pairs = map[key%m_size];
        for(auto i=pairs.begin(); i!= pairs.end(); i++) {
            if(i->first==key) { 
                pairs.erase(i); return; 
            }
        }
    }
};


// Simple solution when we know the key range (given in constraints)

// vector<int> map;

// MyHashMap() { 
//     map.resize(1000001,-1);
// }

// void put(int key, int value) {
//     map[key] = value;
// }

// int get(int key) {
//     return map[key];
// }

// void remove(int key) {
//     map[key] = -1;
// }