/*
 * [54] Spiral Matrix
 *
 * https://leetcode.com/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (26.71%)
 * Total Accepted:    123.9K
 * Total Submissions: 463.8K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given a matrix of m x n elements (m rows, n columns), return all elements of
 * the matrix in spiral order.
 *
 *
 *
 * For example,
 * Given the following matrix:
 *
 *
 * [
 * ⁠[ 1, 2, 3 ],
 * ⁠[ 4, 5, 6 ],
 * ⁠[ 7, 8, 9 ]
 * ]
 *
 *
 * You should return [1,2,3,6,9,8,7,4,5].
 *
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */

int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize <= 0 || matrixColSize <= 0) return NULL;
    int* result = (int*)malloc(sizeof(int) * matrixRowSize * matrixColSize);
    int result_index = 0;
    int row_min = 0;
    int row_max = matrixRowSize - 1;
    int col_min = 0;
    int col_max = matrixColSize - 1;
    while (row_min <= row_max && col_min <= col_max) {
        for (int j = col_min; j <= col_max; ++j)
            result[result_index++] = matrix[row_min][j];
        ++row_min;
        for (int i = row_min; i <= row_max; ++i)
            result[result_index++] = matrix[i][col_max];
        --col_max;
        if (row_min <= row_max)
            for (int j = col_max; j >= col_min; --j)
                result[result_index++] = matrix[row_max][j];
        --row_max;
        if (col_min <= col_max)
            for (int i = row_max; i >= row_min; --i)
                result[result_index++] = matrix[i][col_min];
        ++col_min;
    }
    return result;
}
