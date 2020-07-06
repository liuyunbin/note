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
    vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
        vector<vector<string>> result;
        vector<string> select;
        select.push_back(beginWord);
        unordered_map<string, vector<string>> my_map;
        my_map[beginWord] = vector<string>();
        bool if_have_answer = false;
        while (select.empty() != true) {
            vector<string> temp_select;
            vector<string> temp_not_select;
            for (int i = 0; i < wordList.size(); ++i) {
                if (wordList[i] == beginWord)
                    continue;
                bool if_add_i = false;
                for (int j = 0; j < select.size(); ++j)
                    if (diff(wordList[i], select[j]) == 1) {
                        if (wordList[i] == endWord)
                            if_have_answer = true;
                        my_map[wordList[i]].push_back(select[j]);
                        if (if_add_i == false) {
                            if_add_i = true;
                            temp_select.push_back(wordList[i]);
                        }
                    }
                if (if_add_i == false)
                    temp_not_select.push_back(wordList[i]);
                if (if_have_answer == true)
                    break;
            }
            if (if_have_answer == true)
                break;
            swap(wordList, temp_not_select);
            swap(select,   temp_select);
        }
        if (if_have_answer == true) {
            list<string> temp;
            temp.push_back(endWord);
            backtrack(endWord, my_map, temp, result);
        }
        return result;
    }

    void backtrack(const string& endWord, unordered_map<string, vector<string>>& my_map, list<string>& temp, 
            vector<vector<string>>& result) {
        if (my_map[endWord].size() == 0) {
            result.push_back(vector<string>(temp.begin(), temp.end()));
            return ;
        }
        for (auto str:my_map[endWord]) {
            temp.push_front(str);
            backtrack(str, my_map, temp, result);
            temp.pop_front();
        }
    }

    int diff(const string& s1, const string& s2) {
        int count = 0;
        for (int i = 0; i < s1.size(); ++i)
            if (s1[i] != s2[i])
                ++count;
        return count;
    }
};
