/*
 * [120] Triangle
 *
 * https://leetcode.com/problems/triangle/description/
 *
 * algorithms
 * Medium (34.50%)
 * Total Accepted:    121.6K
 * Total Submissions: 352.5K
 * Testcase Example:  '[[-10]]'
 *
 * Given a triangle, find the minimum path sum from top to bottom. Each step
 * you may move to adjacent numbers on the row below.
 *
 *
 * For example, given the following triangle
 *
 * [
 * ⁠    [2],
 * ⁠   [3,4],
 * ⁠  [6,5,7],
 * ⁠ [4,1,8,3]
 * ]
 *
 *
 *
 * The minimum path sum from top to bottom is 11 (i.e., 2 + 3 + 5 + 1 = 11).
 *
 *
 *
 * Note:
 * Bonus point if you are able to do this using only O(n) extra space, where n
 * is the total number of rows in the triangle.
 *
 */
int min(int x, int y) { return x > y ? y : x; }

int minimumTotal(int** triangle, int triangleRowSize, int* triangleColSizes) {
    for (int i = 1; i < triangleRowSize; ++i)
        for (int j = 0; j <= i; ++j)
            if (j == 0)
                triangle[i][j] += triangle[i - 1][j];
            else if (j == i)
                triangle[i][j] += triangle[i - 1][j - 1];
            else
                triangle[i][j] +=
                    min(triangle[i - 1][j], triangle[i - 1][j - 1]);
    int result = triangle[triangleRowSize - 1][0];
    for (int i = 1; i < triangleRowSize; ++i)
        result = min(result, triangle[triangleRowSize - 1][i]);
    return result;
}
