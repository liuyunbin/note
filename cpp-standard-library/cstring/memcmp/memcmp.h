#ifndef CPP_STANDARD_LIBRARY_CSTRING_MEMCMP_H_
#define CPP_STANDARD_LIBRARY_CSTRING_MEMCMP_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   int memcmp(const void* lhs, const void* rhs, size_t count);
 *
 * 函数说明：
 *   * 比较 lhs 和 rhs 所指向数组的大小，最多比较 count 个字符，
 *   * lhs 将转化为 unsigned char*
 *   * rhs 将转化为 unsigned char*
 *
 * 返回说明：
 *   * 如果 lhs >  rhs，返回 1
 *   * 如果 lhs == rhs，返回 0
 *   * 如果 lhs <  rhs，返回 -1
 *
 * 优化：
 *   * 如果，lhs 和 rhs 的值相同，则直接返回
 */

int memcmp(const void *lhs, const void *rhs, size_t count) {
  if (lhs == rhs)
    return 0;

  auto new_lhs = static_cast<const unsigned char *>(lhs);
  auto new_rhs = static_cast<const unsigned char *>(rhs);

  for (size_t i = 0; i < count; ++i)
    if (new_lhs[i] != new_rhs[i])
      return new_lhs[i] < new_rhs[i] ? -1 : 1;
  return 0;
}

} // namespace liuyunbin

#endif
