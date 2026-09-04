/*
 * [21] Merge Two Sorted Lists
 *
 * https://leetcode.com/problems/merge-two-sorted-lists/description/
 *
 * algorithms
 * Easy (39.62%)
 * Total Accepted:    291K
 * Total Submissions: 734.2K
 * Testcase Example:  '[1,2,4]\n[1,3,4]'
 *
 * Merge two sorted linked lists and return it as a new list. The new list
 * should be made by splicing together the nodes of the first two lists.
 *
 * Example:
 *
 * Input: 1->2->4, 1->3->4
 * Output: 1->1->2->3->4->4
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
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode node;
    struct ListNode* l3 = &node;
    while (l1 != NULL && l2 != NULL)
        if (l1->val < l2->val) {
            l3 = l3->next = l1;
            l1 = l1->next;
        } else {
            l3 = l3->next = l2;
            l2 = l2->next;
        }
    if (l1 != NULL)
        l3->next = l1;
    else
        l3->next = l2;
    return node.next;
}
