/*
 * [129] Sum Root to Leaf Numbers
 *
 * https://leetcode.com/problems/sum-root-to-leaf-numbers/description/
 *
 * algorithms
 * Medium (37.29%)
 * Total Accepted:    125.6K
 * Total Submissions: 336.7K
 * Testcase Example:  '[]'
 *
 * Given a binary tree containing digits from 0-9 only, each root-to-leaf path
 * could represent a number.
 * An example is the root-to-leaf path 1->2->3 which represents the number
 * 123.
 *
 * Find the total sum of all root-to-leaf numbers.
 *
 * For example,
 *
 * ⁠   1
 * ⁠  / \
 * ⁠ 2   3
 *
 *
 *
 * The root-to-leaf path 1->2 represents the number 12.
 * The root-to-leaf path 1->3 represents the number 13.
 *
 *
 * Return the sum = 12 + 13 = 25.
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

void function(const struct TreeNode* root, int val, int* result) {
    if (root == NULL) return;
    val = val * 10 + root->val;
    if (root->left == NULL && root->right == NULL) {
        *result += val;
        return;
    }
    function(root->left, val, result);
    function(root->right, val, result);
}

int sumNumbers(struct TreeNode* root) {
    int result = 0;
    function(root, 0, &result);
    return result;
}
