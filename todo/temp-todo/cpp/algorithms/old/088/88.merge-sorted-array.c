/*
 * [88] Merge Sorted Array
 *
 * https://leetcode.com/problems/merge-sorted-array/description/
 *
 * algorithms
 * Easy (32.11%)
 * Total Accepted:    203.7K
 * Total Submissions: 634.5K
 * Testcase Example:  '[1]\n1\n[]\n0'
 *
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as
 * one sorted array.
 *
 *
 * Note:
 * You may assume that nums1 has enough space (size that is greater or equal to
 * m + n) to hold additional elements from nums2. The number of elements
 * initialized in nums1 and nums2 are m and n respectively.
 */
void merge(int* nums1, int m, int* nums2, int n) {
    int* nums3 = (int*)malloc(sizeof(int) * (m + n));
    int i = 0;
    int j = 0;
    int k = 0;
    while (i < m && j < n)
        if (nums1[i] < nums2[j])
            nums3[k++] = nums1[i++];
        else
            nums3[k++] = nums2[j++];
    while (i < m) nums3[k++] = nums1[i++];
    while (j < n) nums3[k++] = nums2[j++];
    memcpy(nums1, nums3, sizeof(int) * (m + n));
    free(nums3);
}
