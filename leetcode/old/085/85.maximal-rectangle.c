/*
 * [85] Maximal Rectangle
 *
 * https://leetcode.com/problems/maximal-rectangle/description/
 *
 * algorithms
 * Hard (28.99%)
 * Total Accepted:    78.6K
 * Total Submissions: 270.7K
 * Testcase Example:  '[["1","0","1","0","0"],["1","0","1","1","1"],["1","1","1","1","1"],["1","0","0","1","0"]]'
 *
 * 
 * Given a 2D binary matrix filled with 0's and 1's, find the largest rectangle
 * containing only 1's and return its area.
 * 
 * 
 * For example, given the following matrix:
 * 
 * 1 0 1 0 0
 * 1 0 1 1 1
 * 1 1 1 1 1
 * 1 0 0 1 0
 * 
 * Return 6.
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int maximalRectangle(char** matrix, int matrixRowSize, int matrixColSize) {
    int result = 0;
    int* left  = (int*)malloc(sizeof(int)*matrixColSize);
    int* right = (int*)malloc(sizeof(int)*matrixColSize);
    int* count = (int*)malloc(sizeof(int)*matrixColSize);
    for (int i = 0; i < matrixRowSize; ++i) {
        for (int j = 0; j < matrixColSize; ++j) {
            count[j] = 0;
            for (int k = i; k >= 0; --k, ++count[j])
                if (matrix[k][j] == '0')
                    break;
        }
        left[0] = 1;
        for (int j = 1; j < matrixColSize; ++j) {
            left[j] = 1;
            for (int k = j - 1; k >= 0 && count[k] >= count[j]; k -= left[k])
                left[j] += left[k];
        }
        right[matrixColSize-1] = 1;
        for (int j = matrixColSize - 2; j >= 0; --j) {
            right[j] = 1;
            for (int k = j + 1; k < matrixColSize && count[k] >= count[j]; k += right[k])
                right[j] += right[k];
        }
        for (int j = 0; j < matrixColSize; ++j)
            result = max(result, (left[j]+right[j]-1)*count[j]);
    }
    free(left);
    free(right);
    free(count);
    return result;
}
