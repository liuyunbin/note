/*
 * [146] LRU Cache
 *
 * https://leetcode.com/problems/lru-cache/description/
 *
 * algorithms
 * Hard (18.95%)
 * Total Accepted:    154K
 * Total Submissions: 810.5K
 * Testcase Example:  '["LRUCache","put","put","get","put","get","put","get","get","get"]\n[[2],[1,1],[2,2],[1],[3,3],[2],[4,4],[1],[3],[4]]'
 *
 * 
 * Design and implement a data structure for Least Recently Used (LRU) cache.
 * It should support the following operations: get and put.
 * 
 * 
 * 
 * get(key) - Get the value (will always be positive) of the key if the key
 * exists in the cache, otherwise return -1.
 * put(key, value) - Set or insert the value if the key is not already present.
 * When the cache reached its capacity, it should invalidate the least recently
 * used item before inserting a new item.
 * 
 * 
 * Follow up:
 * Could you do both operations in O(1) time complexity?
 * 
 * Example:
 * 
 * LRUCache cache = new LRUCache( 2 * capacity * );
 * 
 * cache.put(1, 1);
 * cache.put(2, 2);
 * cache.get(1);       // returns 1
 * cache.put(3, 3);    // evicts key 2
 * cache.get(2);       // returns -1 (not found)
 * cache.put(4, 4);    // evicts key 1
 * cache.get(1);       // returns -1 (not found)
 * cache.get(3);       // returns 3
 * cache.get(4);       // returns 4
 * 
 * 
 */
class LRUCache {
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }
    
    int get(int key) {
        if (my_map.find(key) == my_map.end())
            return -1;
        li.splice(li.begin(), li, my_map[key]);
        return my_map[key]->second;
    }
    
    void put(int key, int value) {
        if (my_map.find(key) == my_map.end()) {
            if (li.size() == capacity) {
                my_map.erase(li.back().first);
                li.pop_back();
            }
            li.push_front(make_pair(key, value));
            my_map[key] = li.begin();
        } else {
            my_map[key]->second = value;
            li.splice(li.begin(), li, my_map[key]);
        }
    }
private:
    list<pair<int, int>> li;
    unordered_map<int, list<pair<int, int>>::iterator> my_map;
    int capacity;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache obj = new LRUCache(capacity);
 * int param_1 = obj.get(key);
 * obj.put(key,value);
 */
