/*
 * [52] N-Queens II
 *
 * https://leetcode.com/problems/n-queens-ii/description/
 *
 * algorithms
 * Hard (46.05%)
 * Total Accepted:    70.4K
 * Total Submissions: 152.8K
 * Testcase Example:  '1'
 *
 * Follow up for N-Queens problem.
 * 
 * Now, instead outputting board configurations, return the total number of
 * distinct solutions.
 * 
 * 
 */

void function(int n, int* temp, int temp_index, int* result) {
    if (temp_index == n) {
        ++*result;
        return ;
    }
    for (int i = 0; i < n; ++i) {
        int j;
        for (j = 0; j < temp_index; ++j)
            if (temp[j] == i || temp_index - j == abs(i - temp[j]))
                break;
        if (j == temp_index) {
            temp[temp_index] = i;
            function(n, temp, temp_index + 1, result);
        }
    }
}

int totalNQueens(int n) {
    if (n <= 0)
        return 0;
    int result = 0;
    int*  temp = (int*)malloc(sizeof(int)*n);
    function(n, temp, 0, &result);
    free(temp);
    return result;
}
