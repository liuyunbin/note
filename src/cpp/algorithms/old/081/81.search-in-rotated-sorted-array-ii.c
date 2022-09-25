/*
 * [81] Search in Rotated Sorted Array II
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array-ii/description/
 *
 * algorithms
 * Medium (32.73%)
 * Total Accepted:    109.3K
 * Total Submissions: 333.9K
 * Testcase Example:  '[]\n5'
 *
 *
 * Follow up for "Search in Rotated Sorted Array":
 * What if duplicates are allowed?
 *
 * Would this affect the run-time complexity? How and why?
 *
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 *
 * (i.e., 0 1 2 4 5 6 7 might become 4 5 6 7 0 1 2).
 *
 * Write a function to determine if a given target is in the array.
 *
 * The array may contain duplicates.
 */
bool search(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (nums[mid] == target) return true;
        if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
            ++left;
            --right;
            continue;
        }
        if (nums[left] <= nums[mid])
            if (nums[left] <= target && target < nums[mid])
                right = mid - 1;
            else
                left = mid + 1;
        else if (nums[mid] < target && target <= nums[right])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}
