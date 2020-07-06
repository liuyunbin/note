/*
 * [43] Multiply Strings
 *
 * https://leetcode.com/problems/multiply-strings/description/
 *
 * algorithms
 * Medium (27.70%)
 * Total Accepted:    124.2K
 * Total Submissions: 448.3K
 * Testcase Example:  '"0"\n"0"'
 *
 * Given two non-negative integers num1 and num2 represented as strings, return
 * the product of num1 and num2.
 * 
 * Note:
 * 
 * The length of both num1 and num2 is < 110.
 * Both num1 and num2 contains only digits 0-9.
 * Both num1 and num2 does not contain any leading zero.
 * You must not use any built-in BigInteger library or convert the inputs to
 * integer directly.
 * 
 * 
 */
char* multiply(char* num1, char* num2) {
    int num1_len = strlen(num1);
    int num2_len = strlen(num2);
    int result_max_len = num1_len + num2_len;
    char* result       = (char*)malloc(sizeof(char)*(result_max_len+1));
    int result_index   = 0;
    for (int i = 0; i < result_max_len; ++i)
        result[i] = '0';
    int begin_index = 0;
    for (int i = num1_len - 1; i >= 0; --i) {
        result_index = begin_index++;
        int count = 0;
        for (int j = num2_len - 1; j >= 0; --j) {
            count += result[result_index] - '0';
            count += (num1[i] - '0') * (num2[j] - '0');
            result[result_index++] = '0' + count % 10;
            count /= 10;
        }
        if (count != 0)
            result[result_index++] = count + '0';
    }
    result[result_index] = '\0';
    int  left = 0;
    int right = result_index - 1;
    while (left < right) {
        char temp = result[left];
        result[left] = result[right];
        result[right] = temp;
        ++left;
        --right;
    }
    if (result[0] == '0')
        result[1] = '\0';
    return result;
}
