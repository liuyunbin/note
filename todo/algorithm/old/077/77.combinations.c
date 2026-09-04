/*
 * [77] Combinations
 *
 * https://leetcode.com/problems/combinations/description/
 *
 * algorithms
 * Medium (40.56%)
 * Total Accepted:    132.3K
 * Total Submissions: 326.1K
 * Testcase Example:  '4\n2'
 *
 *
 * Given two integers n and k, return all possible combinations of k numbers
 * out of 1 ... n.
 *
 *
 * For example,
 * If n = 4 and k = 2, a solution is:
 *
 *
 *
 * [
 * ⁠ [2,4],
 * ⁠ [3,4],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ [1,3],
 * ⁠ [1,4],
 * ]
 *
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
#define MAX 10000
void function(int n, int k, int index, int* temp, int temp_index, int** result,
              int* returnSize) {
    if (temp_index == k) {
        result[*returnSize] = (int*)malloc(sizeof(int) * k);
        memcpy(result[(*returnSize)++], temp, sizeof(int) * k);
        return;
    }
    if (index == n) return;
    function(n, k, index + 1, temp, temp_index, result, returnSize);
    temp[temp_index] = index + 1;
    function(n, k, index + 1, temp, temp_index + 1, result, returnSize);
}

int** combine(int n, int k, int** columnSizes, int* returnSize) {
    if (n <= 0 || k <= 0) {
        *returnSize = 0;
        return NULL;
    }
    int** result = (int**)malloc(sizeof(int*) * MAX);
    int* temp = (int*)malloc(sizeof(int) * k);
    *returnSize = 0;
    function(n, k, 0, temp, 0, result, returnSize);
    free(temp);
    *columnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; ++i) (*columnSizes)[i] = k;
    return result;
}
