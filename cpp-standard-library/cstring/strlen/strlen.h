#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRLEN_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRLEN_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   size_t strlen(const char* str);
 *
 * 函数说明：
 *   * 求 str 所指向字符串的长度
 *
 * 参数要求：
 *   * str 为指向以 '\0' 结尾的的字符串的指针
 *
 * 返回说明：
 *   * 返回 src 所指向的字符串（不包括 '\0'）的长度
 */

size_t strlen(const char *str) {
  for (size_t i = 0;; ++i)
    if (str[i] == '\0')
      return i;
}

} // namespace liuyunbin

#endif
