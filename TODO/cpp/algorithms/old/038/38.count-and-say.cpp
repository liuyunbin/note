/*
 * [38] Count and Say
 *
 * https://leetcode.com/problems/count-and-say/description/
 *
 * algorithms
 * Easy (35.94%)
 * Total Accepted:    168.3K
 * Total Submissions: 468.2K
 * Testcase Example:  '1'
 *
 * The count-and-say sequence is the sequence of integers with the first five
 * terms as following:
 *
 * 1.     1
 * 2.     11
 * 3.     21
 * 4.     1211
 * 5.     111221
 *
 *
 *
 * 1 is read off as "one 1" or 11.
 * 11 is read off as "two 1s" or 21.
 * 21 is read off as "one 2, then one 1" or 1211.
 *
 *
 *
 * Given an integer n, generate the nth term of the count-and-say sequence.
 *
 *
 *
 * Note: Each term of the sequence of integers will be represented as a
 * string.
 *
 *
 * Example 1:
 *
 * Input: 1
 * Output: "1"
 *
 *
 *
 * Example 2:
 *
 * Input: 4
 * Output: "1211"
 *
 *
 */
class Solution {
   public:
    string countAndSay(int n) {
        string result;
        if (n <= 0) return result;
        result = "1";
        for (int i = 1; i < n; ++i) {
            string temp;
            for (int j = 0; j < result.size();) {
                int count = 1;
                ++j;
                while (j < result.size() && result[j] == result[j - 1]) {
                    ++j;
                    ++count;
                }
                temp += to_string(count) + result[j - 1];
            }
            temp.swap(result);
        }
        return result;
    }
};
