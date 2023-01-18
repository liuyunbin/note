/*
 * [80] Remove Duplicates from Sorted Array II
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array-ii/description/
 *
 * algorithms
 * Medium (36.54%)
 * Total Accepted:    136.8K
 * Total Submissions: 374.2K
 * Testcase Example:  '[]'
 *
 *
 * Follow up for "Remove Duplicates":
 * What if duplicates are allowed at most twice?
 *
 *
 * For example,
 * Given sorted array nums = [1,1,1,2,2,3],
 *
 *
 * Your function should return length = 5, with the first five elements of nums
 * being 1, 1, 2, 2 and 3. It doesn't matter what you leave beyond the new
 * length.
 *
 */
int removeDuplicates(int* nums, int numsSize) {
    int k = 0;
    for (int i = 0; i < numsSize;) {
        int count = 1;
        int j;
        for (j = i + 1; j < numsSize && nums[j] == nums[i]; ++j) ++count;
        for (int index = 0; index < count && index < 2; ++index)
            nums[k++] = nums[i];
        i = j;
    }
    return k;
}
