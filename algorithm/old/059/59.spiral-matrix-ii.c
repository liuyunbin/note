/*
 * [59] Spiral Matrix II
 *
 * https://leetcode.com/problems/spiral-matrix-ii/description/
 *
 * algorithms
 * Medium (40.42%)
 * Total Accepted:    92.9K
 * Total Submissions: 229.8K
 * Testcase Example:  '0'
 *
 * Given an integer n, generate a square matrix filled with elements from 1 to
 * n2 in spiral order.
 *
 *
 * For example,
 * Given n = 3,
 *
 * You should return the following matrix:
 *
 * [
 * ⁠[ 1, 2, 3 ],
 * ⁠[ 8, 9, 4 ],
 * ⁠[ 7, 6, 5 ]
 * ]
 *
 */
/**
 * Return an array of arrays.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int** generateMatrix(int n) {
    if (n <= 0) return NULL;
    int** result = (int**)malloc(sizeof(int*) * n);
    for (int i = 0; i < n; ++i) result[i] = (int*)malloc(sizeof(int) * n);
    int count = 0;
    for (int k = 0; k < n / 2; ++k) {
        int i = k, j = k;
        while (j + 1 < n - k) result[i][j++] = ++count;
        while (i + 1 < n - k) result[i++][j] = ++count;
        while (j > k) result[i][j--] = ++count;
        while (i > k) result[i--][j] = ++count;
    }
    if (n & 1) result[n / 2][n / 2] = ++count;
    return result;
}
