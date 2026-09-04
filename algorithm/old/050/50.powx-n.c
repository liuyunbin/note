/*
 * [50] Pow(x, n)
 *
 * https://leetcode.com/problems/powx-n/description/
 *
 * algorithms
 * Medium (25.98%)
 * Total Accepted:    187K
 * Total Submissions: 719.9K
 * Testcase Example:  '2.00000\n10'
 *
 * Implement pow(x, n).
 *
 *
 *
 *
 * Example 1:
 *
 * Input: 2.00000, 10
 * Output: 1024.00000
 *
 *
 *
 * Example 2:
 *
 * Input: 2.10000, 3
 * Output: 9.26100
 *
 *
 */
double myPow(double x, int n) {
    if (n == 0) return 1;
    long long m = n;
    if (n < 0) {
        x = 1 / x;
        m = -(long long)n;
    }
    double result = 1;
    while (m > 0) {
        if (m & 1) result *= x;
        x *= x;
        m /= 2;
    }
    return result;
}
