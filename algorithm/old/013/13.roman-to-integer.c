/*
 * [13] Roman to Integer
 *
 * https://leetcode.com/problems/roman-to-integer/description/
 *
 * algorithms
 * Easy (47.08%)
 * Total Accepted:    195.8K
 * Total Submissions: 415.8K
 * Testcase Example:  '"DCXXI"'
 *
 * Given a roman numeral, convert it to an integer.
 * 
 * Input is guaranteed to be within the range from 1 to 3999.
 */
int romanToInt(char* s) {
    int result = 0;
    for (int i = strlen(s) - 1; i >= 0; --i)
        switch (s[i]) {
            case 'M': 
                result += 1000;
                if (i > 0 && s[i-1] == 'C') {
                    result -= 100;
                    --i;
                }
                break;
            case 'D':
                result += 500;
                if (i > 0 && s[i-1] == 'C') {
                    result -= 100;
                    --i;
                }
                break;
            case 'C':
                result += 100;
                if (i > 0 && s[i-1] == 'X') {
                    result -= 10;
                    --i;
                }
                break;
            case 'L':
                result += 50;
                if (i > 0 && s[i-1] == 'X') {
                    result -= 10;
                    --i;
                }
                break;
            case 'X':
                result += 10;
                if (i > 0 && s[i-1] == 'I') {
                    result -= 1;
                    --i;
                }
                break;
            case 'V':
                result += 5;
                if (i > 0 && s[i-1] == 'I') {
                    result -= 1;
                    --i;
                }
                break;
            case 'I':
                result += 1;
                break;
        }
    return result;
}
