/*
 * [67] Add Binary
 *
 * https://leetcode.com/problems/add-binary/description/
 *
 * algorithms
 * Easy (33.43%)
 * Total Accepted:    177.3K
 * Total Submissions: 530.2K
 * Testcase Example:  '"0"\n"0"'
 *
 *
 * Given two binary strings, return their sum (also a binary string).
 *
 *
 *
 * For example,
 * a = "11"
 * b = "1"
 * Return "100".
 *
 */

int max(int x, int y) { return x > y ? x : y; }

char* addBinary(char* a, char* b) {
    int a_len = strlen(a);
    int b_len = strlen(b);
    char* result = (char*)malloc(sizeof(char) * (max(a_len, b_len) + 2));
    int result_index = 0;
    int count = 0;
    for (int i = a_len - 1, j = b_len - 1; i >= 0 || j >= 0 || count != 0;) {
        if (i >= 0) {
            count += a[i] - '0';
            --i;
        }
        if (j >= 0) {
            count += b[j] - '0';
            --j;
        }
        result[result_index++] = count % 2 + '0';
        count /= 2;
    }
    result[result_index] = '\0';
    int left = 0;
    int right = result_index - 1;
    while (left < right) {
        char ch = result[left];
        result[left] = result[right];
        result[right] = ch;
        ++left;
        --right;
    }
    return result;
}
