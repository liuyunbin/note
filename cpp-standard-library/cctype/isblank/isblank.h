#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISBLANK_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISBLANK_H_

#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int isblank(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是空格符，即：
 *     * 空格（' '）
 *     * 水平制表符（'\t'）
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是空格符，返回 非零值，否则，返回 0
 */

int isblank(int ch) {
  if (ch == EOF)
    return 0;

  return ch == ' ' || ch == '\t' ? 1 : 0;
}

} // namespace liuyunbin

#endif
