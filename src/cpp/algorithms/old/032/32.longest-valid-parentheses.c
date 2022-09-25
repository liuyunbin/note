/*
 * [32] Longest Valid Parentheses
 *
 * https://leetcode.com/problems/longest-valid-parentheses/description/
 *
 * algorithms
 * Hard (23.15%)
 * Total Accepted:    113.2K
 * Total Submissions: 489.1K
 * Testcase Example:  '""'
 *
 * Given a string containing just the characters '(' and ')', find the length
 * of the longest valid (well-formed) parentheses substring.
 *
 *
 * For "(()", the longest valid parentheses substring is "()", which has length
 * = 2.
 *
 *
 * Another example is ")()())", where the longest valid parentheses substring
 * is "()()", which has length = 4.
 *
 */

int max(int x, int y) { return x > y ? x : y; }

int longestValidParentheses(char* s) {
    int s_len = strlen(s);
    if (s_len <= 1) return 0;
    int* f = (int*)calloc(s_len, sizeof(int));
    for (int i = 1; i < s_len; ++i)
        if (s[i] == ')' && i - f[i - 1] - 1 >= 0 &&
            s[i - f[i - 1] - 1] == '(') {
            f[i] = f[i - 1] + 2;
            if (i - f[i - 1] - 2 >= 0) f[i] += f[i - f[i - 1] - 2];
        }
    int result = 0;
    for (int i = 0; i < s_len; ++i) result = max(result, f[i]);
    return result;
}
