/*
 * [64] Minimum Path Sum
 *
 * https://leetcode.com/problems/minimum-path-sum/description/
 *
 * algorithms
 * Medium (39.56%)
 * Total Accepted:    132.7K
 * Total Submissions: 335.2K
 * Testcase Example:  '[[1,3,1],[1,5,1],[4,2,1]]'
 *
 * Given a m x n grid filled with non-negative numbers, find a path from top
 * left to bottom right which minimizes the sum of all numbers along its path.
 * 
 * Note: You can only move either down or right at any point in time.
 * 
 * Example 1:
 * 
 * [[1,3,1],
 * ⁠[1,5,1],
 * ⁠[4,2,1]]
 * 
 * Given the above grid map, return 7. Because the path 1→3→1→1→1 minimizes the
 * sum.
 * 
 */

int min(int x, int y) {
    return x > y ? y : x;
}

int minPathSum(int** grid, int gridRowSize, int gridColSize) {
    if (gridRowSize <= 0 || gridColSize <= 0)
        return 0;
    for (int i = 1; i < gridRowSize; ++i)
        grid[i][0] += grid[i-1][0];
    for (int j = 1; j < gridColSize; ++j)
        grid[0][j] += grid[0][j-1];
    for (int i = 1; i < gridRowSize; ++i)
        for (int j = 1; j < gridColSize; ++j)
            grid[i][j] += min(grid[i-1][j], grid[i][j-1]);
    return grid[gridRowSize-1][gridColSize-1];
}
