/*
 * [2] Add Two Numbers
 *
 * https://leetcode.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (28.18%)
 * Total Accepted:    406K
 * Total Submissions: 1.4M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 *
 *
 * Example
 *
 * Input: (2 -> 4 -> 3) + (5 -> 6 -> 4)
 * Output: 7 -> 0 -> 8
 * Explanation: 342 + 465 = 807.
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
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode node;
    struct ListNode* l3 = &node;
    int count = 0;
    while (l1 != NULL || l2 != NULL || count != 0) {
        if (l1 != NULL) {
            count += l1->val;
            l1 = l1->next;
        }
        if (l2 != NULL) {
            count += l2->val;
            l2 = l2->next;
        }
        l3 = l3->next = (struct ListNode*)malloc(sizeof(struct ListNode));
        l3->val = count % 10;
        count /= 10;
    }
    l3->next = NULL;
    return node.next;
}
