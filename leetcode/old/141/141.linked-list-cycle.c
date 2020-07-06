/*
 * [141] Linked List Cycle
 *
 * https://leetcode.com/problems/linked-list-cycle/description/
 *
 * algorithms
 * Easy (35.20%)
 * Total Accepted:    219.6K
 * Total Submissions: 624K
 * Testcase Example:  '[]\nno cycle'
 *
 * 
 * Given a linked list, determine if it has a cycle in it.
 * 
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
bool hasCycle(struct ListNode *head) {
    if (head == NULL)
        return false;
    struct ListNode* fast = head;
    struct ListNode* low  = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        low  = low->next;
        if (low == fast)
            return true;
    }
    return false;
}
