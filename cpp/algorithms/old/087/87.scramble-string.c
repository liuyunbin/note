/*
 * [87] Scramble String
 *
 * https://leetcode.com/problems/scramble-string/description/
 *
 * algorithms
 * Hard (29.50%)
 * Total Accepted:    70K
 * Total Submissions: 237.4K
 * Testcase Example:  '"a"\n"a"'
 *
 *
 * Given a string s1, we may represent it as a binary tree by partitioning it
 * to two non-empty substrings recursively.
 *
 *
 * Below is one possible representation of s1 = "great":
 *
 *
 * ⁠   great
 * ⁠  /    \
 * ⁠ gr    eat
 * ⁠/ \    /  \
 * g   r  e   at
 * ⁠          / \
 * ⁠         a   t
 *
 *
 * To scramble the string, we may choose any non-leaf node and swap its two
 * children.
 *
 *
 * For example, if we choose the node "gr" and swap its two children, it
 * produces a scrambled string "rgeat".
 *
 *
 * ⁠   rgeat
 * ⁠  /    \
 * ⁠ rg    eat
 * ⁠/ \    /  \
 * r   g  e   at
 * ⁠          / \
 * ⁠         a   t
 *
 *
 * We say that "rgeat" is a scrambled string of "great".
 *
 *
 * Similarly, if we continue to swap the children of nodes "eat" and "at", it
 * produces a scrambled string "rgtae".
 *
 *
 * ⁠   rgtae
 * ⁠  /    \
 * ⁠ rg    tae
 * ⁠/ \    /  \
 * r   g  ta  e
 * ⁠      / \
 * ⁠     t   a
 *
 *
 * We say that "rgtae" is a scrambled string of "great".
 *
 *
 * Given two strings s1 and s2 of the same length, determine if s2 is a
 * scrambled string of s1.
 *
 */

bool function(const char* s1, const char* s2, int len) {
    if (strncmp(s1, s2, len) == 0) return true;
    int count[256];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < len; ++i) {
        ++count[s1[i]];
        --count[s2[i]];
    }
    for (int i = 0; i < 256; ++i)
        if (count[i] != 0) return false;
    for (int i = 1; i < len; ++i) {
        if (function(s1, s2, i) && function(s1 + i, s2 + i, len - i))
            return true;
        if (function(s1, s2 + len - i, i) && function(s1 + i, s2, len - i))
            return true;
    }
    return false;
}

bool isScramble(char* s1, char* s2) { return function(s1, s2, strlen(s1)); }
