/*
 * [11] Container With Most Water
 *
 * https://leetcode.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (36.86%)
 * Total Accepted:    169.8K
 * Total Submissions: 460.7K
 * Testcase Example:  '[1,1]'
 *
 * Given n non-negative integers a1, a2, ..., an, where each represents a point
 * at coordinate (i, ai). n vertical lines are drawn such that the two
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
 * with x-axis forms a container, such that the container contains the most
 * water.
 * 
 * Note: You may not slant the container and n is at least 2.
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int maxArea(int* height, int heightSize) {
    int current_max = 0;
    int left        = 0;
    int right       = heightSize - 1;
    while (left < right)
        if (height[left] < height[right]) {
            current_max = max(current_max, height[left]*(right-left));
            ++left;
        } else {
            current_max = max(current_max, height[right]*(right-left));
            --right;
        }
    return current_max;
}
