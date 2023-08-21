/*
 * [60] Permutation Sequence
 *
 * https://leetcode.com/problems/permutation-sequence/description/
 *
 * algorithms
 * Medium (29.10%)
 * Total Accepted:    94.8K
 * Total Submissions: 325.7K
 * Testcase Example:  '1\n1'
 *
 * The set [1,2,3,…,n] contains a total of n! unique permutations.
 *
 * By listing and labeling all of the permutations in order,
 * We get the following sequence (ie, for n = 3):
 *
 * "123"
 * "132"
 * "213"
 * "231"
 * "312"
 * "321"
 *
 *
 *
 * Given n and k, return the kth permutation sequence.
 *
 * Note: Given n will be between 1 and 9 inclusive.
 */
char* getPermutation(int n, int k) {
    int f[10] = {1};
    for (int i = 1; i <= n; ++i) f[i] = i * f[i - 1];
    bool used[10];
    for (int i = 1; i <= n; ++i) used[i] = false;
    char* result = (char*)malloc(sizeof(char) * (n + 1));
    int result_index = 0;
    for (int i = n - 1; i >= 0; --i) {
        int count = (k - 1) / f[i] + 1;
        k %= f[i];
        if (k == 0) k = f[i];
        for (int j = 1; j <= n; ++j)
            if (used[j] == false) {
                --count;
                if (count == 0) {
                    used[j] = true;
                    result[result_index++] = j + '0';
                    break;
                }
            }
    }
    result[n] = '\0';
    return result;
}
