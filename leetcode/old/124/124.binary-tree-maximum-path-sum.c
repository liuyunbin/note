/*
 * [124] Binary Tree Maximum Path Sum
 *
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
 *
 * algorithms
 * Hard (26.75%)
 * Total Accepted:    114.8K
 * Total Submissions: 429K
 * Testcase Example:  '[1,2,3]'
 *
 * 
 * Given a binary tree, find the maximum path sum.
 * 
 * 
 * For this problem, a path is defined as any sequence of nodes from some
 * starting node to any node in the tree along the parent-child connections.
 * The path must contain at least one node and does not need to go through the
 * root.
 * 
 * 
 * For example:
 * Given the below binary tree,
 * 
 * ⁠      1
 * ⁠     / \
 * ⁠    2   3
 * 
 * 
 * 
 * Return 6.
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

int max(int x, int y) {
    return x > y ? x : y;
}

int backtrack(struct TreeNode* root, int* result) {
    if (root == NULL)
        return 0;
    int left  = max(0, backtrack(root->left,  result));
    int right = max(0, backtrack(root->right, result));
    *result   = max(*result, root->val + left + right);
    return root->val + max(left, right);
}

int maxPathSum(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int result = INT_MIN;
    backtrack(root, &result);
    return result;
}
