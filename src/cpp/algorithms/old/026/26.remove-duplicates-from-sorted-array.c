/*
 * [26] Remove Duplicates from Sorted Array
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
 *
 * algorithms
 * Easy (35.69%)
 * Total Accepted:    294K
 * Total Submissions: 823.6K
 * Testcase Example:  '[1,1,2]'
 *
 * 
 * Given a sorted array, remove the duplicates in-place such that each element
 * appear only once and return the new length.
 * 
 * Do not allocate extra space for another array, you must do this by modifying
 * the input array in-place with O(1) extra memory.
 * 
 * 
 * Example:
 * 
 * Given nums = [1,1,2],
 * 
 * Your function should return length = 2, with the first two elements of nums
 * being 1 and 2 respectively.
 * It doesn't matter what you leave beyond the new length.
 * 
 * 
 */
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize <= 1)
        return numsSize;
    int k = 0;
    for (int i = 1; i < numsSize; ++i)
        if (nums[k] != nums[i])
            nums[++k] = nums[i];
    return k + 1;
}
