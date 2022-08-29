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
    if (*s == '\0') {
        int p_len = strlen(p);
        if (p_len&1)
            return false;
        for (int i = 1; i < p_len; i += 2)
            if (p[i] != '*')
                return false;
        return true;
    }
    if (*p == '\0')
        return false;
    if (*s != *p && *p != '.')
        return p[1] == '*' && isMatch(s, p + 2);
    if (p[1] != '*')
        return isMatch(s + 1, p + 1);
    return isMatch(s + 1, p) || isMatch(s, p + 2);
}
