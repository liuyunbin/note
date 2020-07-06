/*
 * [3] Longest Substring Without Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (25.11%)
 * Total Accepted:    613.2K
 * Total Submissions: 2.4M
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string, find the length of the longest substring without repeating
 * characters.
 *
 *
 * Example 1:
 *
 *
 * Input: "abcabcbb"
 * Output: 3
 * Explanation: The answer is "abc", with the length of 3.
 *
 *
 *
 * Example 2:
 *
 *
 * Input: "bbbbb"
 * Output: 1
 * Explanation: The answer is "b", with the length of 1.
 *
 *
 *
 * Example 3:
 *
 *
 * Input: "pwwkew"
 * Output: 3
 * Explanation: The answer is "wke", with the length of 3.
 * ⁠            Note that the answer must be a substring, "pwke" is a
 * subsequence and not a substring.
 *
 *
 *
 *
 *
 */
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int index[127];
        for (int i = 0; i != sizeof(index) / sizeof(*index); ++i)
            index[i] = -1;
        int ret = 0;
        int current_low_index = -1;
        for (int i = 0; i != s.size(); ++i) {
            current_low_index = max(current_low_index, index[s[i]]);
            index[s[i]] = i;
            ret = max(ret, i - current_low_index);
        }
        return ret;
    }
};
