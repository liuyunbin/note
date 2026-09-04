/*
 * [99] Recover Binary Search Tree
 *
 * https://leetcode.com/problems/recover-binary-search-tree/description/
 *
 * algorithms
 * Hard (30.52%)
 * Total Accepted:    82.5K
 * Total Submissions: 270K
 * Testcase Example:  '[0,1]'
 *
 *
 * Two elements of a binary search tree (BST) are swapped by mistake.
 *
 * Recover the tree without changing its structure.
 *
 *
 * Note:
 * A solution using O(n) space is pretty straight forward. Could you devise a
 * constant space solution?
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

void function(const struct TreeNode* root, struct TreeNode** previous,
              struct TreeNode** p1, struct TreeNode** p2) {
    if (root == NULL) return;
    function(root->left, previous, p1, p2);
    if (*previous != NULL)
        if ((*previous)->val >= root->val) {
            if (*p1 == NULL) *p1 = *previous;
            *p2 = root;
        }
    *previous = root;
    function(root->right, previous, p1, p2);
}

void recoverTree(struct TreeNode* root) {
    struct TreeNode* p1 = NULL;
    struct TreeNode* p2 = NULL;
    struct TreeNode* previous = NULL;
    function(root, &previous, &p1, &p2);
    int val = p1->val;
    p1->val = p2->val;
    p2->val = val;
}
