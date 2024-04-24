/*
 * [145] Binary Tree Postorder Traversal
 *
 * https://leetcode.com/problems/binary-tree-postorder-traversal/description/
 *
 * algorithms
 * Hard (41.06%)
 * Total Accepted:    162K
 * Total Submissions: 394.2K
 * Testcase Example:  '[]'
 *
 * Given a binary tree, return the postorder traversal of its nodes' values.
 *
 *
 * For example:
 * Given binary tree {1,#,2,3},
 *
 * ⁠  1
 * ⁠   \
 * ⁠    2
 * ⁠   /
 * ⁠  3
 *
 *
 *
 * return [3,2,1].
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
    vector<int> postorderTraversal(TreeNode* root) {
        vector<int> result;
        stack<TreeNode*> my_stack;
        TreeNode* prev_node = NULL;
        while (root != NULL || !my_stack.empty()) {
            if (root != NULL) {
                my_stack.push(root);
                root = root->left;
            } else {
                TreeNode* temp = my_stack.top();
                if (temp->right == NULL || temp->right == prev_node) {
                    result.push_back(temp->val);
                    my_stack.pop();
                    prev_node = temp;
                } else {
                    root = temp->right;
                }
            }
        }
        return result;
    }
};
