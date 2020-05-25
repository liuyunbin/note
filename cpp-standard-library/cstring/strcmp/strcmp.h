#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRCMP_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRCMP_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   int strcmp(const char* lhs, const char* rhs);
 *
 * 函数说明：
 *   比较 lhs 和 rhs 所指向字符串的大小，将转化为 unsigned char 比较
 *
 * 参数要求：
 *   * lhs 所指向的字符数组中一定包含 '\0'
 *   * rhs 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果 lhs >  rhs，返回 1
 *   * 如果 lhs == rhs，返回 0
 *   * 如果 lhs <  rhs，返回 -1
 *
 * 优化：
 *   * 如果，lhs 和 rhs 的值相同，则无需比较，直接相同
 */

int strcmp(const char *lhs, const char *rhs) {
  if (lhs == rhs)
    return 0;

  for (size_t i = 0;; ++i) {
    unsigned char lhs_char = lhs[i];
    unsigned char rhs_char = rhs[i];

    if (lhs_char != rhs_char)
      return lhs_char < rhs_char ? -1 : 1;

    if (lhs[i] == '\0')
      return 0;
  }
}

} // namespace liuyunbin

#endif
