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
        string temp;
        backtrack(digits, 0, number, temp, result);
        return result;
    }

   private:
    void backtrack(const string& digits, int k, const vector<string>& number,
                   string& temp, vector<string>& result) {
        if (k == digits.size()) {
            result.push_back(temp);
            return;
        }
        for (int i = 0; i < number[digits[k] - '0'].size(); ++i) {
            temp.push_back(number[digits[k] - '0'][i]);
            backtrack(digits, k + 1, number, temp, result);
            temp.pop_back();
        }
    }
};
