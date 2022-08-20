/*
 * [103] Binary Tree Zigzag Level Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/description/
 *
 * algorithms
 * Medium (35.82%)
 * Total Accepted:    121.4K
 * Total Submissions: 338.6K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the zigzag level order traversal of its nodes'
 * values. (ie, from left to right, then right to left for the next level and
 * alternate between).
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
 * return its zigzag level order traversal as:
 * 
 * [
 * ⁠ [3],
 * ⁠ [20,9],
 * ⁠ [15,7]
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
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> result;
        backtrack(root, 0, result);
        for (int i = 1; i < result.size(); i += 2)
            reverse(result[i].begin(), result[i].end());
        return result;
    }

    void backtrack(const TreeNode* root, int k, vector<vector<int>>& result) {
        if (root == NULL)
            return ;
        if (result.size() == k)
            result.push_back(vector<int>());
        backtrack(root->left,  k + 1, result);
        result[k].push_back(root->val);
        backtrack(root->right, k + 1, result);
    }
};
