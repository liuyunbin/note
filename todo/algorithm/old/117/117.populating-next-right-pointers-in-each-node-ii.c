/*
 * [117] Populating Next Right Pointers in Each Node II
 *
 * https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/description/
 *
 * algorithms
 * Medium (33.89%)
 * Total Accepted:    116.7K
 * Total Submissions: 344.1K
 * Testcase Example:  '{}'
 *
 * Follow up for problem "Populating Next Right Pointers in Each Node".
 * What if the given tree could be any binary tree? Would your previous
 * solution still work?
 *
 * Note:
 * You may only use constant extra space.
 *
 *
 * For example,
 * Given the following binary tree,
 *
 * ⁠        1
 * ⁠      /  \
 * ⁠     2    3
 * ⁠    / \    \
 * ⁠   4   5    7
 *
 *
 *
 * After calling your function, the tree should look like:
 *
 * ⁠        1 -> NULL
 * ⁠      /  \
 * ⁠     2 -> 3 -> NULL
 * ⁠    / \    \
 * ⁠   4-> 5 -> 7 -> NULL
 *
 *
 */
/**
 * Definition for binary tree with next pointer.
 * struct TreeLinkNode {
 *  int val;
 *  struct TreeLinkNode *left, *right, *next;
 * };
 *
 */
void connect(struct TreeLinkNode* root) {
    while (root != NULL) {
        struct TreeLinkNode* next_root = NULL;
        struct TreeLinkNode* prev_root = NULL;
        while (root != NULL) {
            if (root->left != NULL) {
                if (next_root == NULL) next_root = root->left;
                if (prev_root != NULL) prev_root->next = root->left;
                prev_root = root->left;
            }
            if (root->right != NULL) {
                if (next_root == NULL) next_root = root->right;
                if (prev_root != NULL) prev_root->next = root->right;
                prev_root = root->right;
            }
            root = root->next;
        }
        root = next_root;
    }
}
