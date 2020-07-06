/*
 * [107] Binary Tree Level Order Traversal II
 *
 * https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
 *
 * algorithms
 * Easy (41.25%)
 * Total Accepted:    149.4K
 * Total Submissions: 362K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the bottom-up level order traversal of its
 * nodes' values. (ie, from left to right, level by level from leaf to root).
 * 
 * 
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 
 * 
 * return its bottom-up level order traversal as:
 * 
 * [
 * ⁠ [15,7],
 * ⁠ [9,20],
 * ⁠ [3]
 * ]
 * 
 * 
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
    vector<vector<int>> levelOrderBottom(TreeNode* root) {
        int depth = get_depth(root);
        vector<vector<int>> result(depth, vector<int>());
        backtrack(root, depth - 1, result);
        return result;
    }

    void backtrack(const TreeNode* root, int k, vector<vector<int>>& result) {
        if (root == NULL)
            return ;
        backtrack(root->left,  k - 1, result);
        result[k].push_back(root->val);
        backtrack(root->right, k - 1, result);
    }

    int get_depth(TreeNode* root) {
        if (root == NULL)
            return 0;
        return 1 + max(get_depth(root->left), get_depth(root->right));
    }


};
