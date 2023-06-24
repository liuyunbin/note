/*
 * [14] Longest Common Prefix
 *
 * https://leetcode.com/problems/longest-common-prefix/description/
 *
 * algorithms
 * Easy (31.56%)
 * Total Accepted:    230.1K
 * Total Submissions: 729K
 * Testcase Example:  '[]'
 *
 * Write a function to find the longest common prefix string amongst an array
 * of strings.
 *
 */

int min(int x, int y) { return x > y ? y : x; }

char* longestCommonPrefix(char** strs, int strsSize) {
    if (strsSize <= 0) return "";
    if (strsSize == 1) return strs[0];
    int result_max_len = strlen(strs[0]);
    for (int i = 1; i < strsSize; ++i)
        result_max_len = min(result_max_len, strlen(strs[i]));
    int k;
    for (k = 0; k < result_max_len; ++k) {
        int i;
        for (i = 1; i < strsSize; ++i)
            if (strs[0][k] != strs[i][k]) break;
        if (i < strsSize) break;
    }
    if (k == 0) return "";
    char* result = (char*)malloc(sizeof(char) * (k + 1));
    strncpy(result, strs[0], k);
    result[k] = '\0';
    return result;
}
