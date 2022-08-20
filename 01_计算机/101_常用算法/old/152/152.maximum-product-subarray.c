/*
 * [152] Maximum Product Subarray
 *
 * https://leetcode.com/problems/maximum-product-subarray/description/
 *
 * algorithms
 * Medium (26.35%)
 * Total Accepted:    123.8K
 * Total Submissions: 469.2K
 * Testcase Example:  '[-2]'
 *
 * 
 * Find the contiguous subarray within an array (containing at least one
 * number) which has the largest product.
 * 
 * 
 * 
 * For example, given the array [2,3,-2,4],
 * the contiguous subarray [2,3] has the largest product = 6.
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x > y ? y : x;
}

int maxProduct(int* nums, int numsSize) {
    int prev_max = nums[0];
    int prev_min = nums[0];
    int result   = nums[0];
    for (int i = 1; i < numsSize; ++i) {
        int temp = prev_max;
        prev_max = max(nums[i], max(nums[i]*prev_max, nums[i]*prev_min));
        prev_min = min(nums[i], min(nums[i]*temp,     nums[i]*prev_min));
        result = max(result, prev_max);
    }
    return result;
}
