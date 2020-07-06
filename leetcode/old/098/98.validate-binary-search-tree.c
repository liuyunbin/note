/*
 * [98] Validate Binary Search Tree
 *
 * https://leetcode.com/problems/validate-binary-search-tree/description/
 *
 * algorithms
 * Medium (23.85%)
 * Total Accepted:    205.9K
 * Total Submissions: 863.1K
 * Testcase Example:  '[2,1,3]'
 *
 * 
 * Given a binary tree, determine if it is a valid binary search tree (BST).
 * 
 * 
 * 
 * Assume a BST is defined as follows:
 * 
 * The left subtree of a node contains only nodes with keys less than the
 * node's key.
 * The right subtree of a node contains only nodes with keys greater than the
 * node's key.
 * Both the left and right subtrees must also be binary search trees.
 * 
 * 
 * 
 * Example 1:
 * 
 * ⁠   2
 * ⁠  / \
 * ⁠ 1   3
 * 
 * Binary tree [2,1,3], return true.
 * 
 * 
 * Example 2:
 * 
 * ⁠   1
 * ⁠  / \
 * ⁠ 2   3
 * 
 * Binary tree [1,2,3], return false.
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

bool check_left(const struct TreeNode* root, int val) {
    if (root == NULL)
        return true;
    return root->val < val && check_left(root->left, val) && check_left(root->right, val);
}

bool check_right(const struct TreeNode* root, int val) {
    if (root == NULL)
        return true;
    return root->val > val && check_right(root->left, val) && check_right(root->right, val);
}

bool isValidBST(struct TreeNode* root) {
    if (root == NULL)
        return true;
    return isValidBST(root->left) && isValidBST(root->right) && check_left(root->left, root->val) && check_right(root->right, root->val);
}
