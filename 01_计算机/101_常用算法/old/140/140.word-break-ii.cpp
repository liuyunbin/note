/*
 * [140] Word Break II
 *
 * https://leetcode.com/problems/word-break-ii/description/
 *
 * algorithms
 * Hard (24.04%)
 * Total Accepted:    104.3K
 * Total Submissions: 433.4K
 * Testcase Example:  '"catsanddog"\n["cat","cats","and","sand","dog"]'
 *
 * 
 * Given a non-empty string s and a dictionary wordDict containing a list of
 * non-empty words, add spaces in s to construct a sentence where each word is
 * a valid dictionary word. You may assume the dictionary does not contain
 * duplicate words.
 * 
 * 
 * 
 * Return all such possible sentences.
 * 
 * 
 * 
 * For example, given
 * s = "catsanddog",
 * dict = ["cat", "cats", "and", "sand", "dog"].
 * 
 * 
 * 
 * A solution is ["cats and dog", "cat sand dog"].
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
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> my_set(wordDict.begin(), wordDict.end());
        vector<bool> f(s.size()+1, false);
        f[0] = true;
        vector<vector<int>> temp(s.size() + 1, vector<int>());
        for (int i = 1; i <= s.size(); ++i)
            for (int j = 0; j < i; ++j)
                if (f[j] == true && my_set.find(s.substr(j, i - j)) != my_set.end()) {
                    f[i] = true;
                    temp[i].push_back(j);
                }
        vector<string> result;
        if (f[s.size()] == true) {
            string str;
            dfs(s, str, temp, s.size(), result);
        }
        return result;
    }

    void dfs(string s, string str, vector<vector<int>>& temp, int k, vector<string>& result) {
        if (temp[k].size() == 0) {
            result.push_back(str);    
            return ;
        }
        for (auto i:temp[k]) {
            if (str.size() == 0)
                dfs(s, s.substr(i, k - i), temp, i, result);
            else
                dfs(s, s.substr(i, k - i) + " " + str, temp, i, result);
        }
    }
};
