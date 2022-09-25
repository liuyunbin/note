/*
 * [119] Pascal's Triangle II
 *
 * https://leetcode.com/problems/pascals-triangle-ii/description/
 *
 * algorithms
 * Easy (37.62%)
 * Total Accepted:    133.8K
 * Total Submissions: 355.7K
 * Testcase Example:  '0'
 *
 * Given an index k, return the kth row of the Pascal's triangle.
 *
 *
 * For example, given k = 3,
 * Return [1,3,3,1].
 *
 *
 *
 * Note:
 * Could you optimize your algorithm to use only O(k) extra space?
 *
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getRow(int rowIndex, int* returnSize) {
    *returnSize = rowIndex + 1;
    int* result = (int*)malloc(sizeof(int) * (rowIndex + 1));
    int* previous_result = (int*)malloc(sizeof(int) * (rowIndex + 1));
    for (int i = 0; i <= rowIndex; ++i) result[i] = previous_result[i] = 1;
    for (int i = 2; i <= rowIndex; ++i) {
        int* temp = result;
        result = previous_result;
        previous_result = temp;
        for (int j = 1; j < i; ++j)
            result[j] = previous_result[j] + previous_result[j - 1];
    }
    free(previous_result);
    return result;
}
