/*
 * [74] Search a 2D Matrix
 *
 * https://leetcode.com/problems/search-a-2d-matrix/description/
 *
 * algorithms
 * Medium (34.82%)
 * Total Accepted:    144K
 * Total Submissions: 413.6K
 * Testcase Example:  '[[1,3,5,7],[10,11,16,20],[23,30,34,50]]\n3'
 *
 * Write an efficient algorithm that searches for a value in an m x n matrix.
 * This matrix has the following properties:
 *
 *
 *
 * Integers in each row are sorted from left to right.
 * The first integer of each row is greater than the last integer of the
 * previous row.
 *
 *
 *
 *
 * For example,
 *
 * Consider the following matrix:
 *
 *
 * [
 * ⁠ [1,   3,  5,  7],
 * ⁠ [10, 11, 16, 20],
 * ⁠ [23, 30, 34, 50]
 * ]
 *
 *
 * Given target = 3, return true.
 */
bool searchMatrix(int** matrix, int matrixRowSize, int matrixColSize,
                  int target) {
    int left = 0;
    int right = matrixRowSize * matrixColSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int x = mid / matrixColSize;
        int y = mid % matrixColSize;
        if (matrix[x][y] == target) return true;
        if (matrix[x][y] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}
