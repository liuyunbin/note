/*
 * [132] Palindrome Partitioning II
 *
 * https://leetcode.com/problems/palindrome-partitioning-ii/description/
 *
 * algorithms
 * Hard (24.60%)
 * Total Accepted:    77K
 * Total Submissions: 313.1K
 * Testcase Example:  '"aab"'
 *
 * 
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 * 
 * 
 * Return the minimum cuts needed for a palindrome partitioning of s.
 * 
 * 
 * For example, given s = "aab",
 * Return 1 since the palindrome partitioning ["aa","b"] could be produced
 * using 1 cut.
 * 
 */

int min(int x, int y) {
    return x > y ? y : x;
}

int minCut(char* s) {
    int s_len = strlen(s);
    if (s_len <= 1)
        return 0;
    bool** f = (bool**)malloc(sizeof(bool*)*s_len);
    for (int i = 0; i < s_len; ++i)
        f[i] = (bool*)malloc(sizeof(bool)*s_len);
    for (int k = 0; k < s_len; ++k)
        for (int i = 0; i + k < s_len; ++i)
            f[i][i+k] = s[i] == s[i+k] && (k<=2 || f[i+1][i+k-1] == true); 
    int* cut = (int*)malloc(sizeof(int)*(s_len+1));
    cut[0] = -1;
    for (int i = 0; i < s_len; ++i) {
        cut[i+1] = i;
        for (int j = 0; j <= i; ++j)
            if (f[j][i])
                cut[i+1] = min(cut[i+1], cut[j] + 1);
    }
    return cut[s_len];
}
