/*
 * [75] Sort Colors
 *
 * https://leetcode.com/problems/sort-colors/description/
 *
 * algorithms
 * Medium (38.55%)
 * Total Accepted:    196.9K
 * Total Submissions: 510.7K
 * Testcase Example:  '[0]'
 *
 * 
 * Given an array with n objects colored red, white or blue, sort them so that
 * objects of the same color are adjacent, with the colors in the order red,
 * white and blue.
 * 
 * 
 * 
 * Here, we will use the integers 0, 1, and 2 to represent the color red,
 * white, and blue respectively.
 * 
 * 
 * 
 * Note:
 * You are not suppose to use the library's sort function for this problem.
 * 
 * 
 * click to show follow up.
 * 
 * 
 * Follow up:
 * A rather straight forward solution is a two-pass algorithm using counting
 * sort.
 * First, iterate the array counting number of 0's, 1's, and 2's, then
 * overwrite array with total number of 0's, then 1's and followed by 2's.
 * Could you come up with an one-pass algorithm using only constant space?
 * 
 * 
 */
void sortColors(int* nums, int numsSize) {
    for (int i = 0, j = 0, k = 0; k < numsSize; ++k) {
        int temp = nums[k];
        nums[k]  = 2;
        if (temp < 2)
            nums[j++] = 1;
        if (temp < 1)
            nums[i++] = 0;
    }
}
