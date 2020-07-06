/*
 * [138] Copy List with Random Pointer
 *
 * https://leetcode.com/problems/copy-list-with-random-pointer/description/
 *
 * algorithms
 * Medium (26.02%)
 * Total Accepted:    138.9K
 * Total Submissions: 533.8K
 * Testcase Example:  '{}'
 *
 * 
 * A linked list is given such that each node contains an additional random
 * pointer which could point to any node in the list or null.
 * 
 * 
 * 
 * Return a deep copy of the list.
 * 
 */
/**
 * Definition for singly-linked list with a random pointer.
 * struct RandomListNode {
 *     int label;
 *     struct RandomListNode *next;
 *     struct RandomListNode *random;
 * };
 */
struct RandomListNode *copyRandomList(struct RandomListNode *head) {
    if (head == NULL)
        return NULL;
    for (struct RandomListNode* p = head; p != NULL; ) {
        struct RandomListNode* q = (struct RandomListNode*)malloc(sizeof(struct RandomListNode));
        q->next  = p->next;
        q->label = p->label;
        p->next  = q;
        p = q->next;
    }
    for (struct RandomListNode* p = head; p != NULL; p = p->next->next)
        if (p->random == NULL)
            p->next->random = NULL;
        else
            p->next->random = p->random->next;
    struct RandomListNode* new_head = head->next;
    while (head != NULL) {
        struct RandomListNode* p = head->next;
        head = head->next = head->next->next;
        if (head != NULL)
            p->next = head->next;
        else
            p->next = NULL;
    }
    return new_head;
}
