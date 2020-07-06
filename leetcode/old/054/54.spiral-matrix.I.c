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

int min(int x, int y) {
    return x > y ? y : x;
}

int* spiralOrder(int** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize <= 0 || matrixColSize <= 0)
        return NULL;
    int* result = (int*)malloc(sizeof(int)*matrixRowSize*matrixColSize);
    if (matrixRowSize == 1) {
        memcpy(result, matrix[0], sizeof(int)*matrixColSize);
        return result;
    }
    if (matrixColSize == 1) {
        for (int i = 0; i < matrixRowSize; ++i)
            result[i] = matrix[i][0];
        return result;
    }
    int result_index = 0;
    for (int k = 0; k < matrixRowSize / 2 && k < matrixColSize / 2; ++k) {
        int i = k, j = k;
        while (j + 1 < matrixColSize - k)
            result[result_index++] = matrix[i][j++];
        while (i + 1 < matrixRowSize - k)
            result[result_index++] = matrix[i++][j];
        while (j > k)
            result[result_index++] = matrix[i][j--];
        while (i > k)
            result[result_index++] = matrix[i--][j];
    }
    if (min(matrixRowSize, matrixColSize)%2 == 0)
        return result;
    if (matrixRowSize < matrixColSize) { 
        int i = matrixRowSize / 2;
        for (int j = i; j < matrixColSize - i; ++j)
            result[result_index++] = matrix[i][j];
        return result;
    }
    int j = matrixColSize / 2;
    for (int i = j; i < matrixRowSize - j; ++i)
        result[result_index++] = matrix[i][j];
    return result;
}
