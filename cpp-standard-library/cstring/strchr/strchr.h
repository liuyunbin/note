#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRCHR_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRCHR_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   const char* strchr(const char* str, int ch);
 *         char* strchr(      char* str, int ch);
 *
 * 函数说明：
 *   * 查找 str 所指向的字符串中的第一个 ch 的位置
 *   * ch 将转化为 char 比较
 *   * ch 可以是 '\0'
 *   * str 所指向的字符串中的 '\0' 也会被查找
 *
 * 参数要求：
 *   * src 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回 str 所指向的字符串中的第一个 ch 的位置
 *   * 如果未找到，将返回 NULL
 *
 */

const char *strchr(const char *str, int ch) {
  for (;;) {
    if (*str == static_cast<char>(ch))
      return str;
    if (*str == '\0')
      return NULL;
    ++str;
  }
}

char *strchr(char *str, int ch) {
  return const_cast<char *>(strchr(const_cast<const char *>(str), ch));
}

} // namespace liuyunbin

#endif
