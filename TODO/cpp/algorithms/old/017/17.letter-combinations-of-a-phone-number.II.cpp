/*
 * [17] Letter Combinations of a Phone Number
 *
 * https://leetcode.com/problems/letter-combinations-of-a-phone-number/description/
 *
 * algorithms
 * Medium (35.59%)
 * Total Accepted:    199.3K
 * Total Submissions: 560K
 * Testcase Example:  '""'
 *
 * Given a digit string, return all possible letter combinations that the
 * number could represent.
 *
 *
 *
 * A mapping of digit to letters (just like on the telephone buttons) is given
 * below.
 *
 *
 *
 * Input:Digit string "23"
 * Output: ["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"].
 *
 *
 *
 * Note:
 * Although the above answer is in lexicographical order, your answer could be
 * in any order you want.
 *
 */
class Solution {
   public:
    vector<string> letterCombinations(string digits) {
        vector<string> result;
        if (digits.size() == 0) return result;
        const vector<string> number = {"",    "",    "abc",  "def", "ghi",
                                       "jkl", "mno", "pqrs", "tuv", "wxyz"};
        result.push_back("");
        for (int k = 0; k < digits.size(); ++k) {
            vector<string> temp;
            for (int i = 0; i < number[digits[k] - '0'].size(); ++i)
                for (int j = 0; j < result.size(); ++j)
                    temp.push_back(result[j] + number[digits[k] - '0'][i]);
            result.swap(temp);
        }
        return result;
    }
};
