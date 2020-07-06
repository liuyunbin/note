/*
 * [142] Linked List Cycle II
 *
 * https://leetcode.com/problems/linked-list-cycle-ii/description/
 *
 * algorithms
 * Medium (30.85%)
 * Total Accepted:    133.1K
 * Total Submissions: 431.5K
 * Testcase Example:  '[]\nno cycle'
 *
 * 
 * Given a linked list, return the node where the cycle begins. If there is no
 * cycle, return null.
 * 
 * 
 * 
 * Note: Do not modify the linked list.
 * 
 * 
 * Follow up:
 * Can you solve it without using extra space?
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode *detectCycle(struct ListNode *head) {
    if (head == NULL)
        return NULL;
    struct ListNode* fast = head;
    struct ListNode* low  = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        low  = low->next;
        if (low == fast) {
            fast = head;
            while (true) {
                if (low == fast)
                    return low;
                low  =  low->next;
                fast = fast->next;
            }
        }
    }
    return NULL;
}
