/*
 * [42] Trapping Rain Water
 *
 * https://leetcode.com/problems/trapping-rain-water/description/
 *
 * algorithms
 * Hard (37.29%)
 * Total Accepted:    142.3K
 * Total Submissions: 381.7K
 * Testcase Example:  '[]'
 *
 *
 * Given n non-negative integers representing an elevation map where the width
 * of each bar is 1, compute how much water it is able to trap after
 * raining.
 *
 *
 *
 * For example,
 * Given [0,1,0,2,1,0,1,3,2,1,2,1], return 6.
 *
 *
 *
 *
 * The above elevation map is represented by array [0,1,0,2,1,0,1,3,2,1,2,1].
 * In this case, 6 units of rain water (blue section) are being trapped. Thanks
 * Marcos for contributing this image!
 */
int trap(int* height, int heightSize) {
    int left = 0;
    int right = heightSize - 1;
    int left_max = 0;
    int right_max = 0;
    int result = 0;
    while (left < right)
        if (height[left] < height[right]) {
            if (height[left] >= left_max)
                left_max = height[left];
            else
                result += left_max - height[left];
            ++left;
        } else {
            if (height[right] >= right_max)
                right_max = height[right];
            else
                result += right_max - height[right];
            --right;
        }
    return result;
}
