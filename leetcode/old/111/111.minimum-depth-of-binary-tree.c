/*
 * [111] Minimum Depth of Binary Tree
 *
 * https://leetcode.com/problems/minimum-depth-of-binary-tree/description/
 *
 * algorithms
 * Easy (33.42%)
 * Total Accepted:    195.1K
 * Total Submissions: 583.7K
 * Testcase Example:  '[]'
 *
 * Given a binary tree, find its minimum depth.
 * 
 * The minimum depth is the number of nodes along the shortest path from the
 * root node down to the nearest leaf node.
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

int min(int x, int y) {
    return x > y ? y : x;
}

int minDepth(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    if (root->left == NULL && root->right == NULL)
        return 1;
    if (root->left != NULL && root->right != NULL)
        return 1 + min(minDepth(root->left), minDepth(root->right));
    if (root->left != NULL)
        return 1 + minDepth(root->left);
    return 1 + minDepth(root->right);
}
