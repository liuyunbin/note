/*
 * [126] Word Ladder II
 *
 * https://leetcode.com/problems/word-ladder-ii/description/
 *
 * algorithms
 * Hard (14.58%)
 * Total Accepted:    76.4K
 * Total Submissions: 524.1K
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 *
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * all shortest transformation sequence(s) from beginWord to endWord, such
 * that:
 *
 *
 * Only one letter can be changed at a time
 * Each transformed word must exist in the word list. Note that beginWord is
 * not a transformed word.
 *
 *
 *
 * For example,
 *
 *
 * Given:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 *
 * Return
 *
 * ⁠ [
 * ⁠   ["hit","hot","dot","dog","cog"],
 * ⁠   ["hit","hot","lot","log","cog"]
 * ⁠ ]
 *
 *
 *
 *
 * Note:
 *
 * Return an empty list if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 *
 *
 *
 *
 * UPDATE (2017/1/20):
 * The wordList parameter had been changed to a list of strings (instead of a
 * set of strings). Please reload the code definition to get the latest
 * changes.
 *
 */
class Solution {
   public:
    vector<vector<string>> findLadders(string beginWord, string endWord,
                                       vector<string>& wordList) {
        vector<vector<string>> result;
        unordered_set<string> dict;
        for (auto str : wordList) dict.insert(str);
        if (dict.find(endWord) == dict.end()) return result;
        unordered_set<string> word1;
        word1.insert(beginWord);
        unordered_set<string> word2;
        word2.insert(endWord);
        unordered_map<string, vector<string>> previous;
        previous[beginWord] = vector<string>();
        bool have_find_answer = false;
        bool word1_to_word2 = true;
        while (word1.empty() != true) {
            for (auto str : word1) dict.erase(str);
            for (auto str : word2) dict.erase(str);
            unordered_set<string> word3;
            for (auto str : word1)
                for (auto i = 0; i < str.size(); ++i) {
                    auto temp = str;
                    for (auto ch = 'a'; ch <= 'z'; ++ch) {
                        temp[i] = ch;
                        if (word2.find(temp) != word2.end()) {
                            if (word1_to_word2 == true)
                                previous[temp].push_back(str);
                            else
                                previous[str].push_back(temp);
                            have_find_answer = true;
                        }
                        if (dict.find(temp) != dict.end()) {
                            word3.insert(temp);
                            if (word1_to_word2 == true)
                                previous[temp].push_back(str);
                            else
                                previous[str].push_back(temp);
                        }
                    }
                }
            if (have_find_answer == true) break;
            swap(word1, word3);
            if (word1.size() > word2.size()) {
                swap(word1, word2);
                word1_to_word2 = !word1_to_word2;
            }
        }
        if (have_find_answer == true) {
            list<string> temp;
            temp.push_back(endWord);
            backtrack(beginWord, endWord, temp, previous, result);
        }
        return result;
    }

    void backtrack(string& beginWord, string& endWord, list<string>& temp,
                   unordered_map<string, vector<string>>& previous,
                   vector<vector<string>>& result) {
        if (previous[endWord].size() == 0) {
            if (beginWord == endWord)
                result.push_back(vector<string>(temp.begin(), temp.end()));
            return;
        }
        for (auto str : previous[endWord]) {
            temp.push_front(str);
            backtrack(beginWord, str, temp, previous, result);
            temp.pop_front();
        }
    }
};
