/*
 * [7] Reverse Integer
 *
 * https://leetcode.com/problems/reverse-integer/description/
 *
 * algorithms
 * Easy (24.40%)
 * Total Accepted:    335.8K
 * Total Submissions: 1.4M
 * Testcase Example:  '123'
 *
 * Given a 32-bit signed integer, reverse digits of an integer.
 * 
 * Example 1:
 * 
 * Input: 123
 * Output:  321
 * 
 * 
 * 
 * Example 2:
 * 
 * Input: -123
 * Output: -321
 * 
 * 
 * 
 * Example 3:
 * 
 * Input: 120
 * Output: 21
 * 
 * 
 * 
 * Note:
 * Assume we are dealing with an environment which could only hold integers
 * within the 32-bit signed integer range. For the purpose of this problem,
 * assume that your function returns 0 when the reversed integer overflows.
 * 
 */
int reverse(int x) {
    int result = 0;
    while (x != 0) {
        int new_result = result * 10 + x % 10;
        if (new_result / 10 != result)
            return 0;
        result = new_result;
        x /= 10;
    }
    return result;
}
