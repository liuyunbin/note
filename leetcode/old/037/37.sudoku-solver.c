/*
 * [37] Sudoku Solver
 *
 * https://leetcode.com/problems/sudoku-solver/description/
 *
 * algorithms
 * Hard (31.29%)
 * Total Accepted:    85.1K
 * Total Submissions: 271.7K
 * Testcase Example:  '[[".",".","9","7","4","8",".",".","."],["7",".",".",".",".",".",".",".","."],[".","2",".","1",".","9",".",".","."],[".",".","7",".",".",".","2","4","."],[".","6","4",".","1",".","5","9","."],[".","9","8",".",".",".","3",".","."],[".",".",".","8",".","3",".","2","."],[".",".",".",".",".",".",".",".","6"],[".",".",".","2","7","5","9",".","."]]'
 *
 * Write a program to solve a Sudoku puzzle by filling the empty cells.
 * 
 * Empty cells are indicated by the character '.'.
 * 
 * You may assume that there will be only one unique solution.
 * 
 * 
 * 
 * A sudoku puzzle...
 * 
 * 
 * 
 * 
 * ...and its solution numbers marked in red.
 * 
 */
bool backtrack(char** board, int x, int y, bool row[][9], bool col[][9], bool grid[][9]) {
    if (y == 9) {
        y = 0;
        ++x;
    }
    if (x == 9)
        return true;
    if (board[x][y] != '.')
        return backtrack(board, x, y + 1, row, col, grid);
    int k = x / 3 * 3 + y / 3;
    for (int i = 0; i < 9; ++i) {
        if (row[x][i] == true || col[y][i] == true || grid[k][i] == true)
            continue;
        board[x][y] = '1' + i;
        row[x][i] = col[y][i] = grid[k][i] = true;
        if (backtrack(board, x, y + 1, row, col, grid) == true)
            return true;
        row[x][i] = col[y][i] = grid[k][i] = false;
    }
    board[x][y] = '.';
    return false;
}

void solveSudoku(char** board, int boardRowSize, int boardColSize) {
    bool row[9][9], col[9][9], grid[9][9];
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            row[i][j] = col[i][j] = grid[i][j] = false;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (board[i][j] != '.') {
                int num = board[i][j] - '1';
                int k   = i / 3 * 3 + j / 3;
                row[i][num] = col[j][num] = grid[k][num] = true;
            }
    backtrack(board, 0, 0, row, col, grid);
}
