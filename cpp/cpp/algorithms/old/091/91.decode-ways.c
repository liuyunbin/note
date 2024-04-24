/*
 * [91] Decode Ways
 *
 * https://leetcode.com/problems/decode-ways/description/
 *
 * algorithms
 * Medium (20.10%)
 * Total Accepted:    152.1K
 * Total Submissions: 756.1K
 * Testcase Example:  '""'
 *
 *
 * A message containing letters from A-Z is being encoded to numbers using the
 * following mapping:
 *
 *
 *
 * 'A' -> 1
 * 'B' -> 2
 * ...
 * 'Z' -> 26
 *
 *
 *
 * Given an encoded message containing digits, determine the total number of
 * ways to decode it.
 *
 *
 *
 * For example,
 * Given encoded message "12",
 * it could be decoded as "AB" (1 2) or "L" (12).
 *
 *
 *
 * The number of ways decoding "12" is 2.
 *
 */
int numDecodings(char* s) {
    if (*s == '\0') return 0;
    int s_len = strlen(s);
    int* f = (int*)malloc(sizeof(int) * (s_len + 1));
    f[s_len] = 1;
    f[s_len - 1] = s[s_len - 1] == '0' ? 0 : 1;
    for (int i = s_len - 2; i >= 0; --i)
        if (s[i] == '0')
            f[i] = 0;
        else {
            f[i] = f[i + 1];
            if (s[i] == '1' || s[i] == '2' && s[i + 1] <= '6') f[i] += f[i + 2];
        }
    return f[0];
}
