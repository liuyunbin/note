/*
 * [34] Search for a Range
 *
 * https://leetcode.com/problems/search-for-a-range/description/
 *
 * algorithms
 * Medium (31.51%)
 * Total Accepted:    166.9K
 * Total Submissions: 529.8K
 * Testcase Example:  '[5,7,7,8,8,10]\n8'
 *
 * Given an array of integers sorted in ascending order, find the starting and
 * ending position of a given target value.
 * 
 * Your algorithm's runtime complexity must be in the order of O(log n).
 * 
 * If the target is not found in the array, return [-1, -1].
 * 
 * 
 * For example,
 * Given [5, 7, 7, 8, 8, 10] and target value 8,
 * return [3, 4].
 * 
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    int* result = (int*)malloc(sizeof(int)*2);
    result[0] = result[1] = -1;
    *returnSize = 2;
    if (numsSize <= 0)
        return result;
    int left  = 0;
    int right = numsSize - 1;
    while (left < right) {
        int mid = (left + right) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] < target)
            left  = mid + 1;
        else
            right = mid;
    }
    if (nums[left] != target)
        return result;
    result[0] = left;
    right = numsSize - 1;
    while (left < right) {
        int mid = (left + right + 1) / 2;
        if (nums[mid] > target)
            right = mid - 1;
        else 
            left  = mid;
    }
    result[1] = left;
    return result;
}
