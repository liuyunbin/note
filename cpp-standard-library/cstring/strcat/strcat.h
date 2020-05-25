#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRCAT_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRCAT_H_

#include <stdio.h>
#include <string.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   char* strcat(char* dest, const char* src);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），添加到 dest 所指向的字符串之后
 *
 * 参数要求：
 *   * dest 为指向以 '\0' 结尾的的字符串的指针
 *   * src  为指向以 '\0' 结尾的的字符串的指针
 *   * dest 所指向的字符数组的长度最小为：strlen(dest) + strlen(src) + 1
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终将包含 '\0'
 */

char *strcat(char *dest, const char *src) {
  size_t dest_size = ::strlen(dest);
  for (size_t i = 0;; ++i) {
    dest[dest_size + i] = src[i];
    if (dest[dest_size + i] == '\0')
      break;
  }

  return dest;
}

} // namespace liuyunbin

#endif
