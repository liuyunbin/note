/*
 * [79] Word Search
 *
 * https://leetcode.com/problems/word-search/description/
 *
 * algorithms
 * Medium (27.63%)
 * Total Accepted:    156.7K
 * Total Submissions: 566.9K
 * Testcase Example:
 * '[["A","B","C","E"],["S","F","C","S"],["A","D","E","E"]]\n"ABCCED"'
 *
 *
 * Given a 2D board and a word, find if the word exists in the grid.
 *
 *
 * The word can be constructed from letters of sequentially adjacent cell,
 * where "adjacent" cells are those horizontally or vertically neighboring. The
 * same letter cell may not be used more than once.
 *
 *
 *
 * For example,
 * Given board =
 *
 * [
 * ⁠ ['A','B','C','E'],
 * ⁠ ['S','F','C','S'],
 * ⁠ ['A','D','E','E']
 * ]
 *
 *
 * word = "ABCCED", -> returns true,
 * word = "SEE", -> returns true,
 * word = "ABCB", -> returns false.
 *
 */

bool function(char** board, int boardRowSize, int boardColSize, int x, int y,
              bool** used, char* word) {
    if (*word == '\0') return true;
    if (x < 0 || x >= boardRowSize || y < 0 || y >= boardColSize ||
        used[x][y] == true || *word != board[x][y])
        return false;
    used[x][y] = true;
    if (function(board, boardRowSize, boardColSize, x + 1, y, used, word + 1) ==
        true)
        return true;
    if (function(board, boardRowSize, boardColSize, x - 1, y, used, word + 1) ==
        true)
        return true;
    if (function(board, boardRowSize, boardColSize, x, y + 1, used, word + 1) ==
        true)
        return true;
    if (function(board, boardRowSize, boardColSize, x, y - 1, used, word + 1) ==
        true)
        return true;
    used[x][y] = false;
    return false;
}

bool exist(char** board, int boardRowSize, int boardColSize, char* word) {
    if (boardRowSize <= 0 || boardColSize <= 0) return false;
    bool** used = (bool**)malloc(sizeof(bool*) * boardRowSize);
    for (int i = 0; i < boardRowSize; ++i)
        used[i] = (bool*)malloc(sizeof(bool) * boardColSize);
    for (int i = 0; i < boardRowSize; ++i)
        for (int j = 0; j < boardColSize; ++j) used[i][j] = false;
    for (int i = 0; i < boardRowSize; ++i)
        for (int j = 0; j < boardColSize; ++j)
            if (function(board, boardRowSize, boardColSize, i, j, used, word) ==
                true)
                return true;
    return false;
}
