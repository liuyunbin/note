/*
 * [19] Remove Nth Node From End of List
 *
 * https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/
 *
 * algorithms
 * Medium (34.02%)
 * Total Accepted:    214.4K
 * Total Submissions: 630.1K
 * Testcase Example:  '[1]\n1'
 *
 * Given a linked list, remove the nth node from the end of list and return its
 * head.
 * 
 * 
 * For example,
 * 
 * 
 * ⁠  Given linked list: 1->2->3->4->5, and n = 2.
 * 
 * ⁠  After removing the second node from the end, the linked list becomes
 * 1->2->3->5.
 * 
 * 
 * 
 * Note:
 * Given n will always be valid.
 * Try to do this in one pass.
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode node;
    node.next = head;
    struct ListNode* fast = &node;
    while (n > 0) {
        --n;
        fast = fast->next;
    }
    struct ListNode* low = &node;
    while (fast->next != NULL) {
        fast = fast->next;
        low  = low->next;
    }
    low->next = low->next->next;
    return node.next;
}
