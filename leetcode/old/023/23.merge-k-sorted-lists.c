/*
 * [23] Merge k Sorted Lists
 *
 * https://leetcode.com/problems/merge-k-sorted-lists/description/
 *
 * algorithms
 * Hard (27.83%)
 * Total Accepted:    190.4K
 * Total Submissions: 684K
 * Testcase Example:  '[]'
 *
 * 
 * Merge k sorted linked lists and return it as one sorted list. Analyze and
 * describe its complexity.
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize <= 0)
        return NULL;
    if (listsSize == 1)
        return lists[0];
    struct ListNode* left  = mergeKLists(lists, listsSize / 2);
    struct ListNode* right = mergeKLists(lists + listsSize / 2, listsSize - listsSize / 2);
    struct ListNode  node;
    struct ListNode* p = &node;
    while (left != NULL && right != NULL)
        if (left->val < right->val) {
            p = p->next = left;
            left = left->next;
        } else {
            p = p->next = right;
            right = right->next;
        }
    if (left != NULL)
        p->next = left;
    else
        p->next = right;
    return node.next;
}
