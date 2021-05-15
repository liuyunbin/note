/*
 * [97] Interleaving String
 *
 * https://leetcode.com/problems/interleaving-string/description/
 *
 * algorithms
 * Hard (24.96%)
 * Total Accepted:    78.2K
 * Total Submissions: 313.2K
 * Testcase Example:  '""\n""\n""'
 *
 * 
 * Given s1, s2, s3, find whether s3 is formed by the interleaving of s1 and
 * s2.
 * 
 * 
 * 
 * For example,
 * Given:
 * s1 = "aabcc",
 * s2 = "dbbca",
 * 
 * 
 * When s3 = "aadbbcbcac", return true.
 * When s3 = "aadbbbaccc", return false.
 * 
 */
bool isInterleave(char* s1, char* s2, char* s3) {
    int s1_len = strlen(s1);
    int s2_len = strlen(s2);
    if (s1_len + s2_len != strlen(s3))
        return false;
    bool** f = (bool**)malloc(sizeof(bool*)*(s1_len+1));
    for (int i = 0; i <= s1_len; ++i)
        f[i] = (bool*)malloc(sizeof(bool)*(s2_len+1));
    for (int i = 0; i <= s1_len; ++i)
        for (int j = 0; j <= s2_len; ++j)
            if (i == 0 && j == 0)
                f[i][j] = true;
            else if (i == 0)
                f[i][j] = f[i][j-1] && s2[j-1] == s3[j-1];
            else if (j == 0)
                f[i][j] = f[i-1][j] && s1[i-1] == s3[i-1];
            else
                f[i][j] = s1[i-1] == s3[i+j-1] && f[i-1][j] || s2[j-1] == s3[i+j-1] && f[i][j-1];
    return f[s1_len][s2_len];
}
