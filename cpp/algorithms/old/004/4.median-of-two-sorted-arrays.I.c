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

int min(int x, int y) { return x > y ? y : x; }

int find_kth_element(const int* nums1, int nums1_size, const int* nums2,
                     int nums2_size, int k) {
    if (nums1_size > nums2_size)
        return find_kth_element(nums2, nums2_size, nums1, nums1_size, k);
    if (nums1_size == 0) return nums2[k - 1];
    if (k == 1) return min(nums1[0], nums2[0]);
    int nums1_index = min(k / 2, nums1_size);
    int nums2_index = k - nums1_index;
    if (nums1[nums1_index - 1] == nums2[nums2_index - 1])
        return nums1[nums1_index - 1];
    if (nums1[nums1_index - 1] < nums2[nums2_index - 1])
        return find_kth_element(nums1 + nums1_index, nums1_size - nums1_index,
                                nums2, nums2_index, k - nums1_index);
    return find_kth_element(nums1, nums1_index, nums2 + nums2_index,
                            nums2_size - nums2_index, k - nums2_index);
}

double findMedianSortedArrays(int* nums1, int nums1_size, int* nums2,
                              int nums2_size) {
    int nums_size = nums1_size + nums2_size;
    double result = find_kth_element(nums1, nums1_size, nums2, nums2_size,
                                     nums_size / 2 + 1);
    if (nums_size & 1) return result;
    result +=
        find_kth_element(nums1, nums1_size, nums2, nums2_size, nums_size / 2);
    return result / 2.0;
}
