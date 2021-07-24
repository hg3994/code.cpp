
/*

Harshit Gupta | 24th May, 2021
---------------------------------

C++ program for "Inserting, Deleting and Getting Random Element in O(1) time"

1. RandomizedSet() 
    Initializes the RandomizedSet object.
2. bool insert(int val) 
    Inserts an item val into the set if not present. Returns true if the item was not present, false otherwise.
3. bool remove(int val) 
    Removes an item val from the set if present. Returns true if the item was present, false otherwise.
4. int getRandom() 
    Returns a random element from the current set of elements (it's guaranteed that at least one element exists 
    when this method is called). Each element must have the same probability of being returned.

https://leetcode.com/problems/insert-delete-getrandom-o1/
------

Solution: The data structure that comes to our mind with O(1) are:
    - HashMaps: Insert, Delete in O(1) but getting any random value would need an iterator and that 
        iteration in hashmap to a random index would be O(n).
    - DLL: Insert in O(1), Delete in O(1) time but to traverse to a specific index will take O(n) time for deletion.
        It doesn't have support for [] operator for randomly accessing the index.
    - Set: Insert and Remove in O(1) time for unordered_set but it doesnt have the [] operator to access any index.
        To acccess a random index, you must traverse the set in O(n) time.
    - Vectors/Arrays: Insert is O(1) but to know if an element is already present will take O(n) time if done at end. 
        Remove any element is O(1) through a stratergy discussed below but to know iff it is present is again O(n)
        Getting Random Index is O(1) since any index can be accessed through [] operator.
        The only difficulty with Vectors is "HOW TO KNOW IF AN ELEMENT IS PRESENT IN IT?"" in O(1) time.
        
    - Vectors/Arrays+HashMaps: Hashmaps store indexes of elements and solve the problem above, vector stores the elements.
        Insert: To know if already inserted, we use Hashmap and get it in O(1) time.
            If not inserted, we push_back in vector in O(1) time & put the val->index in map
        Remove: To know if present or not, we use Hashmap and get it in O(1) time.
            If present, we remove it from vector like this:
                Copy element of last index to the element to be removed index
                Pop the last index in O(1) time.
                Update map with new index of last element and remove element to be deleted from the map
        Get Random: Simply choose a random number and access it with the [] operator.

Time Complexity: O(1) for all operations
Space Complexity: O(1) for all operations
---
  NOTE: 

*/



class RandomizedSet {
public:
    unordered_map <int, int > m;
    vector<int> v;
    RandomizedSet() {
        
    }
    
    bool insert(int val) {
        // If my map has the val, return false
        if(m.count(val)){
            return false;
        }
        // If my map doesn't have it, push it in the vector
        // Update the map with the val and index of the vector
        else{
            v.push_back(val);
            m[val] = v.size()-1;
            return true;
        }
    }
    
    
    bool remove(int val) {
        // If map doesn't have the value, return false    
        if (m.find(val) == m.end()) return false;
        
        // We're sure that map has the val. Get the index of the stored val
        auto it = m.find(val);
        
        // update the vector in index of val to be = last element in v
        // it->second : index of the element 'val' which is to be deleted
        v[it->second] = v.back();
        
        // remove the last element, we have got rid of 'val' from the vector 'v' now
        v.pop_back();
        
        // map's index for last element has changed to old index of val, so update it
        m[v[it->second]] = it->second;
        
        // map's val would still show the old index, erase it
        m.erase(val);

        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return v[rand() % v.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */