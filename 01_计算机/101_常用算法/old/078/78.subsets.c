/*
 * [78] Subsets
 *
 * https://leetcode.com/problems/subsets/description/
 *
 * algorithms
 * Medium (43.00%)
 * Total Accepted:    204.5K
 * Total Submissions: 475.3K
 * Testcase Example:  '[1,2,3]'
 *
 * 
 * Given a set of distinct integers, nums, return all possible subsets (the
 * power set).
 * 
 * Note: The solution set must not contain duplicate subsets.
 * 
 * 
 * For example,
 * If nums = [1,2,3], a solution is:
 * 
 * 
 * 
 * [
 * ⁠ [3],
 * ⁠ [1],
 * ⁠ [2],
 * ⁠ [1,2,3],
 * ⁠ [1,3],
 * ⁠ [2,3],
 * ⁠ [1,2],
 * ⁠ []
 * ]
 * 
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */

void function(int* nums, int numsSize, int index, bool* f, int** result, int* columnSizes, int* returnSize) {
    if (index == numsSize) {
        columnSizes[*returnSize] = 0;
        for (int i = 0; i < numsSize; ++i)
            if (f[i] == true)
                ++columnSizes[*returnSize];
        if (columnSizes[*returnSize] == 0) {
            result[(*returnSize)++] = (int*)malloc(sizeof(int));
            return ;
        }
        result[*returnSize] = (int*)malloc(sizeof(int)*(columnSizes[*returnSize]));
        for (int i = 0, k = 0; i < numsSize; ++i)
            if (f[i] == true)
                result[*returnSize][k++] = nums[i];
        ++*returnSize;
        return ;
    }
    f[index] = false;
    function(nums, numsSize, index + 1, f, result, columnSizes, returnSize);
    f[index] = true;
    function(nums, numsSize, index + 1, f, result, columnSizes, returnSize);
}

int** subsets(int* nums, int numsSize, int** columnSizes, int* returnSize) {
    if (numsSize <= 0) {
        *returnSize = 0;
        return NULL;
    }
    *returnSize = 1;
    for (int i = 0; i < numsSize; ++i)
        *returnSize *= 2;
    int** result = (int**)malloc(sizeof(int*)*(*returnSize));
    *columnSizes =  (int*)malloc(sizeof(int*)*(*returnSize));
    bool* f = (bool*)malloc(sizeof(bool)*numsSize);
    *returnSize = 0;
    function(nums, numsSize, 0, f, result, *columnSizes, returnSize);
    free(f);
    return result;
}
