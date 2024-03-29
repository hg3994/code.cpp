/* 
Harshit Gupta | 3rd February, 2019


C++ program for How to implement LRU caching scheme? What data structures should be used?
	We are given total possible page numbers that can be referred. We are also given cache size 
	(Number of page frames that cache can hold at a time). The LRU caching scheme is to remove the 
	least recently used frame when the cache is full and a new page is referenced which is not there in cache.

https://leetcode.com/problems/lru-cache/

Solution: We want to have two APIs, one is InsertIntoCache() and another showCache();
		We want to implement the LRU algorithm in the InsertIntoCache() method.
		We want to see the contents of the cache at any point of time through the showCache() method.

		We obviously want to 
			insert the elements into the cache in O(1) time.
			delete the elements from the cache in O(1) time.
			update the elements in   the cache in O(1) time.

		Queue: If we use queue to store the elements, then can insert the elements from back in O(1) time, 
				but it will be very hard to delete the last element and then update the contents in the middle.
				So, we can't use Queue.

		Linked List: If we use LL to store the elements, we can insert in O(1) time, delete in O(1) time. 
				To update, we will have to connect the prev and next nodes, but here we won't know the address
				of the prev node.
				Moreover, to find an element in the LL to figure out "if the node is already present in the cache?", 
				it needs O(n) time.

		DLL: This fixes the problem of prev in LL, but if we use DLL only, then it will take us O(n) time
				to figure out "if the node is already present in the cache?"

		Hash & DLL: If we use a hash then we would be able to find the address of the node (if present) in O(1) time.
				All we have to do is, store a hash of addresses of nodes with their keys and then if we want to know
				if the key is already in the DLL, then we can check the hash and know it in O(1) time. If the element
				is present, then we can point to the address of the node, and if it is not present, we can delete
				the last node and then create a new node in the front of the DLL.

		---		

		We can use Hash and DLL as the data structures used for LRUCache implementation.
		Hash will store the key as the input number and the value would be the address of the node in the DLL.
		The DLL would also contain the same input in its data part. Now when we get a new element, 
		the algo would be:

			If the element 'n' is in the map:
				remove 'n' from its place
				insert 'n' to the front
				update the map
			If the element 'n' is not in the map:
				If the cache is full:
					delete the last element and remove from the map
					insert 'n' in the front
					update the map
				If cache is not full:
					insert 'n' in the front
					update the map

EXAMPLE FROM LEETCODE:
	Input
		["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
		[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
	Output
		[null,null,null,10,null,-1,null,-1,30,40]

	Explanation
		LRUCache lRUCache = new LRUCache(2);
		lRUCache.put(1, 10); 	// cache is {1=10}
		lRUCache.put(2, 20); 	// cache is {1=10, 2=20}
		lRUCache.get(1);    	// return 10
		lRUCache.put(3, 30);	// LRU key was 2, evicts key 2, cache is {1=10, 3=30}
		lRUCache.get(2);    	// returns -1 (not found)
		lRUCache.put(4, 40); 	// LRU key was 1, evicts key 1, cache is {4=40, 3=30}
		lRUCache.get(1);    	// return -1 (not found)
		lRUCache.get(3);    	// return 30
		lRUCache.get(4);    	// return 40


Paradigm: Hash, Doubly Linked List, DLL

*/

// --------
// LEETCODE
// --------

class LRUCache {
public:
    
    int cache_size;
    
    // DLL to store the Least Recently Used Cache
    // Front -> Most Recently Used
    // Back -> Least recently used / Last Element in Cache
    // Adding directly in front will be O(1) time.
	list<pair<int, int>> dll; 
    
    // Map to store the key and address of the node of the DLL.
    // This will help us retrieve the node in O(1) time.
	unordered_map<int, list<pair<int, int>>::iterator> map;
    
    // Size of the Cache is fixed, we evict the least recently used if required.
    LRUCache(int capacity) {
        cache_size = capacity;
    }
    
    int get(int key) {
        // If the key is present in the map, we find the value and return it
        // We must also bring that node to the "front" since it is USED now!!
        // To bring it to the front, 
        //      we delete the old node, 
        //      add a new node in front with same key,val
        //      update the map with address of new node
        
        if(map.find(key) == map.end()){
            return -1;
        }
        else{
            list<pair<int, int>>::iterator it0 = map[key];
            pair<int, int> node = *it0;
            
            dll.erase(map[key]);
            dll.push_front(make_pair(key, node.second));
            map[key] = dll.begin();
            
            return node.second;
        }
    }
    
    
    void put(int key, int value) {
        // If the key is NOT present in the map (it is NOT present in cache)
        //      If the cache is full
        //          We delete the last element from cache and map
        //          We add new element in front and its address in the map
        //      If the cache is vacant
        //          We add new element in front and its address in the map
        // If node is present in the map (it is present in the cache)
        //      Erase the node which was already present
        //      We add new element in front and its address in the map

        if(map.find(key) == map.end()){
            if(dll.size() == cache_size){
            	pair<int, int> last_element = dll.back();
                dll.pop_back();
                map.erase(last_element.first); // THIS IS VERY IMPORTANT !!! DONT FORGET !!!
            }
        }
        else {
            dll.erase(map[key]);
        }
        
        dll.push_front(make_pair(key, value));
        map[key] = dll.begin();
        // show();
    }
    
    
    // void show(){
    //     cout<<"DLL: ";
    //     for(auto l : dll){
    //         cout<<l.first<<","<<l.second<<" -> ";
    //     }
    //     cout<<endl;
    //     cout<<"Map: ";
    //     for(auto m: map){
    //         cout<<m.first<<" ";
    //     }
    //     cout<<endl<<"***"<<endl;
    // }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

// ---------------------------------------------------------------------------------

#include <bits/stdc++.h>
using namespace std; 

class Cache{

	int cache_size;
	list<int> dll; 
	unordered_map<int, list<int>::iterator> map;
	
	public:
		// constructor to set the size of the cache
		Cache(int);
		void insertIntoCache(int);
		void showCache();
};

Cache::Cache(int n){
	cache_size = n;
}

void Cache::insertIntoCache(int n){
	// If the element 'n' is in the map:
	// 		remove 'n' from its place
	// 		insert 'n' to the front
	// 		update the map
	// If the element 'n' is not in the map:
	// 		If the cache is full:
	// 			delete the last element and remove from the map
	// 			insert 'n' in the front
	// 			update the map
	// 		If cache is not full:
	// 			insert 'n' in the front
	// 			update the map

	// You see that "insert 'n' in the front" and "update the map" is done for all the three Ifs. 
	// So, just for the sake of DRY code, it is brought outside the IFs.

	// Not in cache
	if (map.find(n) == map.end()){
		// cache is full
		if(dll.size() == cache_size){
			int last_element = dll.back();
			// delete from DLL and remove from map
			dll.pop_back();
			map.erase(last_element);
		}
	}
	// already in cache
	else{
		// remove the previous entry since a new entry is to be made.
		dll.erase(map[n]);
	}

	// insert it in front and update the map
	dll.push_front(n);
	map[n] = dll.begin();

}

void Cache::showCache(){
	// print the DLL.
	for (auto it = dll.begin(); it != dll.end(); it++) 
      cout << (*it) << " ";
  cout << endl;
}

int main() 
{
	Cache c(4);
	c.insertIntoCache(10);
	c.insertIntoCache(20);
	c.insertIntoCache(30);
	c.insertIntoCache(10);
	c.insertIntoCache(40);
	c.insertIntoCache(50);
	c.showCache();
  return 0; 
} 