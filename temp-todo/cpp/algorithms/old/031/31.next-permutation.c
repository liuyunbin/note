/*
 * [31] Next Permutation
 *
 * https://leetcode.com/problems/next-permutation/description/
 *
 * algorithms
 * Medium (28.91%)
 * Total Accepted:    134K
 * Total Submissions: 463.4K
 * Testcase Example:  '[1,2,3]'
 *
 *
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 *
 *
 * If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order).
 *
 *
 * The replacement must be in-place, do not allocate extra memory.
 *
 *
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 *
 */
void nextPermutation(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    for (int i = numsSize - 2; i >= 0; --i) {
        if (nums[i] >= nums[i + 1]) continue;
        int j;
        for (j = numsSize - 1; nums[j] <= nums[i]; --j)
            ;

        int temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
        left = i + 1;
        break;
    }
    while (left < right) {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
        ++left;
        --right;
    }
}
