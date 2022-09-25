/*
 * [93] Restore IP Addresses
 *
 * https://leetcode.com/problems/restore-ip-addresses/description/
 *
 * algorithms
 * Medium (27.99%)
 * Total Accepted:    96.2K
 * Total Submissions: 343.5K
 * Testcase Example:  '"0000"'
 *
 * Given a string containing only digits, restore it by returning all possible
 * valid IP address combinations.
 *
 *
 * For example:
 * Given "25525511135",
 *
 *
 * return ["255.255.11.135", "255.255.111.35"]. (Order does not matter)
 *
 */
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
#define MAX 10000
void function(const char* s, int level, char* temp, int temp_index,
              char** result, int* returnSize) {
    if (*s == '\0') {
        if (level != 4) return;
        temp[--temp_index] = '\0';
        result[*returnSize] = (char*)malloc(sizeof(char) * (temp_index + 1));
        strcpy(result[(*returnSize)++], temp);
        return;
    }
    if (level == 4) return;
    int count = 0;
    for (int i = 0; s[i] != '\0'; ++i) {
        count = count * 10 + s[i] - '0';
        if (count > 255) break;
        temp[temp_index++] = s[i];
        temp[temp_index] = '.';
        function(s + i + 1, level + 1, temp, temp_index + 1, result,
                 returnSize);
        if (count == 0) break;
    }
}

char** restoreIpAddresses(char* s, int* returnSize) {
    char** result = (char**)malloc(sizeof(char*) * MAX);
    *returnSize = 0;
    char* temp = (char*)malloc(sizeof(char) * (strlen(s) + 4));
    function(s, 0, temp, 0, result, returnSize);
    free(temp);
    return result;
}
