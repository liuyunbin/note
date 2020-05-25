#ifndef CPP_STANDARD_LIBRARY_CSTRING_MEMSET_H_
#define CPP_STANDARD_LIBRARY_CSTRING_MEMSET_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   void* memset(void* dest, int ch, size_t count);
 *
 * 函数说明：
 *   * 将 dest 所指向的数组中的前 count 个字符设置为 ch
 *   * dest 将转化为 unsigned char*
 *   * ch   将转化为 unsigned char
 *
 * 参数要求：
 *   * dest 所指向的数组的大小最小为 count
 *
 * 返回说明：
 *   * 返回 dest
 */

void *memset(void *dest, int ch, size_t count) {
  auto new_dest = static_cast<unsigned char *>(dest);
  auto new_ch = static_cast<unsigned char>(ch);
  for (size_t i = 0; i < count; ++i)
    new_dest[i] = new_ch;
  return dest;
}

} // namespace liuyunbin

#endif
