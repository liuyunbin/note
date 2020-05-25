#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRTOK_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRTOK_H_

#include <stdio.h>
#include <string.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   char* strtok(char* str, const char* delim);
 *
 * 函数说明：
 *   * 使用 delim 中的字符，对 str 字符数组进行切割
 *
 * 参数要求：
 *   * str   可能是 NULL
 *   * str   所指向的字符数组中一定包含 '\0'
 *   * delim 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回首位置
 *   * 否则，返回 NULL
 *
 * 特别说明：
 *   * 此函数，线程不安全
 *
 */

char *strtok(char *str, const char *delim) {
  static char *p = NULL;

  if (str != NULL)
    p = str;
  if (p == NULL)
    return NULL;
  p = p + ::strspn(p, delim);
  if (*p == '\0') {
    p = NULL;
    return NULL;
  }
  char *return_str = p;
  p = p + ::strcspn(p, delim);
  if (*p == '\0')
    p = NULL;
  else
    *p++ = '\0';
  return return_str;
}

} // namespace liuyunbin

#endif
