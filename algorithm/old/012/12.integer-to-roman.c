/*
 * [12] Integer to Roman
 *
 * https://leetcode.com/problems/integer-to-roman/description/
 *
 * algorithms
 * Medium (45.69%)
 * Total Accepted:    126.3K
 * Total Submissions: 276.4K
 * Testcase Example:  '1'
 *
 * Given an integer, convert it to a roman numeral.
 *
 *
 * Input is guaranteed to be within the range from 1 to 3999.
 */
#define MAX 16
char* intToRoman(int num) {
    char one[][5] = {"",  "I",  "II",  "III",  "IV",
                     "V", "VI", "VII", "VIII", "IX"};
    char two[][5] = {"",  "X",  "XX",  "XXX",  "XL",
                     "L", "LX", "LXX", "LXXX", "XC"};
    char three[][5] = {"",  "C",  "CC",  "CCC",  "CD",
                       "D", "DC", "DCC", "DCCC", "CM"};
    char four[][5] = {"", "M", "MM", "MMM"};
    char* result = (char*)malloc(sizeof(char) * MAX);
    result[0] = '\0';
    strcat(result, four[num / 1000]);
    num %= 1000;
    strcat(result, three[num / 100]);
    num %= 100;
    strcat(result, two[num / 10]);
    num %= 10;
    strcat(result, one[num]);
    return result;
}
