/*
 * [90] Subsets II
 *
 * https://leetcode.com/problems/subsets-ii/description/
 *
 * algorithms
 * Medium (37.44%)
 * Total Accepted:    132.6K
 * Total Submissions: 353.9K
 * Testcase Example:  '[1,2,2]'
 *
 *
 * Given a collection of integers that might contain duplicates, nums, return
 * all possible subsets (the power set).
 *
 * Note: The solution set must not contain duplicate subsets.
 *
 *
 * For example,
 * If nums = [1,2,2], a solution is:
 *
 *
 *
 * [
 * ⁠ [2],
 * ⁠ [1],
 * ⁠ [1,2,2],
 * ⁠ [2,2],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 *
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume
 * caller calls free().
 */
int compare(const void* x, const void* y) {
    return *(const int*)x - *(const int*)y;
}

void function(int* nums, int numsSize, int index, bool* used, int** result,
              int* columnSizes, int* returnSize) {
    if (index == numsSize) {
        columnSizes[*returnSize] = 0;
        for (int i = 0; i < numsSize; ++i)
            if (used[i] == true) ++columnSizes[*returnSize];
        if (columnSizes[*returnSize] == 0) {
            result[(*returnSize)++] = (int*)malloc(sizeof(int));
            return;
        }
        result[*returnSize] =
            (int*)malloc(sizeof(int) * columnSizes[*returnSize]);
        for (int i = 0, k = 0; i < numsSize; ++i)
            if (used[i] == true) result[*returnSize][k++] = nums[i];
        ++*returnSize;
        return;
    }
    used[index] = false;
    function(nums, numsSize, index + 1, used, result, columnSizes, returnSize);
    if (index == 0 || nums[index] != nums[index - 1] ||
        used[index - 1] == true) {
        used[index] = true;
        function(nums, numsSize, index + 1, used, result, columnSizes,
                 returnSize);
    }
}

int** subsetsWithDup(int* nums, int numsSize, int** columnSizes,
                     int* returnSize) {
    if (numsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 1;
    for (int i = 0; i < numsSize; ++i) *returnSize *= 2;
    qsort(nums, numsSize, sizeof(int), compare);
    int** result = (int**)malloc(sizeof(int*) * (*returnSize));
    *columnSizes = (int*)malloc(sizeof(int) * (*returnSize));
    bool* used = (bool*)malloc(sizeof(bool) * numsSize);
    *returnSize = 0;
    function(nums, numsSize, 0, used, result, *columnSizes, returnSize);
    free(used);
    return result;
}
