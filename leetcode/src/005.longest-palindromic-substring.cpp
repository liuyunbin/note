/*
 * [5] Longest Palindromic Substring
 *
 * https://leetcode.com/problems/longest-palindromic-substring/description/
 *
 * algorithms
 * Medium (25.62%)
 * Total Accepted:    392.7K
 * Total Submissions: 1.5M
 * Testcase Example:  '"babad"'
 *
 * Given a string s, find the longest palindromic substring in s. You may
 * assume that the maximum length of s is 1000.
 *
 * Example 1:
 *
 *
 * Input: "babad"
 * Output: "bab"
 * Note: "aba" is also a valid answer.
 *
 *
 * Example 2:
 *
 *
 * Input: "cbbd"
 * Output: "bb"
 *
 *
 */
class Solution {
public:
    string longestPalindrome(string s) {
        int index = 0;
        int len   = 0;
        for (int i = 0; i != s.size(); ++i) {
            int left  = i;
            int right = i;
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                --left;
                ++right;
            }
            if (right - left - 1 > len) {
                index = left + 1;
                len = right - left - 1;
            }
            if (i == 0)
                continue;
            left  = i - 1;
            right = i;
            while (left >= 0 && right < s.size() && s[left] == s[right]) {
                --left;
                ++right;
            }
            if (right - left - 1 > len) {
                index = left + 1;
                len = right - left - 1;
            }
        }
        return s.substr(index, len);
    }
};
