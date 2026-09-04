/*
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (24.06%)
 * Total Accepted:    318.4K
 * Total Submissions: 1.3M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * You may assume nums1 and nums2 cannot be both empty.
 *
 * Example 1:
 *
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 *
 * Example 2:
 *
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 *
 *
 */
class Solution {
   public:
    int findkth(const int* nums1, int nums1_len, const int* nums2,
                int nums2_len, int k) {
        if (nums1_len > nums2_len)
            return findkth(nums2, nums2_len, nums1, nums1_len, k);
        if (nums1_len == 0) return nums2[k - 1];
        if (k == 1) return min(*nums1, *nums2);
        int nums1_index = min(nums1_len, k / 2);
        int nums2_index = k - nums1_index;
        if (nums1[nums1_index - 1] == nums2[nums2_index - 1])
            return nums1[nums1_index - 1];
        if (nums1[nums1_index - 1] < nums2[nums2_index - 1])
            return findkth(nums1 + nums1_index, nums1_len - nums1_index, nums2,
                           nums2_index, k - nums1_index);
        return findkth(nums2 + nums2_index, nums2_len - nums2_index, nums1,
                       nums1_index, k - nums2_index);
    }

    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int nums1_len = nums1.size();
        int nums2_len = nums2.size();
        int len = nums1_len + nums2_len;
        int k = len / 2 + 1;
        if (len % 2 != 0)
            return findkth(nums1.data(), nums1_len, nums2.data(), nums2_len, k);
        return (findkth(nums1.data(), nums1_len, nums2.data(), nums2_len, k) +
                findkth(nums1.data(), nums1_len, nums2.data(), nums2_len,
                        k - 1)) /
               2.0;
    }
};
