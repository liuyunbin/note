#ifndef CPP_STANDARD_LIBRARY_CSTRING_STRPBRK_H_
#define CPP_STANDARD_LIBRARY_CSTRING_STRPBRK_H_

#include <stdio.h>
#include <string.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   const char* strpbrk(const char* dest, const char* breakset);
 *         char* strpbrk(      char* dest, const char* breakset);
 *
 * 函数说明：
 *   * 查找 dest 所指向的字符串中，第一个在 breakset 中出现的字符的位置
 *
 * 参数要求：
 *   * dest     所指向的字符数组中一定包含 '\0'
 *   * breakset 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回该字符的位置
 *   * 否则，返回 NULL
 *
 * 优化：
 *   * 如果，dest 和 breakset 的值相同，则直接返回
 */

const char *strpbrk(const char *dest, const char *breakset) {
  if (dest == breakset)
    return dest;

  for (size_t i = 0; dest[i] != '\0'; ++i)
    if (::strchr(breakset, dest[i]) != NULL)
      return dest + i;
  return NULL;
}

char *strpbrk(char *dest, const char *breakset) {
  return const_cast<char *>(strpbrk(const_cast<const char *>(dest), breakset));
}

} // namespace liuyunbin

#endif
