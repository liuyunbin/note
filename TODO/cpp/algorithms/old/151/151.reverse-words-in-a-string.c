/*
 * [151] Reverse Words in a String
 *
 * https://leetcode.com/problems/reverse-words-in-a-string/description/
 *
 * algorithms
 * Medium (15.70%)
 * Total Accepted:    181.2K
 * Total Submissions: 1.2M
 * Testcase Example:  '""'
 *
 *
 * Given an input string, reverse the string word by word.
 *
 *
 *
 * For example,
 * Given s = "the sky is blue",
 * return "blue is sky the".
 *
 *
 *
 * Update (2015-02-12):
 * For C programmers: Try to solve it in-place in O(1) space.
 *
 *
 * click to show clarification.
 *
 * Clarification:
 *
 *
 *
 * What constitutes a word?
 * A sequence of non-space characters constitutes a word.
 * Could the input string contain leading or trailing spaces?
 * Yes. However, your reversed string should not contain leading or trailing
 * spaces.
 * How about multiple spaces between two words?
 * Reduce them to a single space in the reversed string.
 *
 *
 *
 */
void reverse(char* s, int len) {
    int left = 0;
    int right = len - 1;
    while (left < right) {
        char ch = s[left];
        s[left] = s[right];
        s[right] = ch;
        ++left;
        --right;
    }
}

void reverseWords(char* s) {
    int k = 0;
    int i = 0;
    while (s[i] == ' ') ++i;
    while (s[i] != '\0')
        if (s[i] != ' ')
            s[k++] = s[i++];
        else {
            s[k++] = s[i++];
            while (s[i] == ' ') ++i;
        }
    if (s[k - 1] == ' ') --k;
    s[k] = '\0';
    int s_len = strlen(s);
    reverse(s, s_len);
    for (i = 0; i < s_len;) {
        int j = i;
        while (j < s_len && s[j] != ' ') ++j;
        reverse(s + i, j - i);
        i = j + 1;
    }
}
