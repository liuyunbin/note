
#include <ctype.h>   // isdigit
#include <stdio.h>   // printf
#include <stdlib.h>  // exit

char data[9][9];                   // 用于存储数独
int solution_count = 0;            // 用于表示解的个数
bool output_all_solution = false;  // 用于表示是否输出所有解

void init_sudoku(int argc, char *argv[]);

void input_sudoku(FILE *fp);
void input_from_file(const char *pathname);
void input_from_stdin();

void output_help(int argc, char *argv[]);
void output_sudoku();

bool check_current_value_is_valid(int row, int col, char ch);
bool check_current_sudoku_is_valid();

bool DFS(int row, int col);

void solve_sudoku();

int main(int argc, char *argv[]) {
  init_sudoku(argc, argv);
  solve_sudoku();
  return 0;
}

void input_sudoku(FILE *fp) {
  for (int row = 0; row != 9; ++row) {
    for (int col = 0; col != 9; ++col) {
      for (;;) {
        int ch = fgetc(fp);
        if (ch == EOF) {
          printf("数据格式错误\n");
          exit(EXIT_FAILURE);
        }
        if (isdigit(ch)) {
          data[row][col] = ch;
          break;
        }
      }
    }
  }
}

void input_from_file(const char *pathname) {
  FILE *fp = fopen(pathname, "r");
  if (fp == NULL) {
    printf("无法打开文件：%s\n", pathname);
    exit(EXIT_FAILURE);
  }
  input_sudoku(fp);
  fclose(fp);
}

void input_from_stdin() { input_sudoku(stdin); }

void init_sudoku(int argc, char *argv[]) {
  char *file_name = NULL;
  for (int i = 1; i < argc; ++i) {
    if (argv[i][0] != '-') {
      file_name = argv[i];
    } else {
      for (int j = 1; argv[i][j] != '\0'; ++j) {
        switch (argv[i][j]) {
          case 'h':
            output_help(argc, argv);
            exit(EXIT_SUCCESS);
          case 'a':
            output_all_solution = true;
            break;
          default:
            printf("\n参数 %s 非法\n", argv[i]);
            printf("\n使用 %s -h 获取帮助信息\n", argv[0]);
            exit(EXIT_FAILURE);
        }
      }
    }
  }
  if (file_name != NULL) {
    input_from_file(file_name);
  } else {
    input_from_stdin();
  }
}

void output_help(int argc, char *argv[]) {
  printf("使用：\n");
  printf("\t %s [可选项] [文件名]\n", argv[0]);
  printf("\n");
  printf("说明：\n");
  printf("\t 本程序用于解数独，可从文件或标准输入输入数据\n");
  printf("\t 数据格式为 81 个数字字符 [0, 9]\n");
  printf("\t 本程序将忽略除数字字符以外的其它字符\n");
  printf("\n");
  printf("可选项：\n");
  printf("\t -a ，输出所有解\n");
  printf("\t -h ，输出帮助\n");
  printf("\n");
  printf("例子：\n");
  printf("\t %s             从标准输入输入数据，只输出一个解\n", argv[0]);
  printf("\t %s -a          从标准输入输入数据，输出所有解\n", argv[0]);
  printf("\t %s data.txt    从文件输入数据，只输出一个解\n", argv[0]);
  printf("\t %s data.txt -a 从文件输入数据，输出所有解\n", argv[0]);
  printf("\t %s -h          输出帮助\n", argv[0]);
  printf("\n");
}

void output_sudoku() {
  for (int row = 0; row != 9; ++row) {
    if (row != 0 && row % 3 == 0) {
      printf("\n");
    }
    for (int col = 0; col != 9; ++col) {
      if (col != 0 && col % 3 == 0) {
        printf("\t");
      }
      printf("%c ", data[row][col]);
    }
    printf("\n");
  }
}

bool check_current_value_is_valid(int row, int col, char ch) {
  for (int i = 0; i != 9; ++i) {
    if (data[row][i] == ch || data[i][col] == ch) {
      return false;
    }
  }
  for (int i = 0; i != 3; ++i) {
    for (int j = 0; j != 3; ++j) {
      if (data[row / 3 * 3 + i][col / 3 * 3 + j] == ch) {
        return false;
      }
    }
  }
  return true;
}

bool check_current_sudoku_is_valid() {
  for (int row = 0; row != 9; ++row) {
    for (int col = 0; col != 9; ++col) {
      if (data[row][col] != '0') {
        char ch = data[row][col];  // 暂时修改数据
        data[row][col] = '0';
        if (!check_current_value_is_valid(row, col, ch)) {
          data[row][col] = ch;  // 恢复数据
          return false;
        }
        data[row][col] = ch;  // 恢复数据
      }
    }
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
    if (solution_count == 1) {
      printf("\n该数独的解为：\n\n");
    }
    if (output_all_solution) {
      printf("\n第 %d 种解法为：\n\n", solution_count);
    }
    output_sudoku();
    return true;
  }
  if (data[row][col] != '0') {
    return DFS(row, col + 1);
  }
  for (char ch = '1'; ch <= '9'; ++ch) {
    if (check_current_value_is_valid(row, col, ch)) {
      data[row][col] = ch;
      if (DFS(row, col + 1) && output_all_solution == false) {
        return true;
      }
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
  if (solution_count == 0) {
    printf("\n此数独无解\n");
  }
}
