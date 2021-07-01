/*
 * [2] Add Two Numbers
 *
 * https://leetcode.com/problems/add-two-numbers/description/
 *
 * algorithms
 * Medium (29.26%)
 * Total Accepted:    622K
 * Total Submissions: 2.1M
 * Testcase Example:  '[2,4,3]\n[5,6,4]'
 *
 * You are given two non-empty linked lists representing two non-negative
 * integers. The digits are stored in reverse order and each of their nodes
 * contain a single digit. Add the two numbers and return it as a linked list.
 *
 * You may assume the two numbers do not contain any leading zero, except the
 * number 0 itself.
 *
 * Example:
 *
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
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode node(0);
        ListNode* l3 = &node;
        int count = 0;
        while (l1 != NULL || l2 != NULL) {
            if (l1 != NULL) {
                count += l1->val;
                l1 = l1->next;
            }
            if (l2 != NULL) {
                count += l2->val;
                l2 = l2->next;
            }
            l3 = l3->next = new ListNode(count%10);
            count /= 10;
        }
        if (count == 1)
            l3 = l3->next = new ListNode(1);
        l3->next = NULL;
        return node.next;
    }
};
