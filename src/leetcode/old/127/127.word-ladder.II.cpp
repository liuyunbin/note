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
        unordered_set<string> word1;
        word1.insert(beginWord);
        unordered_set<string> word2;
        word2.insert(endWord);
        int result = 1;
        unordered_set<string> dict;
        for (auto str:wordList)
            if (str != beginWord)
                dict.insert(str);
        if (dict.find(endWord) == dict.end())
            return 0;
        dict.erase(endWord);
        while (word1.empty() == false) {
            ++result;
            unordered_set<string> word3;
            for (auto str:word1)
                for (auto i = 0; i < str.size(); ++i) {
                    string temp = str;    
                    for (auto ch = 'a'; ch <= 'z'; ++ch) {
                        temp[i] = ch;
                        if (word2.find(temp) != word2.end())
                            return result;
                        if (dict.find(temp)  != dict.end()) {
                            dict.erase(temp);
                            word3.insert(temp);
                        }
                    }
                }
            swap(word1, word3);
            if (word1.size() > word2.size())
                swap(word1, word2);
        }
        return 0;
    }
};
