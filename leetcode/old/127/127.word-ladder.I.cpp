/*
 * [127] Word Ladder
 *
 * https://leetcode.com/problems/word-ladder/description/
 *
 * algorithms
 * Medium (19.73%)
 * Total Accepted:    147.4K
 * Total Submissions: 746.8K
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * 
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * the length of shortest transformation sequence from beginWord to endWord,
 * such that:
 * 
 * 
 * Only one letter can be changed at a time.
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
 * As one shortest transformation is "hit" -> "hot" -> "dot" -> "dog" -> "cog",
 * return its length 5.
 * 
 * 
 * 
 * Note:
 * 
 * Return 0 if there is no such transformation sequence.
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
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        vector<string> select;
        select.push_back(beginWord);
        int result = 1;
        while (select.empty() == false) {
            ++result;
            vector<string> temp_select;
            vector<string> temp_not_select;
            for (auto i = 0; i < wordList.size(); ++i) {
                auto j = 0;
                while (j < select.size()) {
                    if (diff(wordList[i], select[j]) == 1) {
                        if (wordList[i] == endWord)
                            return result;
                        temp_select.push_back(wordList[i]);
                        break;
                    }
                    ++j;
                }
                if (j == select.size())
                    temp_not_select.push_back(wordList[i]);
            }
            swap(wordList, temp_not_select);
            swap(select,   temp_select);
        }
        return 0;
    }

    int diff(const string& s1, const string& s2) {
        int count = 0;
        for (auto i = 0; i < s1.size(); ++i)
            if (s1[i] != s2[i])
                ++count;
        return count;
    }



};
