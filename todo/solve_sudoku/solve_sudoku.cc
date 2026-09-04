
#include <ctype.h>   // isdigit
#include <errno.h>   // program_invocation_name
#include <getopt.h>  // getopt_long
#include <stdio.h>   // printf
#include <stdlib.h>  // exit

char data[9][9];                   // 用于存储数独
int solution_count = 0;            // 用于表示解的个数
bool output_all_solution = false;  // 用于表示是否输出所有解

void usage(int status) {
    if (status == EXIT_FAILURE) {
        fprintf(stderr, "Try '%s --help or %s -h' for more information.\n",
                program_invocation_name, program_invocation_name);
    } else if (status == EXIT_SUCCESS) {
        printf("使用：\n");
        printf("\t %s [可选项]... [文件名]...\n", program_invocation_name);
        printf("\n");
        printf("说明：\n");
        printf("\t 本程序用于解数独，可从文件或标准输入输入数据\n");
        printf("\t 数据格式为 81 个数字字符 [0, 9]\n");
        printf("\t 本程序将忽略除数字字符以外的其它字符\n");
        printf("\n");
        printf("可选项：\n");
        printf("\t -a，--all  ，输出所有解\n");
        printf("\t -h，--help ，输出帮助\n");
        printf("\t -f，--file ，从文件输入数据\n");
        printf("\n");
        printf("例子：\n");
        printf("\t %s                从标准输入输入数据\n",
               program_invocation_name);
        printf("\t %s -a             从标准输入输入数据，输出所有解\n",
               program_invocation_name);
        printf("\t %s data.txt       从文件输入数据\n",
               program_invocation_name);
        printf("\t %s data.txt -a    从文件输入数据，输出所有解\n",
               program_invocation_name);
        printf("\t %s -f data.txt    从文件输入数据\n",
               program_invocation_name);
        printf("\t %s -f data.txt -a 从文件输入数据，输出所有解\n",
               program_invocation_name);
        printf("\t %s -h             输出帮助\n", program_invocation_name);
        printf("\n");
    }
    exit(status);
}

void input_sudoku(FILE *fp) {
    for (int row = 0; row != 9; ++row)
        for (int col = 0; col != 9; ++col)
            for (;;) {
                int ch = fgetc(fp);
                if (ch == EOF) {
                    printf("数据格式错误\n\n");
                    usage(EXIT_FAILURE);
                }
                if (isdigit(ch)) {
                    data[row][col] = ch;
                    break;
                }
            }
}

void input_from_file(const char *file_name) {
    FILE *fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("无法打开文件：%s\n", file_name);
        exit(EXIT_FAILURE);
    }
    input_sudoku(fp);
    fclose(fp);
}

void input_from_stdin() { input_sudoku(stdin); }

void output_sudoku() {
    for (int row = 0; row != 9; ++row) {
        if (row != 0 && row % 3 == 0) printf("\n");

        for (int col = 0; col != 9; ++col) {
            if (col != 0 && col % 3 == 0) printf("\t");
            printf("%c ", data[row][col]);
        }
        printf("\n");
    }
}

bool check_current_value_is_valid(int row, int col, char ch) {
    for (int i = 0; i != 9; ++i)
        if (data[row][i] == ch || data[i][col] == ch) return false;

    for (int i = 0; i != 3; ++i)
        for (int j = 0; j != 3; ++j)
            if (data[row / 3 * 3 + i][col / 3 * 3 + j] == ch) return false;

    return true;
}

bool check_current_sudoku_is_valid() {
    for (int row = 0; row != 9; ++row)
        for (int col = 0; col != 9; ++col)
            if (data[row][col] != '0') {
                char ch = data[row][col];  // 暂时修改数据
                data[row][col] = '0';
                if (!check_current_value_is_valid(row, col, ch)) {
                    data[row][col] = ch;  // 恢复数据
                    return false;
                }
                data[row][col] = ch;  // 恢复数据
            }
    return true;
}

bool DFS(int row, int col) {
    if (col == 9) {
        ++row;
        col = 0;
    }

    if (row == 9) {
        ++solution_count;
        if (solution_count == 1) printf("\n该数独的解为：\n\n");
        if (output_all_solution)
            printf("\n第 %d 种解法为：\n\n", solution_count);
        output_sudoku();
        return true;
    }

    if (data[row][col] != '0') return DFS(row, col + 1);

    for (char ch = '1'; ch <= '9'; ++ch)
        if (check_current_value_is_valid(row, col, ch)) {
            data[row][col] = ch;
            if (DFS(row, col + 1) && output_all_solution == false) {
                return true;
            }
        }

    data[row][col] = '0';
    return false;
}

void solve_sudoku() {
    printf("\n原数独为（0 表示未填）：\n\n");
    output_sudoku();

    if (!check_current_sudoku_is_valid()) {
        printf("\n原数独不合法\n");
        exit(EXIT_FAILURE);
    }

    DFS(0, 0);
    if (solution_count == 0) printf("\n此数独无解\n");
}

void solve_sudoku(int argc, char *argv[], const char *file_name) {
    if (argc == 0 && file_name == NULL) {
        input_from_stdin();
        solve_sudoku();
    } else {
        if (file_name != NULL) {
            input_from_file(file_name);
            solve_sudoku();
        }
        for (int i = 0; i != argc; ++i) {
            input_from_file(argv[i]);
            solve_sudoku();
        }
    }
}

int main(int argc, char *argv[]) {
    struct option long_options[] = {{"all", no_argument, NULL, 'a'},
                                    {"file", required_argument, NULL, 'f'},
                                    {"help", no_argument, NULL, 'h'},
                                    {NULL, 0, NULL, 0}};
    const char *file_name = NULL;

    for (;;) {
        int c = getopt_long(argc, argv, "af:h", long_options, NULL);
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'a':
                output_all_solution = true;
                break;

            case 'h':
                usage(EXIT_SUCCESS);
                break;

            case 'f':
                file_name = optarg;
                break;

            case '?':
                usage(EXIT_FAILURE);
                break;

            default:
                usage(EXIT_FAILURE);
                break;
        }
    }

    argc -= optind;
    argv += optind;
    solve_sudoku(argc, argv, file_name);
    exit(EXIT_SUCCESS);
}
