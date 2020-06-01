
#include "bc.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <stack>

#include <readline/history.h>
#include <readline/readline.h>

char *data = NULL;           // 存储输入字符串
std::stack<char> stack_char; // 存储运算符
std::stack<long> stack_long; // 存储运算数

void input() {
  data = readline("> ");

  if (data == NULL) // 读入 EOF
    exit(EXIT_SUCCESS);

  if (data[0] != '\0')
    add_history(data);

  // 移除多余的空格
  int k = 0;
  for (size_t i = 0; data[i] != '\0'; ++i)
    if (data[i] != ' ')
      data[k++] = data[i];
  if (k > 0 && data[k - 1] == '=')
    data[k - 1] = '\0';
  else
    data[k] = '\0';
}

bool count_one_char(char ch) {
  if (stack_long.size() < 2)
    return false;

  long rhs = stack_long.top();
  stack_long.pop();
  long lhs = stack_long.top();
  stack_long.pop();
  long data;
  switch (ch) {
  case '+':
    data = lhs + rhs;
    break;
  case '-':
    data = lhs - rhs;
    break;
  case '*':
    data = lhs * rhs;
    break;
  case '/':
    if (rhs == 0)
      return false;
    data = lhs / rhs;
    break;
  default:
    return false;
  }
  stack_long.push(data);
  return true;
}

bool solve() {
  char *st = data;
  if (*st == '+') { // 解决开头类似 +123 的情况
    ++st;
  } else if (*st == '-') { // 解决开头类似 -123 的情况
    stack_long.push(0);
    stack_char.push(*st++);
  }

  while (*st != '\0') {
    if (isdigit(*st)) { // 当前是数字
      long data = strtol(st, &st, 10);
      stack_long.push(data);
      continue;
    }

    if (*st == '(') {
      stack_char.push(*st++);
      if (*st == '+') { // 解决 类似 (+123) 的问题
        ++st;
      } else if (*st == '-') { // 解决 类似 (-123) 的问题
        stack_long.push(0);
        stack_char.push(*st++);
      }
      continue;
    }
    if (*st == ')') {
      for (;;) {
        if (stack_char.empty())
          return false;
        char ch = stack_char.top();
        stack_char.pop();
        if (ch == '(')
          break;
        if (count_one_char(ch) == false)
          return false;
      }
      ++st;
      continue;
    }
    if (*st != '+' && *st != '-' && *st != '*' && *st != '/')
      return false;
    for (;;) {
      if (stack_char.empty() || stack_char.top() == '(') {
        stack_char.push(*st++);
        break;
      }
      char ch = stack_char.top();
      if ((ch == '+' || ch == '-') && (*st == '*' || *st == '/')) {
        stack_char.push(*st++);
        break;
      }
      if (count_one_char(ch) == false)
        return false;
      stack_char.pop();
    }
  }
  for (;;) {
    if (stack_char.empty())
      break;
    char ch = stack_char.top();
    if (count_one_char(ch) == false)
      return false;
    stack_char.pop();
  }
  if (stack_long.size() != 1)
    return false;
  std::cout << stack_long.top() << std::endl;
  return true;
}

void output() {
  if (data[0] == '\0')
    return;

  if (solve() == false)
    std::cout << "输入格式错误" << std::endl;

  if (data != NULL) {
    free(data);
    data = NULL;
  }
  // 清空栈，避免影响下次计算
  while (!stack_char.empty())
    stack_char.pop();
  while (!stack_long.empty())
    stack_long.pop();
}

