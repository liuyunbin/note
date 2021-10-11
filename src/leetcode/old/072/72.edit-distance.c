/*
 * [72] Edit Distance
 *
 * https://leetcode.com/problems/edit-distance/description/
 *
 * algorithms
 * Hard (32.23%)
 * Total Accepted:    104.6K
 * Total Submissions: 324.4K
 * Testcase Example:  '""\n""'
 *
 * 
 * Given two words word1 and word2, find the minimum number of steps required
 * to convert word1 to word2. (each operation is counted as 1 step.)
 * 
 * 
 * 
 * You have the following 3 operations permitted on a word:
 * 
 * 
 * 
 * a) Insert a character
 * b) Delete a character
 * c) Replace a character
 * 
 */

int min(int x, int y) {
    return x > y ? y : x;
}

int minDistance(char* word1, char* word2) {
    int word1_len = strlen(word1);
    int word2_len = strlen(word2);
    int** f = (int**)malloc(sizeof(int*)*(word1_len+1));
    for (int i = 0; i <= word1_len; ++i)
        f[i] = (int*)malloc(sizeof(int)*(word2_len+1));
    for (int i = 0; i <= word1_len; ++i)
        for (int j = 0; j <= word2_len; ++j)
            if (i == 0 && j == 0)
                f[i][j] = 0;
            else if (i == 0)
                f[i][j] = f[i][j-1] + 1;
            else if (j == 0)
                f[i][j] = f[i-1][j] + 1;
            else if (word1[i-1] == word2[j-1])
                f[i][j] = f[i-1][j-1];
            else
                f[i][j] = 1 + min(f[i-1][j], min(f[i][j-1], f[i-1][j-1]));

    return f[word1_len][word2_len];
}
