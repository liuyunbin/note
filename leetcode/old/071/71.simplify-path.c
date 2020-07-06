/*
 * [71] Simplify Path
 *
 * https://leetcode.com/problems/simplify-path/description/
 *
 * algorithms
 * Medium (25.97%)
 * Total Accepted:    103.6K
 * Total Submissions: 398.8K
 * Testcase Example:  '"/"'
 *
 * Given an absolute path for a file (Unix-style), simplify it.
 * 
 * For example,
 * path = "/home/", => "/home"
 * path = "/a/./b/../../c/", => "/c"
 * 
 * 
 * click to show corner cases.
 * 
 * Corner Cases:
 * 
 * 
 * 
 * Did you consider the case where path = "/../"?
 * In this case, you should return "/".
 * Another corner case is the path might contain multiple slashes '/' together,
 * such as "/home//foo/".
 * In this case, you should ignore redundant slashes and return "/home/foo".
 * 
 * 
 */
char* simplifyPath(char* path) {
    char* result = (char*)malloc(sizeof(char)*(strlen(path)+1));
    int   result_index = 0;
    for (char* p = strtok(path, "/"); p != NULL; p = strtok(NULL, "/")) {
        if (strcmp(p, ".") == 0)
            continue;
        if (strcmp(p, "..") == 0) {
            if (result_index > 0)
                do
                    --result_index;
                while (result[result_index] != '/');
            continue;
        }
        result[result_index++] = '/';
        for (int i = 0; p[i] != '\0'; ++i)
            result[result_index++] = p[i];
    }
    if (result_index == 0)
        result[result_index++] = '/';
    result[result_index] = '\0';
    return result;
}
