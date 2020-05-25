#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRCSPN_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRCSPN_H_

#include <stdio.h>
#include <string.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   size_t strcspn(const char* dest, const char* src);
 *
 * 函数说明：
 *   * 查找 dest 所指向的字符串中，从头开始，不包含 src 中的字符的最大长度
 *
 * 参数要求：
 *   * dest 所指向的字符数组中一定包含 '\0'
 *   * src  所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 返回 dest 所指向的字符串中，从头开始，不包含 src 中的字符的最大长度
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则直接返回
 */

size_t strcspn(const char *dest, const char *src) {
  if (dest == src)
    return 0;

  for (size_t i = 0;; ++i) {
    if (dest[i] == '\0')
      return i;
    if (::strchr(src, dest[i]) != NULL)
      return i;
  }
}

} // namespace liuyunbin

#endif
