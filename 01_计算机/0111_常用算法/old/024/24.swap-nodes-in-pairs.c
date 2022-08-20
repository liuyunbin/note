/*
 * [24] Swap Nodes in Pairs
 *
 * https://leetcode.com/problems/swap-nodes-in-pairs/description/
 *
 * algorithms
 * Medium (38.78%)
 * Total Accepted:    193.3K
 * Total Submissions: 498.5K
 * Testcase Example:  '[]'
 *
 * 
 * Given a linked list, swap every two adjacent nodes and return its head.
 * 
 * 
 * 
 * For example,
 * Given 1->2->3->4, you should return the list as 2->1->4->3.
 * 
 * 
 * 
 * Your algorithm should use only constant space. You may not modify the values
 * in the list, only nodes itself can be changed.
 * 
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* swapPairs(struct ListNode* head) {
    if (head == NULL || head->next == NULL)
        return head;
    struct ListNode node;
    node.next = head;
    for (struct ListNode* p1 = &node; p1->next != NULL && p1->next->next != NULL; ) {
        struct ListNode* p2 = p1->next;
        struct ListNode* p3 = p2->next;
        p2->next = p3->next;
        p3->next = p2;
        p1->next = p3;
        p1 = p2;
    }
    return node.next;
}
