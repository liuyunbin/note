/*
 * [114] Flatten Binary Tree to Linked List
 *
 * https://leetcode.com/problems/flatten-binary-tree-to-linked-list/description/
 *
 * algorithms
 * Medium (35.92%)
 * Total Accepted:    148.8K
 * Total Submissions: 414.1K
 * Testcase Example:  '[]'
 *
 * 
 * Given a binary tree, flatten it to a linked list in-place.
 * 
 * 
 * 
 * For example,
 * Given
 * 
 * ⁠        1
 * ⁠       / \
 * ⁠      2   5
 * ⁠     / \   \
 * ⁠    3   4   6
 * 
 * 
 * 
 * The flattened tree should look like:
 * 
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠     \
 * ⁠      3
 * ⁠       \
 * ⁠        4
 * ⁠         \
 * ⁠          5
 * ⁠           \
 * ⁠            6
 * 
 * 
 * click to show hints.
 * 
 * Hints:
 * If you notice carefully in the flattened tree, each node's right child
 * points to the next node of a pre-order traversal.
 * 
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void flatten(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    if (root->left == NULL)
        return flatten(root->right);
    struct TreeNode* p = root->left;
    while (p->right != NULL)
        p = p->right;
    p->right = root->right;
    root->right = root->left;
    root->left  = NULL;
    flatten(root->right);
}
