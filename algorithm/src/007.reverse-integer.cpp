/*
 * [7] Reverse Integer
 *
 * https://leetcode.com/problems/reverse-integer/description/
 *
 * algorithms
 * Easy (24.47%)
 * Total Accepted:    504.2K
 * Total Submissions: 2.1M
 * Testcase Example:  '123'
 *
 * Given a 32-bit signed integer, reverse digits of an integer.
 *
 * Example 1:
 *
 *
 * Input: 123
 * Output: 321
 *
 *
 * Example 2:
 *
 *
 * Input: -123
 * Output: -321
 *
 *
 * Example 3:
 *
 *
 * Input: 120
 * Output: 21
 *
 *
 * Note:
 * Assume we are dealing with an environment which could only store integers
 * within the 32-bit signed integer range: [−231,  231 − 1]. For the purpose of
 * this problem, assume that your function returns 0 when the reversed integer
 * overflows.
 *
 */
class Solution {
   public:
    int reverse(int x) {
        long long ret = 0;
        while (x != 0) {
            ret = ret * 10 + x % 10;
            x /= 10;
        }
        if (ret < INT_MIN || ret > INT_MAX) return 0;
        return ret;
    }
};
