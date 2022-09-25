/*
 * [143] Reorder List
 *
 * https://leetcode.com/problems/reorder-list/description/
 *
 * algorithms
 * Medium (26.23%)
 * Total Accepted:    104.5K
 * Total Submissions: 397.9K
 * Testcase Example:  '[1,2,3,4]'
 *
 *
 * Given a singly linked list L: L0→L1→…→Ln-1→Ln,
 * reorder it to: L0→Ln→L1→Ln-1→L2→Ln-2→…
 *
 *
 * You must do this in-place without altering the nodes' values.
 *
 *
 * For example,
 * Given {1,2,3,4}, reorder it to {1,4,2,3}.
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
void reorderList(struct ListNode* head) {
    if (head == NULL || head->next == NULL) return;
    struct ListNode* fast = head;
    struct ListNode* low = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        low = low->next;
    }
    struct ListNode* p = low->next;
    low->next = NULL;
    struct ListNode node;
    node.next = NULL;
    while (p != NULL) {
        struct ListNode* q = p->next;
        p->next = node.next;
        node.next = p;
        p = q;
    }
    p = node.next;
    while (p != NULL) {
        struct ListNode* q = p->next;
        p->next = head->next;
        head->next = p;
        head = p->next;
        p = q;
    }
}
