/*
 * [137] Single Number II
 *
 * https://leetcode.com/problems/single-number-ii/description/
 *
 * algorithms
 * Medium (42.16%)
 * Total Accepted:    127.6K
 * Total Submissions: 302.5K
 * Testcase Example:  '[1]'
 *
 * 
 * Given an array of integers, every element appears three times except for
 * one, which appears exactly once. Find that single one.
 * 
 * 
 * 
 * Note:
 * Your algorithm should have a linear runtime complexity. Could you implement
 * it without using extra memory?
 * 
 */
int singleNumber(int* nums, int numsSize) {
    int f[32];
    memset(f, 0, sizeof(f));
    for (int i = 0; i < numsSize; ++i)
        for (int j = 0; j < 32; ++j) {
            if (nums[i]&1)
                ++f[j];
            nums[i] >>= 1;
        }
    int result = 0;
    for (int i = 31; i >= 0; --i)
        result = result * 2 + f[i]%3;
    return result;
}
