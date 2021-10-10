/*
 * [49] Group Anagrams
 *
 * https://leetcode.com/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (36.84%)
 * Total Accepted:    171.4K
 * Total Submissions: 465.1K
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * Given an array of strings, group anagrams together.
 * 
 * 
 * For example, given: ["eat", "tea", "tan", "ate", "nat", "bat"], 
 * Return:
 * 
 * [
 * ⁠ ["ate", "eat","tea"],
 * ⁠ ["nat","tan"],
 * ⁠ ["bat"]
 * ]
 * 
 * Note: All inputs will be in lower-case.
 */
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> my_map;
        for (auto str:strs) {
            string temp = str;
            sort(temp.begin(), temp.end());
            my_map[temp].push_back(str);
        }
        vector<vector<string>> result;
        for (auto str:my_map)
            result.push_back(move(str.second));
        return result;
    }
};
