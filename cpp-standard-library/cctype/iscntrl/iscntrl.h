#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISCNTRL_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISCNTRL_H_

#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int iscntrl(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是控制字符，即：
 *     * 0x00~0x1F
 *     * 0x7F
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是控制字符，返回 非零值，否则，返回 0
 */

int iscntrl(int ch) {
  if (ch == EOF)
    return 0;

  return (0x00 <= ch && ch <= 0x1F) || ch == 0x7F ? 1 : 0;
}

} // namespace liuyunbin

#endif
