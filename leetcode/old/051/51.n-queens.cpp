/*
 * [51] N-Queens
 *
 * https://leetcode.com/problems/n-queens/description/
 *
 * algorithms
 * Hard (32.35%)
 * Total Accepted:    91.5K
 * Total Submissions: 282.6K
 * Testcase Example:  '4'
 *
 * The n-queens puzzle is the problem of placing n queens on an n×n chessboard
 * such that no two queens attack each other.
 * 
 * 
 * 
 * Given an integer n, return all distinct solutions to the n-queens puzzle.
 * 
 * Each solution contains a distinct board configuration of the n-queens'
 * placement, where 'Q' and '.' both indicate a queen and an empty space
 * respectively.
 * 
 * For example,
 * There exist two distinct solutions to the 4-queens puzzle:
 * 
 * [
 * ⁠[".Q..",  // Solution 1
 * ⁠ "...Q",
 * ⁠ "Q...",
 * ⁠ "..Q."],
 * 
 * ⁠["..Q.",  // Solution 2
 * ⁠ "Q...",
 * ⁠ "...Q",
 * ⁠ ".Q.."]
 * ]
 * 
 */
class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> result;
        if (n <= 0)
            return result;
        vector<int> temp(n, 0);
        backtrack(n, 0, temp, result);
        return result;
    }

private:
    void backtrack(int n, int k, vector<int>& temp, vector<vector<string>>& result) {
        if (k == n) {
            vector<string> queen(n, string(n, '.'));
            for (int i = 0; i < temp.size(); ++i) {
                cout << queen[i] << endl;
                queen[i][temp[i]] = 'Q';
            }
            result.push_back(queen);
            return ;
        }
        for (int col = 0; col < n; ++col) {
            int row = 0;
            while (row < k && temp[row] != col && k-row != abs(col-temp[row]))
                ++row;
            if (row == k) {
                temp[k] = col;
                backtrack(n, k + 1, temp, result);
            }
        }
    }
};
