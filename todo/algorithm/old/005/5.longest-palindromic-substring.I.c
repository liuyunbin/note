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

void function(const char* s, int s_len, int left, int right, int* current_max,
              int* current_index) {
    while (left >= 0 && right < s_len && s[left] == s[right]) {
        --left;
        ++right;
    }
    if (right - left - 1 > *current_max) {
        *current_max = right - left - 1;
        *current_index = left + 1;
    }
}

char* longestPalindrome(char* s) {
    if (*s == '\0') return "";
    int current_index = 0;
    int current_max = 0;
    int s_len = strlen(s);
    for (int i = 0; i < s_len; ++i) {
        function(s, s_len, i, i, &current_max, &current_index);
        function(s, s_len, i, i + 1, &current_max, &current_index);
    }
    char* result = (char*)malloc(sizeof(char) * (current_max + 1));
    strncpy(result, s + current_index, current_max);
    result[current_max] = '\0';
    return result;
}
