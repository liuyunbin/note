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
    char* previous_s = NULL;
    char* previous_p = NULL;
    while (true) {
        if (*s == '\0') {
            while (*p == '*')
                ++p;
            return *p == '\0';
        }
        if (*s == *p || *p == '?') {
            ++s;
            ++p;
            continue;
        }
        if (*p == '*') {
            previous_p = ++p;
            previous_s = s;
            continue;
        }
        if (previous_p == NULL)
            return false;
        p = previous_p;
        s = ++previous_s;
    }
}
