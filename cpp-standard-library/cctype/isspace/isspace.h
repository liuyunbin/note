#ifndef CPP_STANDARD_LIBRARY_CCTYPE_ISSPACE_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_ISSPACE_H_

#include <stdio.h> // EOF

namespace liuyunbin {

/*
 * 函数原型：
 *   int isspace(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是空白间隔字符，即：
 *     * 空格（' '）
 *     * 换页（'\f'）
 *     * 换行（'\n'）
 *     * 回车（'\r'）
 *     * 水平制表符（'\t'）
 *     * 垂直制表符（'\v')
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是空白间隔字符，返回 非零值，否则，返回 0
 */

int isspace(int ch) {
  if (ch == EOF)
    return 0;

  for (const char *p = " \f\n\r\t\v"; *p != '\0'; ++p)
    if (*p == ch)
      return 1;
  return 0;
}

} // namespace liuyunbin

#endif
