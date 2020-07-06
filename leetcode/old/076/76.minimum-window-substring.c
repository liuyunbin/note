/*
 * [76] Minimum Window Substring
 *
 * https://leetcode.com/problems/minimum-window-substring/description/
 *
 * algorithms
 * Hard (26.31%)
 * Total Accepted:    129.2K
 * Total Submissions: 490.8K
 * Testcase Example:  '"a"\n"a"'
 *
 * 
 * Given a string S and a string T, find the minimum window in S which will
 * contain all the characters in T in complexity O(n).
 * 
 * 
 * 
 * For example,
 * S = "ADOBECODEBANC"
 * T = "ABC"
 * 
 * 
 * Minimum window is "BANC".
 * 
 * 
 * 
 * Note:
 * If there is no such window in S that covers all characters in T, return the
 * empty string "".
 * 
 * 
 * If there are multiple such windows, you are guaranteed that there will
 * always be only one unique minimum window in S.
 * 
 */
char* minWindow(char* s, char* t) {
    int f[256];
    memset(f, 0, sizeof(f));
    int t_len = strlen(t);
    bool used[256];
    memset(used, 0, sizeof(used));
    for (int i = 0; i < t_len; ++i) {
         ++f[t[i]];
        used[t[i]] = true;
    }
    int count = 0;
    int result_index = -1;
    int result_max   = INT_MAX;
    int left = 0;
    for (int i = 0; s[i] != '\0'; ++i) 
        if (used[s[i]] == true) {
            --f[s[i]];
            if (f[s[i]] >= 0) {
                ++count;
                if (count == t_len) {
                    while (used[s[left]] == false || f[s[left]] < 0) {
                        ++f[s[left]];
                        ++left;
                    }
                    if (result_max > i - left + 1) {
                        result_max   = i - left + 1;
                        result_index = left;
                    }
                    ++f[s[left]];
                    ++left;
                    --count;
                }
            }
    
        }
    if (result_index == -1)
        return "";
    char* result = (char*)malloc(sizeof(char)*(result_max+1));
    strncpy(result, s + result_index, result_max);
    result[result_max] = '\0';
    return result;
}

