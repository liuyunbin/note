/*
 * [73] Set Matrix Zeroes
 *
 * https://leetcode.com/problems/set-matrix-zeroes/description/
 *
 * algorithms
 * Medium (36.29%)
 * Total Accepted:    123.5K
 * Total Submissions: 340.4K
 * Testcase Example:  '[[0]]'
 *
 * 
 * Given a m x n matrix, if an element is 0, set its entire row and column to
 * 0. Do it in place.
 * 
 * 
 * click to show follow up.
 * 
 * Follow up:
 * 
 * 
 * Did you use extra space?
 * A straight forward solution using O(mn) space is probably a bad idea.
 * A simple improvement uses O(m + n) space, but still not the best solution.
 * Could you devise a constant space solution?
 * 
 * 
 */
void setZeroes(int** matrix, int matrixRowSize, int matrixColSize) {
    if (matrixRowSize <= 0 || matrixColSize <= 0)
        return ;
    bool row_0_is_0 = false;
    bool col_0_is_0 = false;
    for (int i = 0; i < matrixRowSize; ++i)
        if (matrix[i][0] == 0) {
            col_0_is_0 = true;
            break;
        }
    for (int j = 0; j < matrixColSize; ++j)
        if (matrix[0][j] == 0) {
            row_0_is_0 = true;
            break;
        }
    for (int i = 1; i < matrixRowSize; ++i)
        for (int j = 1; j < matrixColSize; ++j)
            if (matrix[i][j] == 0)
                matrix[i][0] = matrix[0][j] = 0;
    for (int i = 1; i < matrixRowSize; ++i)
        if (matrix[i][0] == 0)
            for (int j = 1; j < matrixColSize; ++j)
                matrix[i][j] = 0;
    for (int j = 1; j < matrixColSize; ++j)
        if (matrix[0][j] == 0)
            for (int i = 1; i < matrixRowSize; ++i)
                matrix[i][j] = 0;
    if (row_0_is_0)
        for (int j = 0; j < matrixColSize; ++j)
            matrix[0][j] = 0;
    if (col_0_is_0)
        for (int i = 0; i < matrixRowSize; ++i)
            matrix[i][0] = 0;
}
