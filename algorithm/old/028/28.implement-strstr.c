/*
 * [28] Implement strStr()
 *
 * https://leetcode.com/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (28.68%)
 * Total Accepted:    232.3K
 * Total Submissions: 809.7K
 * Testcase Example:  '"hello"\n"ll"'
 *
 *
 * Implement strStr().
 *
 *
 *
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 *
 *
 * Example 1:
 *
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 *
 *
 *
 * Example 2:
 *
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 *
 *
 */
int strStr(char* haystack, char* needle) {
    if (*haystack == '\0' && *needle == '\0') return 0;
    for (int i = 0; haystack[i] != '\0'; ++i)
        if (strncmp(haystack + i, needle, strlen(needle)) == 0) return i;
    return -1;
}
