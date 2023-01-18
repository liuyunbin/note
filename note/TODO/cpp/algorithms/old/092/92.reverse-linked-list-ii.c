/*
 * [92] Reverse Linked List II
 *
 * https://leetcode.com/problems/reverse-linked-list-ii/description/
 *
 * algorithms
 * Medium (31.07%)
 * Total Accepted:    126.9K
 * Total Submissions: 408.4K
 * Testcase Example:  '[5]\n1\n1'
 *
 *
 * Reverse a linked list from position m to n. Do it in-place and in
 * one-pass.
 *
 *
 *
 * For example:
 * Given 1->2->3->4->5->NULL, m = 2 and n = 4,
 *
 *
 * return 1->4->3->2->5->NULL.
 *
 *
 * Note:
 * Given m, n satisfy the following condition:
 * 1 ≤ m ≤ n ≤ length of list.
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int m, int n) {
    struct ListNode node;
    node.next = head;
    struct ListNode* p1 = &node;
    while (m > 1) {
        p1 = p1->next;
        --m;
    }
    struct ListNode* p2 = &node;
    while (n > 0) {
        p2 = p2->next;
        --n;
    }
    struct ListNode* p3 = p1->next;
    p1->next = p2->next;
    p2->next = NULL;
    while (p3 != NULL) {
        p2 = p3->next;
        p3->next = p1->next;
        p1->next = p3;
        p3 = p2;
    }
    return node.next;
}
