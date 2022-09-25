/*
 * [105] Construct Binary Tree from Preorder and Inorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/description/
 *
 * algorithms
 * Medium (32.96%)
 * Total Accepted:    122.2K
 * Total Submissions: 370.6K
 * Testcase Example:  '[]\n[]'
 *
 * Given preorder and inorder traversal of a tree, construct the binary tree.
 *
 * Note:
 * You may assume that duplicates do not exist in the tree.
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
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder,
                           int inorderSize) {
    if (preorderSize <= 0) return NULL;
    int k;
    for (k = 0; inorder[k] != preorder[0]; ++k)
        ;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = preorder[0];
    root->left = buildTree(preorder + 1, k, inorder, k);
    root->right = buildTree(preorder + k + 1, preorderSize - k - 1,
                            inorder + k + 1, inorderSize - k - 1);
    return root;
}
