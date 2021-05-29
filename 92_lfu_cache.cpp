
/*

Harshit Gupta | 28th May, 2021
---------------------------------

C++ program for "LFU CACHE"
Read full problem here: https://leetcode.com/problems/lfu-cache/
------

Solution: Explained Below

Time Complexity: O(1)
Space Complexity:

Paradigm:
---
  NOTE: 

*/



//Just for better readability
using Key_t = int;
using Count_t = int;

struct Node {
    int value;
    list<Key_t>::iterator itr;
};

class LFUCache {
    // Map to store the key and value. Also, as a part of the value, we will be storing the address of the DLL node which contains the key.
    unordered_map<Key_t, Node> m_values;
    // Map to store the frequency of each key
    unordered_map<Key_t, Count_t> m_counts;
    // Map to store the frequencies as keys and a DLL associated to them which are keys for that frequency.
    // In this DLL, the back is least recently used while the front is the most freshly added node.
    unordered_map<Count_t, list<Key_t>> m_countKeyMap;
    
    // This will contain the lowest frequency so that we can refer the m_countKeyMap hash and get the keys for the lowest freq
    int m_lowestFrequency;
    int m_maxCapacity;

public:
    LFUCache(int capacity) {
        m_maxCapacity = capacity;
        m_lowestFrequency = 0;
    }

    int get(int key) {
        // if is this key is not present in the map of key,values, then return -1
        if (m_values.find(key) == m_values.end() || m_maxCapacity <= 0) {
            return -1;
        }
        //else return the value from the map and update frequency
        // we call the same put method instead of writing a new one with the value already present 
        // so that it overwrites the same value(as a side effect) and increases the freq of access
        put(key, m_values[key].value);
        return m_values[key].value;
    }

    void put(int key, int value) {
        if (m_maxCapacity <= 0){
            return;
        }

        // If key is not present and capacity has exceeded, 
        //      Then remove the key entry with least frequency
        //      If after removal, it leaves us with NO ELEMENTS in the associated DLL, then we erase that frequency from the map m_countKeyMap
        //          we must also remove the keys from the maps 'm_values' and 'm_counts' since that element is popped out of cache
        //      Also add the new key with 0 frequency in 'm_counts' map and create a node in DLL in the 'm_values' map with 0 freq. Add details in 'm_values' map as well
        // If key is not present and capacity has NOT exceeded
        //      add the new key with 0 frequency in 'm_counts' map and create a node in DLL in the 'm_values' map with 0 freq. Add details in 'm_values' map as well
        
        if (m_values.find(key) == m_values.end())
        {
            if (m_values.size() == m_maxCapacity)
            {
                int keyToDelete = m_countKeyMap[m_lowestFrequency].back(); 
                m_countKeyMap[m_lowestFrequency].pop_back();
                if (m_countKeyMap[m_lowestFrequency].empty()) {
                    m_countKeyMap.erase(m_lowestFrequency);
                }
                m_values.erase(keyToDelete);
                m_counts.erase(keyToDelete);
            }
            m_values[key].value = value;
            m_counts[key] = 0;
            m_lowestFrequency = 0;
            m_countKeyMap[m_counts[key]].push_front(key);
            m_values[key].itr = m_countKeyMap[0].begin();
        }
        
        // If key is present in the m_values map, it means we have to update the value and increase the frequency
        //      We find the frequency of key from 'm_counts' and find the DLL node of the key in 'm_countKeyMap'. We delete the node since the freq will be increased
        //          If on delete, we are left with no nodes for that freq and that is the lowest freq as well, then we increase the lowest freq & delete the freq from the 'm_countKeyMap'
        //          We want to increase the frequency of this key by 1 and now after deletion, no element is left with the same older lowest frequency, so we have to updated lowest frequency by 1 as well since we know that this element will be the one which will have frequency of oldLF+1 after our insertion later.
        //      We update the new value in 'm_values'
        //      We update the freq in 'm_counts'
        //      We create a new DLL node for the updated freq
        //      We link this newly created DLL node in the 'm_values' map
        else {
            m_countKeyMap[m_counts[key]].erase(m_values[key].itr);
            if (m_countKeyMap[m_counts[key]].empty()) {
                if (m_lowestFrequency == m_counts[key]){
                    m_lowestFrequency++;
                }
                m_countKeyMap.erase(m_counts[key]);
            }
            m_values[key].value = value;
            m_counts[key]++;
            m_countKeyMap[m_counts[key]].push_front(key);
            m_values[key].itr = m_countKeyMap[m_counts[key]].begin();
        }
    }
};