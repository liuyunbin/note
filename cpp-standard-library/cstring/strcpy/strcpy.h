#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRCPY_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRCPY_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   char* strcpy(char* dest, const char* src);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），拷贝到 dest 所指向的字符数组中
 *
 * 参数要求：
 *   * src 为指向以 '\0' 结尾的的字符串的指针
 *   * dest 所指向的字符数组的长度最小为：strlen(src) + 1
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终将包含 '\0'
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则无需复制
 */

char *strcpy(char *dest, const char *src) {
  if (dest == src)
    return dest;

  for (size_t i = 0;; ++i) {
    dest[i] = src[i];
    if (dest[i] == '\0')
      break;
  }

  return dest;
}

} // namespace liuyunbin

#endif
