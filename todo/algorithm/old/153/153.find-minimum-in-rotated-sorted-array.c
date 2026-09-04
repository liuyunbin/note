/*
 * [153] Find Minimum in Rotated Sorted Array
 *
 * https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (40.46%)
 * Total Accepted:    176.1K
 * Total Submissions: 435K
 * Testcase Example:  '[1]'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 *
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *
 * Find the minimum element.
 *
 * You may assume no duplicate exists in the array.
 */
int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        if (nums[left] <= nums[right]) return nums[left];
        int mid = (left + right) / 2;
        if (nums[left] <= nums[mid])
            left = mid + 1;
        else
            right = mid;
    }
    return -1;
}
