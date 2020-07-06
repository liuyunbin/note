/*
 * [144] Binary Tree Preorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-preorder-traversal/description/
 *
 * algorithms
 * Medium (45.97%)
 * Total Accepted:    205.4K
 * Total Submissions: 446.4K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the preorder traversal of its nodes' values.
 * 
 * 
 * For example:
 * Given binary tree [1,null,2,3],
 * 
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 * 
 * 
 * 
 * return [1,2,3].
 * 
 * 
 * Note: Recursive solution is trivial, could you do it iteratively?
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */

#define MAX 1000
void function(struct TreeNode* root, int* result, int* returnSize) {
    if (root == NULL)
        return ;
    result[(*returnSize)++] = root->val;
    function(root->left,  result, returnSize);
    function(root->right, result, returnSize);
}

int* preorderTraversal(struct TreeNode* root, int* returnSize) {
    int* result = (int*)malloc(sizeof(int)*MAX);
    *returnSize = 0;
    function(root, result, returnSize);
    return result;
}
