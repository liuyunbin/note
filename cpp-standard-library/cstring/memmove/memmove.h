#ifndef CPP_STANDARD_LIBRARY_CSTRING_MEMMOVE_H_
#define CPP_STANDARD_LIBRARY_CSTRING_MEMMOVE_H_

#include <stdio.h>
#include <string.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   void* memmove(void* dest, const void* src, std::size_t count);
 *
 * 函数说明：
 *   * 将 src 指向的数组复制到 dest 所指向的数组，复制 count 个字符
 *   * dest 将转化为 unsigned char*
 *   * src  将转化为 unsigned char*
 *   * 本函数可以处理数组重叠的情况
 *
 * 参数要求：
 *   * dest 所指向的数组的大小最小为 count
 *   * src  所指向的数组的大小最小为 count
 *
 * 返回说明：
 *   * 返回 dest
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则直接返回
 */

void *memmove(void *dest, const void *src, size_t count) {
  if (dest == src)
    return dest;

  if (dest < src)
    return ::memcpy(dest, src, count);

  auto new_dest = static_cast<unsigned char *>(dest);
  auto new_src = static_cast<const unsigned char *>(src);

  for (size_t i = 0; i < count; ++i)
    new_dest[count - i - 1] = new_src[count - i - 1];
  return dest;
}

} // namespace liuyunbin

#endif
