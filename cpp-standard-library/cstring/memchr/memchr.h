#ifndef CPP_STANDARD_LIBRARY_CSTRING_MEMCHR_H_
#define CPP_STANDARD_LIBRARY_CSTRING_MEMCHR_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   const void* memchr(const void* ptr, int ch, size_t count);
 *         void* memchr(      void* ptr, int ch, size_t count);
 *
 * 函数说明：
 *   * 查找 ptr 所指向的数组中的 ch 第一次出现的位置
 *   * ptr 将转化为 unsigned char*
 *   * ch  将转化为 unsigned char
 *
 * 返回说明：
 *   * 如果找到，返回 ch 第一次出现的位置
 *   * 否则，返回 NULL
 *
 */

const void *memchr(const void *ptr, int ch, size_t count) {
  auto new_ptr = static_cast<unsigned char *>(const_cast<void *>(ptr));
  auto new_ch = static_cast<unsigned char>(ch);
  for (size_t i = 0; i < count; ++i)
    if (new_ptr[i] == new_ch)
      return static_cast<void *>(new_ptr + i);
  return NULL;
}

void *memchr(void *ptr, int ch, size_t count) {
  return const_cast<void *>(memchr(const_cast<const void *>(ptr), ch, count));
}

} // namespace liuyunbin

#endif
