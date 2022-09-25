/*
 * [94] Binary Tree Inorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-inorder-traversal/description/
 *
 * algorithms
 * Medium (48.18%)
 * Total Accepted:    242.5K
 * Total Submissions: 503K
 * Testcase Example:  '[1,null,2,3]'
 *
 * Given a binary tree, return the inorder traversal of its nodes' values.
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
 * return [1,3,2].
 *
 *
 * Note: Recursive solution is trivial, could you do it iteratively?
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
   public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        backtrack(root, result);
        return result;
    }

    void backtrack(TreeNode* root, vector<int>& result) {
        if (root == NULL) return;
        backtrack(root->left, result);
        result.push_back(root->val);
        backtrack(root->right, result);
    }
};
