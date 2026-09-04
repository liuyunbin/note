/*
 * [130] Surrounded Regions
 *
 * https://leetcode.com/problems/surrounded-regions/description/
 *
 * algorithms
 * Medium (19.09%)
 * Total Accepted:    93.8K
 * Total Submissions: 490.9K
 * Testcase Example:
 * '[["X","X","X","X"],["X","O","O","X"],["X","X","O","X"],["X","O","X","X"]]'
 *
 *
 * Given a 2D board containing 'X' and 'O' (the letter O), capture all regions
 * surrounded by 'X'.
 *
 * A region is captured by flipping all 'O's into 'X's in that surrounded
 * region.
 *
 *
 *
 * For example,
 *
 * X X X X
 * X O O X
 * X X O X
 * X O X X
 *
 *
 *
 *
 * After running your function, the board should be:
 *
 * X X X X
 * X X X X
 * X X X X
 * X O X X
 *
 *
 */

void function(char** board, int boardRowSize, int boardColSize, int x, int y) {
    if (x < 0 || x >= boardRowSize || y < 0 || y >= boardColSize ||
        board[x][y] != 'O')
        return;
    board[x][y] = '1';
    function(board, boardRowSize, boardColSize, x + 1, y);
    function(board, boardRowSize, boardColSize, x - 1, y);
    function(board, boardRowSize, boardColSize, x, y - 1);
    function(board, boardRowSize, boardColSize, x, y + 1);
}

void solve(char** board, int boardRowSize, int boardColSize) {
    for (int i = 0; i < boardRowSize; ++i) {
        function(board, boardRowSize, boardColSize, i, 0);
        function(board, boardRowSize, boardColSize, i, boardColSize - 1);
    }
    for (int j = 0; j < boardColSize; ++j) {
        function(board, boardRowSize, boardColSize, 0, j);
        function(board, boardRowSize, boardColSize, boardRowSize - 1, j);
    }
    for (int i = 0; i < boardRowSize; ++i)
        for (int j = 0; j < boardColSize; ++j)
            if (board[i][j] == 'O')
                board[i][j] = 'X';
            else if (board[i][j] == '1')
                board[i][j] = 'O';
}
