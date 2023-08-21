/*
 * [16] 3Sum Closest
 *
 * https://leetcode.com/problems/3sum-closest/description/
 *
 * algorithms
 * Medium (31.44%)
 * Total Accepted:    155.3K
 * Total Submissions: 494K
 * Testcase Example:  '[0,0,0]\n1'
 *
 * Given an array S of n integers, find three integers in S such that the sum
 * is closest to a given number, target. Return the sum of the three integers.
 * You may assume that each input would have exactly one solution.
 *
 *
 * ⁠   For example, given array S = {-1 2 1 -4}, and target = 1.
 *
 * ⁠   The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
 *
 */

int compare(const void* x, const void* y) {
    return *(const int*)x - *(const int*)y;
}

int threeSumClosest(int* nums, int numsSize, int target) {
    qsort(nums, numsSize, sizeof(int), compare);
    int current_closest = nums[0] + nums[1] + nums[2];
    for (int i = 0; i < numsSize; ++i) {
        int left = i + 1;
        int right = numsSize - 1;
        while (left < right) {
            int temp = nums[i] + nums[left] + nums[right];
            if (temp == target) return target;
            if (abs(temp - target) < abs(current_closest - target))
                current_closest = temp;
            if (temp < target)
                ++left;
            else
                --right;
        }
    }
    return current_closest;
}
