/*
 * [36] Valid Sudoku
 *
 * https://leetcode.com/problems/valid-sudoku/description/
 *
 * algorithms
 * Medium (36.76%)
 * Total Accepted:    138.2K
 * Total Submissions: 375.8K
 * Testcase Example:
 * '[[".","8","7","6","5","4","3","2","1"],["2",".",".",".",".",".",".",".","."],["3",".",".",".",".",".",".",".","."],["4",".",".",".",".",".",".",".","."],["5",".",".",".",".",".",".",".","."],["6",".",".",".",".",".",".",".","."],["7",".",".",".",".",".",".",".","."],["8",".",".",".",".",".",".",".","."],["9",".",".",".",".",".",".",".","."]]'
 *
 * Determine if a Sudoku is valid, according to: Sudoku Puzzles - The Rules.
 *
 * The Sudoku board could be partially filled, where empty cells are filled
 * with the character '.'.
 *
 *
 *
 * A partially filled sudoku which is valid.
 *
 *
 * Note:
 * A valid Sudoku board (partially filled) is not necessarily solvable. Only
 * the filled cells need to be validated.
 *
 */
bool isValidSudoku(char** board, int boardRowSize, int boardColSize) {
    bool row[9][10], col[9][10], grid[9][10];
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 10; ++j) row[i][j] = col[i][j] = grid[i][j] = false;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (board[i][j] != '.') {
                int k = i / 3 * 3 + j / 3;
                int data = board[i][j] - '0';
                if (row[i][data] == true || col[j][data] == true ||
                    grid[k][data] == true)
                    return false;
                row[i][data] = col[j][data] = grid[k][data] = true;
            }
    return true;
}
