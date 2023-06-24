/*
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (25.18%)
 * Total Accepted:    266.3K
 * Total Submissions: 1.1M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, find the longest palindromic substring in s. You may
 * assume that the maximum length of s is 1000.
 *
 * Example:
 *
 * Input: "babad"
 *
 * Output: "bab"
 *
 * Note: "aba" is also a valid answer.
 *
 *
 *
 * Example:
 *
 * Input: "cbbd"
 *
 * Output: "bb"
 *
 *
 */

char* longestPalindrome(char* s) {
    if (*s == '\0') return "";
    bool f[1000][1000];
    int current_index = 0;
    int current_max = 0;
    int s_len = strlen(s);
    for (int k = 0; k < s_len; ++k)
        for (int i = 0; i + k < s_len; ++i)
            if (s[i] == s[i + k] && (k < 2 || f[i + 1][i + k - 1])) {
                f[i][i + k] = true;
                current_max = k + 1;
                current_index = i;
            } else
                f[i][i + k] = false;
    char* result = (char*)malloc(sizeof(char) * (current_max + 1));
    strncpy(result, s + current_index, current_max);
    result[current_max] = '\0';
    return result;
}
