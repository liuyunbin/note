/*
 * [22] Generate Parentheses
 *
 * https://leetcode.com/problems/generate-parentheses/description/
 *
 * algorithms
 * Medium (46.73%)
 * Total Accepted:    183.1K
 * Total Submissions: 391.8K
 * Testcase Example:  '3'
 *
 * 
 * Given n pairs of parentheses, write a function to generate all combinations
 * of well-formed parentheses.
 * 
 * 
 * 
 * For example, given n = 3, a solution set is:
 * 
 * 
 * [
 * ⁠ "((()))",
 * ⁠ "(()())",
 * ⁠ "(())()",
 * ⁠ "()(())",
 * ⁠ "()()()"
 * ]
 * 
 */
class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
        if (n <= 0)
            return result;
        string temp;
        backtrack(n, 0, 0, temp, result);
        return result;
    }

private:
    void backtrack(int n, int left, int right, string& temp, vector<string>& result) {
        if (left == n && right == n) {
            result.push_back(temp);
            return ;
        }
        if (left < n) {
            temp.push_back('(');
            backtrack(n, left + 1, right, temp, result);
            temp.pop_back();
        }
        if (right < left) {
            temp.push_back(')');
            backtrack(n, left, right + 1, temp, result);
            temp.pop_back();
        }
    }
};
