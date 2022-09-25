/*
 * [25] Reverse Nodes in k-Group
 *
 * https://leetcode.com/problems/reverse-nodes-in-k-group/description/
 *
 * algorithms
 * Hard (31.12%)
 * Total Accepted:    113.2K
 * Total Submissions: 363.5K
 * Testcase Example:  '[]\n1'
 *
 *
 * Given a linked list, reverse the nodes of a linked list k at a time and
 * return its modified list.
 *
 *
 *
 * k is a positive integer and is less than or equal to the length of the
 * linked list. If the number of nodes is not a multiple of k then left-out
 * nodes in the end should remain as it is.
 *
 * You may not alter the values in the nodes, only nodes itself may be
 * changed.
 *
 * Only constant memory is allowed.
 *
 *
 * For example,
 * Given this linked list: 1->2->3->4->5
 *
 *
 *
 * For k = 2, you should return: 2->1->4->3->5
 *
 *
 *
 * For k = 3, you should return: 3->2->1->4->5
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

void reverse(struct ListNode* head) {
    struct ListNode* p1 = head->next;
    head->next = NULL;
    while (p1 != NULL) {
        struct ListNode* p2 = p1->next;
        p1->next = head->next;
        head->next = p1;
        p1 = p2;
    }
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (k <= 1) return head;
    struct ListNode node;
    node.next = head;
    for (struct ListNode* p1 = &node; p1->next != NULL;) {
        struct ListNode* p2 = p1;
        for (int i = 0; i < k && p2 != NULL; ++i) p2 = p2->next;
        if (p2 == NULL) break;
        struct ListNode* p3 = p2->next;
        p2->next = NULL;
        struct ListNode* p4 = p1->next;
        reverse(p1);
        p4->next = p3;
        p1 = p4;
    }
    return node.next;
}
