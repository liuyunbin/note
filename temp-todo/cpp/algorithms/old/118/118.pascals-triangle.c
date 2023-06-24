/*
 * [118] Pascal's Triangle
 *
 * https://leetcode.com/problems/pascals-triangle/description/
 *
 * algorithms
 * Easy (39.43%)
 * Total Accepted:    154.4K
 * Total Submissions: 391.4K
 * Testcase Example:  '0'
 *
 * Given numRows, generate the first numRows of Pascal's triangle.
 *
 *
 * For example, given numRows = 5,
 * Return
 *
 * [
 * ⁠    [1],
 * ⁠   [1,1],
 * ⁠  [1,2,1],
 * ⁠ [1,3,3,1],
 * ⁠[1,4,6,4,1]
 * ]
 *
 *
 */
/**
 * Return an array of arrays.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int** generate(int numRows, int** columnSizes) {
    int** result = (int**)malloc(sizeof(int*) * numRows);
    for (int i = 0; i < numRows; ++i)
        result[i] = (int*)malloc(sizeof(int) * (i + 1));
    *columnSizes = (int*)malloc(sizeof(int) * numRows);
    for (int i = 0; i < numRows; ++i) (*columnSizes)[i] = i + 1;
    for (int i = 0; i < numRows; ++i) result[i][0] = result[i][i] = 1;
    for (int i = 1; i < numRows; ++i)
        for (int j = 1; j < i; ++j)
            result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
    return result;
}
