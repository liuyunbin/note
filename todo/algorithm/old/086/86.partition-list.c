/*
 * [86] Partition List
 *
 * https://leetcode.com/problems/partition-list/description/
 *
 * algorithms
 * Medium (33.17%)
 * Total Accepted:    113.7K
 * Total Submissions: 342.8K
 * Testcase Example:  '[]\n0'
 *
 * Given a linked list and a value x, partition it such that all nodes less
 * than x come before nodes greater than or equal to x.
 *
 *
 * You should preserve the original relative order of the nodes in each of the
 * two partitions.
 *
 *
 * For example,
 * Given 1->4->3->2->5->2 and x = 3,
 * return 1->2->2->4->3->5.
 *
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode node1, node2;
    node1.next = head;
    struct ListNode* p1 = &node1;
    struct ListNode* p2 = &node2;
    while (p1->next != NULL)
        if (p1->next->val < x)
            p1 = p1->next;
        else {
            p2 = p2->next = p1->next;
            p1->next = p2->next;
        }
    p2->next = NULL;
    p1->next = node2.next;
    return node1.next;
}
