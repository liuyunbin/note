#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISALNUM_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISALNUM_H_

#include <ctype.h>
#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int isalnum(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是数字或字母，即：
 *     * 小写字母：abcdefghijklmnopqrstuvwxyz
 *     * 大写字母：ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *     * 数字：0123456789
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   如果 ch 是数字或字母，返回 非零值，否则，返回 0
 */

int isalnum(int ch) {
  if (ch == EOF)
    return 0;

  if (::isalpha(ch) != 0)
    return 1;
  return ::isdigit(ch);
}

} // namespace liuyunbin

#endif
