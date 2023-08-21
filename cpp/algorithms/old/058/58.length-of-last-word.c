/*
 * [58] Length of Last Word
 *
 * https://leetcode.com/problems/length-of-last-word/description/
 *
 * algorithms
 * Easy (32.00%)
 * Total Accepted:    172K
 * Total Submissions: 537.5K
 * Testcase Example:  '"Hello World"'
 *
 * Given a string s consists of upper/lower-case alphabets and empty space
 * characters ' ', return the length of last word in the string.
 *
 * If the last word does not exist, return 0.
 *
 * Note: A word is defined as a character sequence consists of non-space
 * characters only.
 *
 * Example:
 *
 * Input: "Hello World"
 * Output: 5
 *
 *
 */
int lengthOfLastWord(char* s) {
    int i = strlen(s) - 1;
    while (i >= 0 && s[i] == ' ') --i;
    int count = 0;
    while (i >= 0 && s[i] != ' ') {
        --i;
        ++count;
    }
    return count;
}
