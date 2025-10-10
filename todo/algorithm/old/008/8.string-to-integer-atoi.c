/*
 * [8] String to Integer (atoi)
 *
 * https://leetcode.com/problems/string-to-integer-atoi
 *
 * algorithms
 * Medium (13.94%)
 * Total Accepted:    198.6K
 * Total Submissions: 1.4M
 * Testcase Example:  '""'
 *
 * Implement atoi to convert a string to an integer.
 *
 * Hint: Carefully consider all possible input cases. If you want a challenge,
 * please do not see below and ask yourself what are the possible input
 * cases.
 *
 *
 * Notes:
 * It is intended for this problem to be specified vaguely (ie, no given input
 * specs). You are responsible to gather all the input requirements up
 * front.
 *
 *
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button  to reset your code definition.
 *
 *
 * spoilers alert... click to show requirements for atoi.
 *
 * Requirements for atoi:
 *
 * The function first discards as many whitespace characters as necessary until
 * the first non-whitespace character is found. Then, starting from this
 * character, takes an optional initial plus or minus sign followed by as many
 * numerical digits as possible, and interprets them as a numerical value.
 *
 * The string can contain additional characters after those that form the
 * integral number, which are ignored and have no effect on the behavior of
 * this function.
 *
 * If the first sequence of non-whitespace characters in str is not a valid
 * integral number, or if no such sequence exists because either str is empty
 * or it contains only whitespace characters, no conversion is performed.
 *
 * If no valid conversion could be performed, a zero value is returned. If the
 * correct value is out of the range of representable values, INT_MAX
 * (2147483647) or INT_MIN (-2147483648) is returned.
 *
 *
 */
int myAtoi(char* str) {
    while (*str == ' ') ++str;
    int sign = 1;
    if (*str == '-' || *str == '+') {
        if (*str == '-') sign = -1;
        ++str;
    }
    long long result = 0;
    while (isdigit(*str)) {
        result = result * 10 + *str - '0';
        ++str;
        if (result * sign > INT_MAX) return INT_MAX;
        if (result * sign < INT_MIN) return INT_MIN;
    }
    return result * sign;
}
