/*
 * [110] Balanced Binary Tree
 *
 * https://leetcode.com/problems/balanced-binary-tree/description/
 *
 * algorithms
 * Easy (38.01%)
 * Total Accepted:    204.6K
 * Total Submissions: 538.2K
 * Testcase Example:  '[]'
 *
 * Given a binary tree, determine if it is height-balanced.
 *
 *
 *
 * For this problem, a height-balanced binary tree is defined as a binary tree
 * in which the depth of the two subtrees of every node never differ by more
 * than 1.
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

int max(int x, int y) { return x > y ? x : y; }

int function(const struct TreeNode* root) {
    if (root == NULL) return 0;
    return 1 + max(function(root->left), function(root->right));
}

bool isBalanced(struct TreeNode* root) {
    if (root == NULL) return true;
    return isBalanced(root->left) && isBalanced(root->right) &&
           abs(function(root->left) - function(root->right)) <= 1;
}
