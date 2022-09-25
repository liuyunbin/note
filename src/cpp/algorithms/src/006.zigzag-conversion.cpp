/*
 * [6] ZigZag Conversion
 *
 * https://leetcode.com/problems/zigzag-conversion/description/
 *
 * algorithms
 * Medium (28.85%)
 * Total Accepted:    246.6K
 * Total Submissions: 853.5K
 * Testcase Example:  '"PAYPALISHIRING"\n3'
 *
 * The string "PAYPALISHIRING" is written in a zigzag pattern on a given number
 * of rows like this: (you may want to display this pattern in a fixed font for
 * better legibility)
 *
 *
 * P   A   H   N
 * A P L S I I G
 * Y   I   R
 *
 *
 * And then read line by line: "PAHNAPLSIIGYIR"
 *
 * Write the code that will take a string and make this conversion given a
 * number of rows:
 *
 *
 * string convert(string s, int numRows);
 *
 * Example 1:
 *
 *
 * Input: s = "PAYPALISHIRING", numRows = 3
 * Output: "PAHNAPLSIIGYIR"
 *
 *
 * Example 2:
 *
 *
 * Input: s = "PAYPALISHIRING", numRows = 4
 * Output: "PINALSIGYAHRPI"
 * Explanation:
 *
 * P     I    N
 * A   L S  I G
 * Y A   H R
 * P     I
 *
 */
class Solution {
   public:
    string convert(string s, int numRows) {
        if (numRows <= 1) return s;
        string st = s;
        int k = 0;

        int step = (numRows - 1) * 2;
        for (int i = 0; i < s.size(); i += step) st[k++] = s[i];

        for (int i = 1; i + 1 < numRows; ++i) {
            int temp_step = (numRows - i - 1) * 2;
            for (int j = i; j < s.size(); j += step) {
                st[k++] = s[j];
                int index = j + temp_step;
                if (index < s.size()) st[k++] = s[index];
            }
        }

        for (int i = numRows - 1; i < s.size(); i += step) st[k++] = s[i];

        return st;
    }
};
