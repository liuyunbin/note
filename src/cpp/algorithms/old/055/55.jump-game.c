/*
 * [55] Jump Game
 *
 * https://leetcode.com/problems/jump-game/description/
 *
 * algorithms
 * Medium (29.57%)
 * Total Accepted:    146.4K
 * Total Submissions: 495K
 * Testcase Example:  '[2,3,1,1,4]'
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
 * Determine if you are able to reach the last index.
 *
 *
 *
 * For example:
 * A = [2,3,1,1,4], return true.
 *
 *
 * A = [3,2,1,0,4], return false.
 *
 */
int max(int x, int y) { return x > y ? x : y; }

bool canJump(int* nums, int numsSize) {
    int current_max = 0;
    for (int i = 0; i <= current_max; ++i) {
        current_max = max(current_max, i + nums[i]);
        if (current_max >= numsSize - 1) return true;
    }
    return false;
}
