/*
 * [35] Search Insert Position
 *
 * https://leetcode.com/problems/search-insert-position/description/
 *
 * algorithms
 * Easy (39.92%)
 * Total Accepted:    220.7K
 * Total Submissions: 552.9K
 * Testcase Example:  '[1,3,5,6]\n5'
 *
 * Given a sorted array and a target value, return the index if the target is
 * found. If not, return the index where it would be if it were inserted in
 * order.
 *
 * You may assume no duplicates in the array.
 *
 * Example 1:
 *
 * Input: [1,3,5,6], 5
 * Output: 2
 *
 *
 *
 * Example 2:
 *
 * Input: [1,3,5,6], 2
 * Output: 1
 *
 *
 *
 * Example 3:
 *
 * Input: [1,3,5,6], 7
 * Output: 4
 *
 *
 *
 * Example 1:
 *
 * Input: [1,3,5,6], 0
 * Output: 0
 *
 *
 */
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] == target) return mid;
        if (nums[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return left;
}
