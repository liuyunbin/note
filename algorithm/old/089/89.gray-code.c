/*
 * [89] Gray Code
 *
 * https://leetcode.com/problems/gray-code/description/
 *
 * algorithms
 * Medium (41.88%)
 * Total Accepted:    100.1K
 * Total Submissions: 239K
 * Testcase Example:  '0'
 *
 * The gray code is a binary numeral system where two successive values differ
 * in only one bit.
 *
 * Given a non-negative integer n representing the total number of bits in the
 * code, print the sequence of gray code. A gray code sequence must begin with
 * 0.
 *
 * For example, given n = 2, return [0,1,3,2]. Its gray code sequence is:
 *
 * 00 - 0
 * 01 - 1
 * 11 - 3
 * 10 - 2
 *
 *
 * Note:
 * For a given n, a gray code sequence is not uniquely defined.
 *
 * For example, [0,2,3,1] is also a valid gray code sequence according to the
 * above definition.
 *
 * For now, the judge is able to judge based on one instance of gray code
 * sequence. Sorry about that.
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize) {
    if (n < 0) {
        *returnSize = 0;
        return NULL;
    }
    if (n == 0) {
        *returnSize = 1;
        int* result = (int*)malloc(sizeof(int));
        result[0] = 0;
        return result;
    }
    *returnSize = 1;
    for (int i = 0; i < n; ++i) *returnSize *= 2;
    int count = *returnSize / 2;
    int* result = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; ++i) {
        result[i] = 0;
        for (int j = 0, k = count; j < n; ++j, k /= 2) switch (i / k % 4) {
                case 0:
                case 3:
                    result[i] = result[i] * 2;
                    break;
                default:
                    result[i] = result[i] * 2 + 1;
                    break;
            }
    }
    return result;
}
