/*
 * [139] Word Break
 *
 * https://leetcode.com/problems/word-break/description/
 *
 * algorithms
 * Medium (30.92%)
 * Total Accepted:    186.1K
 * Total Submissions: 601.5K
 * Testcase Example:  '"leetcode"\n["leet","code"]'
 *
 * 
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, determine if s can be segmented into a space-separated
 * sequence of one or more dictionary words. You may assume the dictionary does
 * not contain duplicate words.
 * 
 * 
 * For example, given
 * s = "leetcode",
 * dict = ["leet", "code"].
 * 
 * 
 * 
 * Return true because "leetcode" can be segmented as "leet code".
 * 
 * 
 * 
 * UPDATE (2017/1/4):
 * The wordDict parameter had been changed to a list of strings (instead of a
 * set of strings). Please reload the code definition to get the latest
 * changes.
 * 
 */
class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> my_set(wordDict.begin(), wordDict.end());
        vector<bool> f(s.size() + 1, false);
        f[0] = true;
        for (int i = 1; i <= s.size(); ++i)
            for (int j = 0; j < i; ++j)
                if (f[j] == true && my_set.find(s.substr(j, i - j)) != my_set.end()) {
                    f[i] = true;
                    break;
                }
        return f[s.size()];
    }
};
