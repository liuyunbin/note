#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISLOWER_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISLOWER_H_

#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int islower(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是小写字母，即：
 *     * abcdefghijklmnopqrstuvwxyz
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是小写字母，返回 非零值，否则，返回 0
 */

int islower(int ch) {
  if (ch == EOF)
    return 0;

  for (const char *p = "abcdefghijklmnopqrstuvwxyz"; *p != '\0'; ++p)
    if (*p == ch)
      return 1;
  return 0;
}

} // namespace liuyunbin

#endif
