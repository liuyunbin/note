/*
 * [115] Distinct Subsequences
 *
 * https://leetcode.com/problems/distinct-subsequences/description/
 *
 * algorithms
 * Hard (31.92%)
 * Total Accepted:    78.1K
 * Total Submissions: 244.5K
 * Testcase Example:  '""\n"a"'
 *
 *
 * Given a string S and a string T, count the number of distinct subsequences
 * of S which equals T.
 *
 *
 *
 * A subsequence of a string is a new string which is formed from the original
 * string by deleting some (can be none) of the characters without disturbing
 * the relative positions of the remaining characters. (ie, "ACE" is a
 * subsequence of "ABCDE" while "AEC" is not).
 *
 *
 *
 * Here is an example:
 * S = "rabbbit", T = "rabbit"
 *
 *
 * Return 3.
 *
 */
int numDistinct(char* s, char* t) {
    int s_len = strlen(s);
    int t_len = strlen(t);
    int** f = (int**)malloc(sizeof(int*) * (s_len + 1));
    for (int i = 0; i <= s_len; ++i)
        f[i] = (int*)malloc(sizeof(int) * (t_len + 1));
    for (int i = 0; i <= s_len; ++i)
        for (int j = 0; j <= t_len; ++j)
            if (j == 0)
                f[i][j] = 1;
            else if (i == 0)
                f[i][j] = 0;
            else if (s[i - 1] == t[j - 1])
                f[i][j] = f[i - 1][j - 1] + f[i - 1][j];
            else
                f[i][j] = f[i - 1][j];
    return f[s_len][t_len];
}
