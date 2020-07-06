/*
 * [148] Sort List
 *
 * https://leetcode.com/problems/sort-list/description/
 *
 * algorithms
 * Medium (29.35%)
 * Total Accepted:    121.2K
 * Total Submissions: 412.6K
 * Testcase Example:  '[]'
 *
 * Sort a linked list in O(n log n) time using constant space complexity.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* sortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode* fast = head;
    struct ListNode* low  = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        fast = fast->next->next;
        low  = low->next;
    }
    struct ListNode* p1 = sortList(low->next);
    low->next = NULL;
    struct ListNode* p2 = sortList(head);
    struct ListNode node;
    struct ListNode* p3 = &node;
    while (p1 != NULL && p2 != NULL)
        if (p1->val < p2->val) {
            p3 = p3->next = p1;
            p1 = p1->next;
        } else {
            p3 = p3->next = p2;
            p2 = p2->next;
        }
    if (p1 != NULL)
        p3->next = p1;
    else
        p3->next = p2;
    return node.next;
}
