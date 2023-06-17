/*
 * [29] Divide Two Integers
 *
 * https://leetcode.com/problems/divide-two-integers/description/
 *
 * algorithms
 * Medium (15.87%)
 * Total Accepted:    119.9K
 * Total Submissions: 755.6K
 * Testcase Example:  '0\n1'
 *
 *
 * Divide two integers without using multiplication, division and mod
 * operator.
 *
 *
 * If it is overflow, return MAX_INT.
 *
 */
int divide(int dividend, int divisor) {
    if (dividend == INT_MIN && divisor == -1) return INT_MAX;
    int sign = dividend < 0 ^ divisor < 0 ? -1 : 1;
    long long y = llabs(dividend);
    long long x = llabs(divisor);
    int result = 0;
    while (y >= x) {
        long long temp = x;
        int count = 1;
        while ((temp << 1) <= y) {
            temp <<= 1;
            count <<= 1;
        }
        y -= temp;
        result += count;
    }
    return sign == -1 ? -result : result;
}
