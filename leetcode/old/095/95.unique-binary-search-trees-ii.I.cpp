/*
 * [95] Unique Binary Search Trees II
 *
 * https://leetcode.com/problems/unique-binary-search-trees-ii/description/
 *
 * algorithms
 * Medium (31.86%)
 * Total Accepted:    93.8K
 * Total Submissions: 294.2K
 * Testcase Example:  '3'
 *
 * Given an integer n, generate all structurally unique BST's (binary search
 * trees) that store values 1...n.
 * 
 * 
 * For example,
 * Given n = 3, your program should return all 5 unique BST's shown below.
 * 
 * 
 * ⁠  1         3     3      2      1
 * ⁠   \       /     /      / \      \
 * ⁠    3     2     1      1   3      2
 * ⁠   /     /       \                 \
 * ⁠  2     1         2                 3
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
    vector<TreeNode*> generateTrees(int n) {
        if (n <= 0)
            return vector<TreeNode*>();
        return backtrack(1, n);
    }

    vector<TreeNode*> backtrack(int left, int right) {
        vector<TreeNode*> result;
        if (left > right) {
            result.push_back(NULL);
            return result;
        }
        for (int k = left; k <= right; ++k) {
            vector<TreeNode*> result_left  = backtrack(left, k - 1);
            vector<TreeNode*> result_right = backtrack(k + 1, right);
            for (int i = 0; i < result_left.size(); ++i)
                for (int j = 0; j < result_right.size(); ++j) {
                    TreeNode* temp = new TreeNode(k);
                    temp->left  = result_left[i];
                    temp->right = result_right[j];
                    result.push_back(temp);
                }
        }
        return result;
    }
};
