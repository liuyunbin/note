/*
 * [45] Jump Game II
 *
 * https://leetcode.com/problems/jump-game-ii/description/
 *
 * algorithms
 * Hard (26.19%)
 * Total Accepted:    106.1K
 * Total Submissions: 405.1K
 * Testcase Example:  '[0]'
 *
 * 
 * Given an array of non-negative integers, you are initially positioned at the
 * first index of the array.
 * 
 * 
 * Each element in the array represents your maximum jump length at that
 * position. 
 * 
 * 
 * Your goal is to reach the last index in the minimum number of jumps.
 * 
 * 
 * 
 * For example:
 * Given array A = [2,3,1,1,4]
 * 
 * 
 * The minimum number of jumps to reach the last index is 2. (Jump 1 step from
 * index 0 to 1, then 3 steps to the last index.)
 * 
 * 
 * 
 * Note:
 * You can assume that you can always reach the last index.
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int jump(int* nums, int numsSize) {
    if (numsSize <= 1)
        return 0;
    int count_jump        = 0;
    int previous_jump_max = 0;
    int current_jump_max  = 0;
    for (int i = 0; i + 1 < numsSize; ++i) {
        current_jump_max = max(current_jump_max, i + nums[i]);
        if (i == previous_jump_max) {
            ++count_jump;
            previous_jump_max = current_jump_max;
        }
    }
    return count_jump;
}
