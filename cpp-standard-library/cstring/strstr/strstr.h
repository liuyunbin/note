#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRSTR_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRSTR_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   const char* strstr(const char* str, const char* target);
 *         char* strstr(      char* str, const char* target);
 *
 * 函数说明：
 *   * 查找 str 所指向的字符串中和 target 相同的子序列的首位置
 *
 * 参数要求：
 *   * str    所指向的字符数组中一定包含 '\0'
 *   * target 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回首位置
 *   * 否则，返回 NULL
 *
 * 优化：
 *   * 如果，str 和 target 的值相同，则直接返回
 */

const char *strstr(const char *str, const char *target) {
  if (str == target)
    return str;

  for (;;) {
    auto temp = str;
    auto it = target;
    for (;;) {
      if (*it == '\0')
        return str;
      if (*temp == '\0')
        return NULL;
      if (*it != *temp)
        break;
      ++it;
      ++temp;
    }
    ++str;
  }
}

char *strstr(char *str, const char *target) {
  return const_cast<char *>(strstr(const_cast<const char *>(str), target));
}

} // namespace liuyunbin

#endif
