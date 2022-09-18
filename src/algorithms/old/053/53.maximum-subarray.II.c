/*
 * [53] Maximum Subarray
 *
 * https://leetcode.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (40.04%)
 * Total Accepted:    263.1K
 * Total Submissions: 657.2K
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * 
 * Find the contiguous subarray within an array (containing at least one
 * number) which has the largest sum.
 * 
 * 
 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 * 
 * 
 * click to show more practice.
 * 
 * More practice:
 * 
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

void backtrack(int* nums, int left, int right, int* left_max, int* right_max, int* current_max, int* sum) {
    if (left == right) {
        *left_max = *right_max = *current_max = *sum = nums[left];
        return ;
    }
    int mid = (left + right) / 2;
    int left_left_max, left_right_max, left_current_max, left_sum;
    backtrack(nums, left,  mid, &left_left_max, &left_right_max, &left_current_max, &left_sum);
    int right_left_max, right_right_max, right_current_max, right_sum;
    backtrack(nums, mid + 1,  right, &right_left_max, &right_right_max, &right_current_max, &right_sum);
    *current_max = max(max(left_current_max, right_current_max), left_right_max + right_left_max);
    *sum         = left_sum + right_sum;
    *left_max    = max(left_left_max,   left_sum  + right_left_max);
    *right_max   = max(right_right_max, right_sum + left_right_max);
}

int maxSubArray(int* nums, int numsSize) {
    if (numsSize <= 0)
        return 0;
    int left_max, right_max, current_max, sum;
    backtrack(nums, 0, numsSize - 1, &left_max, &right_max, &current_max, &sum);
    return current_max;
}
