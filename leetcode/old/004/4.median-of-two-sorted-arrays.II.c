/*
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (22.47%)
 * Total Accepted:    218.1K
 * Total Submissions: 970.9K
 * Testcase Example:  '[1,3]\n[2]'
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 * 
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 * 
 * Example 1:
 * 
 * nums1 = [1, 3]
 * nums2 = [2]
 * 
 * The median is 2.0
 * 
 * 
 * 
 * Example 2:
 * 
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 * 
 * The median is (2 + 3)/2 = 2.5
 * 
 * 
 */

int max(int x, int y) {
    return x > y ? x : y;
}

int min(int x, int y) {
    return x > y ? y : x;
}

double findMedianSortedArrays(int* nums1, int nums1_size, int* nums2, int nums2_size) {
    if (nums1_size > nums2_size)
        return findMedianSortedArrays(nums2, nums2_size, nums1, nums1_size);
    int nums1_left  = 0;
    int nums1_right = nums1_size;
    int half_size   = (nums1_size + nums2_size + 1) / 2;
    while (true) {
        int nums1_index = (nums1_left + nums1_right) / 2;
        int nums2_index = half_size - nums1_index;
        if (nums1_index < nums1_size && nums1[nums1_index] < nums2[nums2_index-1]) {
            nums1_left = nums1_index + 1;
            continue;
        }
        if (nums1_index > 0 && nums1[nums1_index-1] > nums2[nums2_index]) {
            nums1_right = nums1_index - 1;
            continue;
        }
        int left_max;
        if (nums1_index == 0)
            left_max = nums2[nums2_index-1];
        else if (nums2_index == 0)
            left_max = nums1[nums1_index-1];
        else
            left_max = max(nums1[nums1_index-1], nums2[nums2_index-1]);
        if ((nums1_size+nums2_size)&1)
            return left_max;
        int right_min;
        if (nums1_index == nums1_size)
            right_min = nums2[nums2_index];
        else if (nums2_index == nums2_size)
            right_min = nums1[nums1_index];
        else
            right_min = min(nums1[nums1_index], nums2[nums2_index]);
        return (left_max + right_min) / 2.0;
    }
}

