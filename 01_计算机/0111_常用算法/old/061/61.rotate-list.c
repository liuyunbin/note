/*
 * [61] Rotate List
 *
 * https://leetcode.com/problems/rotate-list/description/
 *
 * algorithms
 * Medium (24.39%)
 * Total Accepted:    125.5K
 * Total Submissions: 514.7K
 * Testcase Example:  '[1,2,3,4,5]\n2'
 *
 * Given a list, rotate the list to the right by k places, where k is
 * non-negative.
 * 
 * 
 * 
 * Example:
 * 
 * Given 1->2->3->4->5->NULL and k = 2,
 * 
 * return 4->5->1->2->3->NULL.
 * 
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* rotateRight(struct ListNode* head, int k) {
    int len = 0;
    for (struct ListNode* p = head; p != NULL; p = p->next)
        ++len;
    if (head == 0 || k%len == 0)
        return head;
    k %= len;
    struct ListNode* fast = head;
    for (int i = 0; i < k; ++i)
        fast = fast->next;
    struct ListNode* low  = head;
    while (fast->next != NULL) {
        fast = fast->next;
        low  = low->next;
    }
    fast->next = head;
    head       = low->next;
    low->next  = NULL;
    return head;
}
