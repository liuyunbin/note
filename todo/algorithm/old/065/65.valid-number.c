/*
 * [65] Valid Number
 *
 * https://leetcode.com/problems/valid-number/description/
 *
 * algorithms
 * Hard (12.88%)
 * Total Accepted:    77.5K
 * Total Submissions: 601.8K
 * Testcase Example:  '"3"'
 *
 * Validate if a given string is numeric.
 *
 *
 * Some examples:
 * "0" => true
 * "   0.1  " => true
 * "abc" => false
 * "1 a" => false
 * "2e10" => true
 *
 *
 * Note: It is intended for the problem statement to be ambiguous. You should
 * gather all requirements up front before implementing one.
 *
 *
 *
 * Update (2015-02-10):
 * The signature of the C++ function had been updated. If you still see your
 * function signature accepts a const char * argument, please click the reload
 * button  to reset your code definition.
 *
 */
bool isNumber(char* s) {
    while (*s == ' ') ++s;
    if (*s == '-' || *s == '+') ++s;
    bool result = false;
    while (isdigit(*s)) {
        result = true;
        ++s;
    }
    if (*s == '.') ++s;
    while (isdigit(*s)) {
        result = true;
        ++s;
    }
    if (*s == 'e' && result == true) {
        ++s;
        result = false;
        if (*s == '+' || *s == '-') ++s;
        while (isdigit(*s)) {
            result = true;
            ++s;
        }
    }
    while (*s == ' ') ++s;
    return result == true && *s == '\0';
}
