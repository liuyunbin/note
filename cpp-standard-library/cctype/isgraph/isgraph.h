#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISGRAPH_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISGRAPH_H_

#include <ctype.h>
#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int isgraph(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是图形字符，即：
 *     * 数字：0123456789
 *     * 小写字母：abcdefghijklmnopqrstuvwxyz
 *     * 大写字母：ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *     * 标点字符：!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是图形字符，返回 非零值，否则，返回 0
 */

int isgraph(int ch) {
  if (ch == EOF)
    return 0;

  if (::isalnum(ch) != 0)
    return 1;
  return ::ispunct(ch);
}

} // namespace liuyunbin

#endif
