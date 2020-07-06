/*
 * [146] LRU Cache
 *
 * https://leetcode.com/problems/lru-cache
 *
 * algorithms
 * Hard (18.76%)
 * Total Accepted:    150K
 * Total Submissions: 799K
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
 * LRUCache cache = new LRUCache( 2  capacity  );
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

struct Node {
    int key;
    int val;
    struct Node* prev;
    struct Node* next;
};

#define HASH_SIZE 911
struct HashNode {
    int              key;
    struct Node*     val;
    struct HashNode* next;
};

struct Hash {
    struct HashNode hash[HASH_SIZE];
};

void hash_init(struct Hash* self) {
    for (int i = 0; i < HASH_SIZE; ++i)
        self->hash[i].next = NULL;
}

void hash_insert(struct Hash* self, int key, struct Node* val) {
    struct HashNode* p = self->hash + abs(key)%HASH_SIZE;
    struct HashNode* new_node = (struct HashNode*)malloc(sizeof(struct HashNode));
    new_node->key  = key;
    new_node->val  = val;
    new_node->next = p->next;
    p->next = new_node;
}

struct Node* hash_get(struct Hash* self, int key) {
    struct HashNode* p = self->hash + abs(key)%HASH_SIZE;
    while (p->next != NULL) {
        p = p->next;
        if (p->key == key)
            return p->val;
    }
    return NULL;
}

void hash_erase(struct Hash* self, int key) {
    struct HashNode* p = self->hash + abs(key)%HASH_SIZE;
    while (p->next != NULL) {
        if (p->next->key == key) {
            struct HashNode* q = p->next;
            p->next = q->next;
            free(q);
            return ;
        }
        p = p->next;
    }
}

void hash_free(struct Hash* self) {
    for (int i = 0; i < HASH_SIZE; ++i)
        while (self->hash[i].next != NULL) {
            struct HashNode* p = self->hash[i].next;
            self->hash[i].next = p->next;
            free(p->val);
            free(p);
        }
}

typedef struct {
    struct Hash hash;
    struct Node node;
    int size;
    int current_size;
} LRUCache;

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* self = (LRUCache*)malloc(sizeof(LRUCache));
    self->size = capacity;
    self->current_size = 0;
    hash_init(&(self->hash));
    self->node.next = self->node.prev = &(self->node);
    return self;
}

int lRUCacheGet(LRUCache* obj, int key) {
    struct Node* p = hash_get(&obj->hash, key);
    if (p == NULL)
        return -1;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    p->next = obj->node.next;
    p->prev = &(obj->node);
    p->prev->next = p->next->prev = p;
    return p->val;
}

void lRUCachePut(LRUCache* obj, int key, int val) {
    struct Node* p = hash_get(&obj->hash, key);
    if (p != NULL) {
        p->val = val;
        p->prev->next = p->next;
        p->next->prev = p->prev;
        p->next = obj->node.next;
        p->prev = &obj->node;
        p->prev->next = p->next->prev = p;
        return ;
    }
    if (obj->current_size < obj->size) {
        ++obj->current_size;
        struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
        new_node->key  = key;
        new_node->val  = val;
        new_node->next = obj->node.next;
        new_node->prev = &obj->node;
        new_node->next->prev = new_node->prev->next = new_node;
        hash_insert(&obj->hash, key, new_node);
        return ;
    }
    p = obj->node.prev;
    p->prev->next = p->next;
    p->next->prev = p->prev;
    hash_erase(&obj->hash, p->key);
    p->key = key;
    p->val = val;
    p->next = obj->node.next;
    p->prev = &obj->node;
    p->prev->next = p->next->prev = p;
    hash_insert(&obj->hash, p->key, p);
}

void lRUCacheFree(LRUCache* obj) {
    hash_free(&obj->hash);
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * struct LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 * lRUCachePut(obj, key, value);
 * lRUCacheFree(obj);
 */
