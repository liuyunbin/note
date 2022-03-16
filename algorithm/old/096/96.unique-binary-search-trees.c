/*
 * [96] Unique Binary Search Trees
 *
 * https://leetcode.com/problems/unique-binary-search-trees/description/
 *
 * algorithms
 * Medium (41.55%)
 * Total Accepted:    138.2K
 * Total Submissions: 332.6K
 * Testcase Example:  '1'
 *
 * Given n, how many structurally unique BST's (binary search trees) that store
 * values 1...n?
 * 
 * 
 * For example,
 * Given n = 3, there are a total of 5 unique BST's.
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
int numTrees(int n) {
    if (n <= 1)
        return n;
    int* f = (int*)malloc(sizeof(int)*(n+1));
    f[0] = 1;
    for (int i = 1; i <= n; ++i) {
        f[i] = 0;
        int left  = 0;
        int right = i - 1;
        while (left < right) {
            f[i] += f[left] * f[right] * 2;
            ++left;
            --right;
        }
        if (left == right)
            f[i] += f[left] * f[right];
    }
    return f[n];
}
