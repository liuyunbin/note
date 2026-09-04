
#include "sudoku.h"

#include <ctype.h>

const char *test_data =
    "030000001"
    "609003540"
    "048510700"
    "486357020"
    "000168000"
    "300402000"
    "090020310"
    "023000870"
    "000000000";

bool check_current_value_is_valid(char data[9][9], int row, int col, char ch) {
    for (int i = 0; i != 9; ++i)
        if (data[row][i] == ch || data[i][col] == ch) return false;

    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 3; ++j)
            if (data[row / 3 * 3 + i][col / 3 * 3 + j] == ch) return false;
    return true;
}

bool init_sudoku_is_valid(char data[9][9]) {
    for (int row = 0; row != 9; ++row)
        for (int col = 0; col != 9; ++col) {
            if (!isdigit(data[row][col])) {
                return false;
            }
            if (data[row][col] != '0') {
                char ch = data[row][col];  // 暂时修改数据
                data[row][col] = '0';
                if (!check_current_value_is_valid(data, row, col, ch)) {
                    data[row][col] = ch;  // 恢复数据
                    return false;
                }
                data[row][col] = ch;  // 恢复数据
            }
        }
    return true;
}

bool DFS(char data[9][9], int row, int col) {
    if (col == 9) {
        ++row;
        col = 0;
    }
    if (row == 9) {
        return true;
    }
    if (data[row][col] != '0') return DFS(data, row, col + 1);
    for (char ch = '1'; ch <= '9'; ++ch) {
        if (check_current_value_is_valid(data, row, col, ch)) {
            data[row][col] = ch;
            if (DFS(data, row, col + 1) == true) return true;
        }
    }
    data[row][col] = '0';
    return false;
}

bool solve_sudoku(char *str) {
    auto data = (char(*)[9])str;

    return init_sudoku_is_valid(data) && DFS(data, 0, 0);
}
