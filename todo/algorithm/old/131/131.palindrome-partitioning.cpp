/*
 * [131] Palindrome Partitioning
 *
 * https://leetcode.com/problems/palindrome-partitioning/description/
 *
 * algorithms
 * Medium (34.63%)
 * Total Accepted:    110.8K
 * Total Submissions: 319.6K
 * Testcase Example:  '"aab"'
 *
 *
 * Given a string s, partition s such that every substring of the partition is
 * a palindrome.
 *
 *
 * Return all possible palindrome partitioning of s.
 *
 *
 * For example, given s = "aab",
 *
 * Return
 *
 * [
 * ⁠ ["aa","b"],
 * ⁠ ["a","a","b"]
 * ]
 *
 *
 */
class Solution {
   public:
    vector<vector<string>> partition(string s) {
        vector<vector<string>> result;
        if (s.empty()) return result;
        int s_len = s.size();
        bool** f = new bool*[s_len];
        for (int i = 0; i < s_len; ++i) f[i] = new bool[s_len];
        for (int k = 0; k < s_len; ++k)
            for (int i = 0; i + k < s_len; ++i)
                f[i][i + k] =
                    s[i] == s[i + k] && (k <= 2 || f[i + 1][i + k - 1] == true);
        vector<string> temp;
        dfs(s, 0, temp, result, f);
        return result;
    }

    void dfs(string& s, int k, vector<string>& temp,
             vector<vector<string>>& result, bool** f) {
        if (s.size() == k) {
            result.push_back(temp);
            return;
        }
        for (int i = k; i < s.size(); ++i)
            if (f[k][i]) {
                temp.push_back(s.substr(k, i - k + 1));
                dfs(s, i + 1, temp, result, f);
                temp.pop_back();
            }
    }
};
