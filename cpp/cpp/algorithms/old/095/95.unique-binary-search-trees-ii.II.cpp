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
        vector<TreeNode*> result;
        if (n <= 0) return result;
        result.push_back(NULL);
        for (int k = 1; k <= n; ++k) {
            vector<TreeNode*> new_result;
            for (auto it : result) {
                TreeNode* temp = new TreeNode(k);
                temp->left = copy(it);
                temp->right = NULL;
                new_result.push_back(temp);
                if (it != NULL) {
                    TreeNode* p = it;
                    while (p->right != NULL) {
                        TreeNode* right = p->right;
                        p->right = new TreeNode(k);
                        p->right->left = right;
                        new_result.push_back(copy(it));
                        p = p->right = right;
                    }
                    p->right = new TreeNode(k);
                    new_result.push_back(copy(it));
                    p->right = NULL;
                }
            }
            result.swap(new_result);
        }
        return result;
    }

    TreeNode* copy(TreeNode* root) {
        if (root == NULL) return NULL;
        TreeNode* new_root = new TreeNode(root->val);
        new_root->left = copy(root->left);
        new_root->right = copy(root->right);
        return new_root;
    }
};
