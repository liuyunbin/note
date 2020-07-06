/*
 * [44] Wildcard Matching
 *
 * https://leetcode.com/problems/wildcard-matching/description/
 *
 * algorithms
 * Hard (20.68%)
 * Total Accepted:    111.5K
 * Total Submissions: 539K
 * Testcase Example:  '"aa"\n"a"'
 *
 * Implement wildcard pattern matching with support for '?' and '*'.
 * 
 * 
 * '?' Matches any single character.
 * '*' Matches any sequence of characters (including the empty sequence).
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
 * isMatch("aa", "*") → true
 * isMatch("aa", "a*") → true
 * isMatch("ab", "?*") → true
 * isMatch("aab", "c*a*b") → false
 * 
 */
bool isMatch(char* s, char* p) {
    int s_len = strlen(s);
    int p_len = strlen(p);
    bool** f = (bool**)malloc(sizeof(bool*)*(s_len+1));
    for (int i = 0; i <= s_len; ++i)
        f[i] = (bool*)malloc(sizeof(bool)*(p_len+1));
    for (int i = 0; i <= s_len; ++i)
        for (int j = 0; j <= p_len; ++j)
            if (i == 0 && j == 0)
                f[i][j] = true;
            else if (i == 0)
                f[i][j] = p[j-1] == '*' && f[i][j-1];
            else if (j == 0)
                f[i][j] = false;
            else if (p[j-1] != '*')
                f[i][j] = (s[i-1] == p[j-1] || p[j-1] == '?') && f[i-1][j-1];
            else
                f[i][j] = f[i][j-1] || f[i-1][j];
    return f[s_len][p_len];
}
