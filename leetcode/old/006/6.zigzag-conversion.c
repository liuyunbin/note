/*
 * [6] ZigZag Conversion
 *
 * https://leetcode.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (27.05%)
 * Total Accepted:    185.2K
 * Total Submissions: 684.7K
 * Testcase Example:  '""\n1'
 *
 * 
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 * 
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 * 
 * 
 * And then read line by line: "PAHNAPLSIIGYIR"
 * 
 * 
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 * 
 * string convert(string text, int nRows);
 * 
 * convert("PAYPALISHIRING", 3) should return "PAHNAPLSIIGYIR".
 * 
 */
char* convert(char* s, int numRows) {
    int s_len = strlen(s);
    if (s_len == 0 || s_len <= numRows || numRows <= 1)
        return s;
    char* result       = (char*)malloc(sizeof(char)*(s_len+1));
    int   result_index = 0;
    for (int i = 0; i < numRows; ++i)
        for (int j = i; j < s_len; j += 2*(numRows-1)) {
            result[result_index++] = s[j];
            if (i == 0 || i + 1 == numRows)
                continue;
            int index = j + 2 * (numRows-i-1);
            if (index < s_len)
                result[result_index++] = s[index];
        }
    result[result_index] = '\0';
    return result;
}

