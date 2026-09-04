/*
 * [3] Longest Substring Without Repeating Characters
 *
 * https://leetcode.com/problems/longest-substring-without-repeating-characters/description/
 *
 * algorithms
 * Medium (24.52%)
 * Total Accepted:    404.1K
 * Total Submissions: 1.6M
 * Testcase Example:  '"abcabcbb"'
 *
 * Given a string, find the length of the longest substring without repeating
 * characters.
 *
 * Examples:
 *
 * Given "abcabcbb", the answer is "abc", which the length is 3.
 *
 * Given "bbbbb", the answer is "b", with the length of 1.
 *
 * Given "pwwkew", the answer is "wke", with the length of 3. Note that the
 * answer must be a substring, "pwke" is a subsequence and not a substring.
 */
int max(int x, int y) { return x > y ? x : y; }

int lengthOfLongestSubstring(char* s) {
    int index[256];
    memset(index, -1, sizeof(index));
    int current_left = -1;
    int current_max = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        current_left = max(current_left, index[s[i]]);
        current_max = max(current_max, i - current_left);
        index[s[i]] = i;
    }
    return current_max;
}
