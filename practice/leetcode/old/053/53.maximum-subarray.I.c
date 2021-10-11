/*
 * [53] Maximum Subarray
 *
 * https://leetcode.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (40.04%)
 * Total Accepted:    263.1K
 * Total Submissions: 657.2K
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * 
 * Find the contiguous subarray within an array (containing at least one
 * number) which has the largest sum.
 * 
 * 
 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 * 
 * 
 * click to show more practice.
 * 
 * More practice:
 * 
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int maxSubArray(int* nums, int numsSize) {
    if (numsSize <= 0)
        return 0;
    int result      = nums[0];
    int current_max = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        current_max = nums[i] + max(0, current_max);
        result = max(result, current_max);
    }
    return result;
}
