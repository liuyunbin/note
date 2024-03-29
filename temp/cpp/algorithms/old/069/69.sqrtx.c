/*
 * [69] Sqrt(x)
 *
 * https://leetcode.com/problems/sqrtx/description/
 *
 * algorithms
 * Easy (28.40%)
 * Total Accepted:    197.2K
 * Total Submissions: 694.2K
 * Testcase Example:  '4'
 *
 * Implement int sqrt(int x).
 *
 * Compute and return the square root of x.
 *
 * x is guaranteed to be a non-negative integer.
 *
 *
 *
 * Example 1:
 *
 * Input: 4
 * Output: 2
 *
 *
 *
 * Example 2:
 *
 * Input: 8
 * Output: 2
 * Explanation: The square root of 8 is 2.82842..., and since we want to return
 * an integer, the decimal part will be truncated.
 *
 *
 */
int mySqrt(int x) {
    long long left = 0;
    long long right = x;
    while (true) {
        long long mid = (left + right) / 2;
        if (mid * mid <= x && (mid + 1) * (mid + 1) > x) return mid;
        if (mid * mid > x)
            right = mid - 1;
        else
            left = mid + 1;
    }
}
