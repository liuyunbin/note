/*
 * [30] Substring with Concatenation of All Words
 *
 * https://leetcode.com/problems/substring-with-concatenation-of-all-words/description/
 *
 * algorithms
 * Hard (22.16%)
 * Total Accepted:    90K
 * Total Submissions: 406.3K
 * Testcase Example:  '"barfoothefoobarman"\n["foo","bar"]'
 *
 * 
 * You are given a string, s, and a list of words, words, that are all of the
 * same length. Find all starting indices of substring(s) in s that is a
 * concatenation of each word in words exactly once and without any intervening
 * characters.
 * 
 * 
 * 
 * For example, given:
 * s: "barfoothefoobarman"
 * words: ["foo", "bar"]
 * 
 * 
 * 
 * You should return the indices: [0,9].
 * (order does not matter).
 * 
 */
class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> result;
        if (words.size() == 0)
            return result;
        int word_len = words[0].size();
        unordered_map<string, int> map_words;
        for (int i = 0; i < words.size(); ++i)
            ++map_words[words[i]];
        for (int i = 0; i < word_len; ++i) {
            unordered_map<string, int> map_s;
            int number = 0;
            int left = i;
            for (int j = i; j + word_len <= s.size(); j += word_len) {
                string str = s.substr(j, word_len);
                if (map_words.find(str) == map_words.end()) {
                    map_s.clear();
                    left = j + word_len;
                    number = 0;
                    continue;
                }
                if (map_s[str] < map_words[str]) {
                    ++map_s[str];
                    ++number;
                    if (number == words.size()) {
                        result.push_back(left);
                        string temp = s.substr(left, word_len);
                        if (--map_s[temp] == 0)
                            map_s.erase(temp);
                        left += word_len;
                        --number;
                    }
                    continue;
                }
                while (map_s[str] == map_words[str]) {
                    string temp = s.substr(left, word_len);
                    if (--map_s[temp] == 0)
                        map_s.erase(temp);
                    left += word_len;
                    --number;
                }
                ++map_s[str];
                ++number;
            }
        }
        return result;
    }
};
