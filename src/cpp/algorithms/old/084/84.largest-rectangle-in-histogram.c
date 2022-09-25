/*
 * [84] Largest Rectangle in Histogram
 *
 * https://leetcode.com/problems/largest-rectangle-in-histogram/description/
 *
 * algorithms
 * Hard (27.25%)
 * Total Accepted:    107K
 * Total Submissions: 392.4K
 * Testcase Example:  '[2,1,5,6,2,3]'
 *
 *
 * Given n non-negative integers representing the histogram's bar height where
 * the width of each bar is 1, find the area of largest rectangle in the
 * histogram.
 *
 *
 *
 *
 * Above is a histogram where width of each bar is 1, given height =
 * [2,1,5,6,2,3].
 *
 *
 *
 *
 * The largest rectangle is shown in the shaded area, which has area = 10
 * unit.
 *
 *
 *
 * For example,
 * Given heights = [2,1,5,6,2,3],
 * return 10.
 *
 */

int max(int x, int y) { return x > y ? x : y; }

int largestRectangleArea(int* heights, int heightsSize) {
    if (heightsSize <= 0) return 0;
    int* left = (int*)malloc(heightsSize * sizeof(int));
    for (int i = 0; i < heightsSize; ++i) {
        left[i] = 1;
        for (int j = i - 1; j >= 0 && heights[j] >= heights[i]; j -= left[j])
            left[i] += left[j];
    }
    int* right = (int*)malloc(heightsSize * sizeof(int));
    for (int i = heightsSize - 1; i >= 0; --i) {
        right[i] = 1;
        for (int j = i + 1; j < heightsSize && heights[j] >= heights[i];
             j += right[j])
            right[i] += right[j];
    }
    int result = 0;
    for (int i = 0; i < heightsSize; ++i)
        result = max(result, (left[i] + right[i] - 1) * heights[i]);
    return result;
}
