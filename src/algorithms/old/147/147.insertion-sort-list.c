/*
 * [147] Insertion Sort List
 *
 * https://leetcode.com/problems/insertion-sort-list/description/
 *
 * algorithms
 * Medium (33.55%)
 * Total Accepted:    112.4K
 * Total Submissions: 334.8K
 * Testcase Example:  '[]'
 *
 * Sort a linked list using insertion sort.
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* insertionSortList(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode node;
    node.next = NULL;
    while (head != NULL) {
        struct ListNode* p1 = head;
        head = head->next;
        struct ListNode* p2 = &node;
        while (p2->next != NULL && p2->next->val < p1->val)
            p2 = p2->next;
        p1->next = p2->next;
        p2->next = p1;
    }
    return node.next;
}
