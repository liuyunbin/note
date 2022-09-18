/*
 * [116] Populating Next Right Pointers in Each Node
 *
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node/description/
 *
 * algorithms
 * Medium (36.93%)
 * Total Accepted:    156.1K
 * Total Submissions: 422.6K
 * Testcase Example:  '{}'
 *
 * 
 * Given a binary tree
 * 
 * ⁠   struct TreeLinkNode {
 * ⁠     TreeLinkNode *left;
 * ⁠     TreeLinkNode *right;
 * ⁠     TreeLinkNode *next;
 * ⁠   }
 * 
 * 
 * 
 * Populate each next pointer to point to its next right node. If there is no
 * next right node, the next pointer should be set to NULL.
 * 
 * Initially, all next pointers are set to NULL.
 * 
 * 
 * Note:
 * 
 * You may only use constant extra space.
 * You may assume that it is a perfect binary tree (ie, all leaves are at the
 * same level, and every parent has two children).
 * 
 * 
 * 
 * 
 * For example,
 * Given the following perfect binary tree,
 * 
 * ⁠        1
 * ⁠      /  \
 * ⁠     2    3
 * ⁠    / \  / \
 * ⁠   4  5  6  7
 * 
 * 
 * 
 * After calling your function, the tree should look like:
 * 
 * ⁠        1 -> NULL
 * ⁠      /  \
 * ⁠     2 -> 3 -> NULL
 * ⁠    / \  / \
 * ⁠   4->5->6->7 -> NULL
 * 
 * 
 */
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  struct TreeLinkNode *left, *right, *next;
 * };
 *
 */
void connect(struct TreeLinkNode *root) {
    if (root == NULL)
        return ;
    connect(root->left);
    connect(root->right);
    struct TreeLinkNode* left  = root->left;
    struct TreeLinkNode* right = root->right;
    while (left != NULL) {
        left->next = right;
        left  = left->right;
        right = right->left;
    }
}
