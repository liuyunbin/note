/*
 * [106] Construct Binary Tree from Inorder and Postorder Traversal
 *
 * https://leetcode.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/description/
 *
 * algorithms
 * Medium (32.68%)
 * Total Accepted:    97.8K
 * Total Submissions: 299.2K
 * Testcase Example:  '[]\n[]'
 *
 * Given inorder and postorder traversal of a tree, construct the binary tree.
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
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder,
                           int postorderSize) {
    if (inorderSize <= 0) return NULL;
    int k;
    for (k = 0; inorder[k] != postorder[postorderSize - 1]; ++k)
        ;
    struct TreeNode* root = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    root->val = inorder[k];
    root->left = buildTree(inorder, k, postorder, k);
    root->right = buildTree(inorder + k + 1, inorderSize - k - 1, postorder + k,
                            postorderSize - k - 1);
    return root;
}
