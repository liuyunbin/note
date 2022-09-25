/*
 * [63] Unique Paths II
 *
 * https://leetcode.com/problems/unique-paths-ii/description/
 *
 * algorithms
 * Medium (32.01%)
 * Total Accepted:    122.1K
 * Total Submissions: 381.4K
 * Testcase Example:  '[[0]]'
 *
 * Follow up for "Unique Paths":
 *
 * Now consider if some obstacles are added to the grids. How many unique paths
 * would there be?
 *
 * An obstacle and empty space is marked as 1 and 0 respectively in the grid.
 *
 * For example,
 * There is one obstacle in the middle of a 3x3 grid as illustrated below.
 *
 * [
 * ⁠ [0,0,0],
 * ⁠ [0,1,0],
 * ⁠ [0,0,0]
 * ]
 *
 * The total number of unique paths is 2.
 *
 * Note: m and n will be at most 100.
 */
int uniquePathsWithObstacles(int** obstacleGrid, int obstacleGridRowSize,
                             int obstacleGridColSize) {
    if (obstacleGridRowSize <= 0 || obstacleGridColSize <= 0) return 0;
    obstacleGrid[0][0] = obstacleGrid[0][0] == 0;
    for (int i = 1; i < obstacleGridRowSize; ++i)
        obstacleGrid[i][0] =
            obstacleGrid[i - 1][0] == 1 && obstacleGrid[i][0] != 1;
    for (int j = 1; j < obstacleGridColSize; ++j)
        obstacleGrid[0][j] =
            obstacleGrid[0][j - 1] == 1 && obstacleGrid[0][j] != 1;
    for (int i = 1; i < obstacleGridRowSize; ++i)
        for (int j = 1; j < obstacleGridColSize; ++j)
            if (obstacleGrid[i][j] == 1)
                obstacleGrid[i][j] = 0;
            else
                obstacleGrid[i][j] =
                    obstacleGrid[i - 1][j] + obstacleGrid[i][j - 1];
    return obstacleGrid[obstacleGridRowSize - 1][obstacleGridColSize - 1];
}
