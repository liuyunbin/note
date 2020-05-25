#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISPUNCT_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISPUNCT_H_

#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int ispunct(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是标点字符，即：
 *     * !\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是标点字符，返回 非零值，否则，返回 0
 */

int ispunct(int ch) {
  if (ch == EOF)
    return 0;

  for (const char *p = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"; *p != '\0'; ++p)
    if (*p == ch)
      return 1;
  return 0;
}

} // namespace liuyunbin

#endif
