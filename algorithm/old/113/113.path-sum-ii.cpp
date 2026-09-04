/*
 * [113] Path Sum II
 *
 * https://leetcode.com/problems/path-sum-ii/description/
 *
 * algorithms
 * Medium (34.80%)
 * Total Accepted:    149K
 * Total Submissions: 428.1K
 * Testcase Example:  '[5,4,8,11,null,13,4,7,2,null,null,5,1]\n22'
 *
 *
 * Given a binary tree and a sum, find all root-to-leaf paths where each path's
 * sum equals the given sum.
 *
 *
 * For example:
 * Given the below binary tree and sum = 22,
 *
 * ⁠             5
 * ⁠            / \
 * ⁠           4   8
 * ⁠          /   / \
 * ⁠         11  13  4
 * ⁠        /  \    / \
 * ⁠       7    2  5   1
 *
 *
 *
 * return
 *
 * [
 * ⁠  [5,4,11,2],
 * ⁠  [5,8,4,5]
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
    vector<vector<int>> pathSum(TreeNode* root, int sum) {
        vector<vector<int>> result;
        vector<int> temp;
        backtrack(root, sum, temp, result);
        return result;
    }

    void backtrack(const TreeNode* root, int sum, vector<int>& temp,
                   vector<vector<int>>& result) {
        if (root == NULL) return;
        if (root->left == NULL && root->right == NULL) {
            if (root->val == sum) {
                temp.push_back(sum);
                result.push_back(temp);
                temp.pop_back();
            }
            return;
        }
        temp.push_back(root->val);
        backtrack(root->left, sum - root->val, temp, result);
        backtrack(root->right, sum - root->val, temp, result);
        temp.pop_back();
    }
};
