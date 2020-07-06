/*
 * [82] Remove Duplicates from Sorted List II
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list-ii/description/
 *
 * algorithms
 * Medium (29.74%)
 * Total Accepted:    123.9K
 * Total Submissions: 416.7K
 * Testcase Example:  '[]'
 *
 * 
 * Given a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list.
 * 
 * 
 * For example,
 * Given 1->2->3->3->4->4->5, return 1->2->5.
 * Given 1->1->1->2->3, return 2->3.
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
    struct ListNode node;
    node.next = head;
    for (struct ListNode* p = &node; p->next != NULL && p->next->next != NULL; ) {
        if (p->next->val != p->next->next->val) {
            p = p->next;
            continue;
        }
        while (p->next->next != NULL && p->next->val == p->next->next->val)
            p->next = p->next->next;
        p->next = p->next->next;
    }
    return node.next;
}
