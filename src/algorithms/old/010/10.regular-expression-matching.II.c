/*
 * [10] Regular Expression Matching
 *
 * https://leetcode.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (24.28%)
 * Total Accepted:    173.7K
 * Total Submissions: 715.3K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Implement regular expression matching with support for '.' and '*'.
 * 
 * 
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 * 
 * The matching should cover the entire input string (not partial).
 * 
 * The function prototype should be:
 * bool isMatch(const char *s, const char *p)
 * 
 * Some examples:
 * isMatch("aa","a") → false
 * isMatch("aa","aa") → true
 * isMatch("aaa","aa") → false
 * isMatch("aa", "a*") → true
 * isMatch("aa", ".*") → true
 * isMatch("ab", ".*") → true
 * isMatch("aab", "c*a*b") → true
 * 
 */
bool isMatch(char* s, char* p) {
    int s_len = strlen(s);
    int p_len = strlen(p);
    bool**  f = (bool**)malloc(sizeof(bool*)*(s_len+1));
    for (int i = 0; i <= s_len; ++i)
        f[i] = (bool*)malloc(sizeof(bool)*(p_len+1));
    for (int i = 0; i <= s_len; ++i)
        for (int j = 0; j <= p_len; ++j)
            if (i == 0 && j == 0)
                f[i][j] = true;
            else if (i == 0)
                f[i][j] = j > 1 && p[j-1] == '*' && f[i][j-2];
            else if (j == 0)
                f[i][j] = false;
            else if (p[j-1] != '*')
                f[i][j] = f[i-1][j-1] && (s[i-1] == p[j-1] || p[j-1] == '.');
            else /* j >= 2  */
                f[i][j] = f[i][j-2] || (s[i-1] == p[j-2] || p[j-2] == '.') && f[i-1][j];
    return f[s_len][p_len];
}

