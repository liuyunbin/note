/*
 * [83] Remove Duplicates from Sorted List
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
 *
 * algorithms
 * Easy (40.08%)
 * Total Accepted:    213.7K
 * Total Submissions: 533K
 * Testcase Example:  '[]'
 *
 *
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 *
 *
 * For example,
 * Given 1->1->2, return 1->2.
 * Given 1->1->2->3->3, return 1->2->3.
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    if (head == NULL) return head;
    for (struct ListNode* p = head; p->next != NULL;)
        if (p->val == p->next->val)
            p->next = p->next->next;
        else
            p = p->next;
    return head;
}
