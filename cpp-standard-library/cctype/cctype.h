#ifndef CPP_STANDARD_LIBRARY_CCTYPE_H_
#define CPP_STANDARD_LIBRARY_CCTYPE_H_

#include <ctype.h>
#include <stdio.h>  // EOF

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
  if (ch == EOF) return 0;

  if (::isalpha(ch) != 0) return 1;
  return ::isdigit(ch);
}

/*
 * 函数原型：
 *   int isalpha(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是字母，即：
 *     * 小写字母：abcdefghijklmnopqrstuvwxyz
 *     * 大写字母：ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是字母，返回 非零值，否则，返回 0
 */

int isalpha(int ch) {
  if (ch == EOF) return 0;

  if (::islower(ch) != 0) return 1;
  return ::isupper(ch);
}

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
  if (ch == EOF) return 0;

  return ch == ' ' || ch == '\t' ? 1 : 0;
}

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
  if (ch == EOF) return 0;

  return (0x00 <= ch && ch <= 0x1F) || ch == 0x7F ? 1 : 0;
}

/*
 * 函数原型：
 *   int isdigit(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是数字字符，即：
 *     * 0123456789
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是数字字符，返回 非零值，否则，返回 0
 */

int isdigit(int ch) {
  if (ch == EOF) return 0;

  for (const char *p = "0123456789"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

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
  if (ch == EOF) return 0;

  if (::isalnum(ch) != 0) return 1;
  return ::ispunct(ch);
}

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
  if (ch == EOF) return 0;

  for (const char *p = "abcdefghijklmnopqrstuvwxyz"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

/*
 * 函数原型：
 *   int isprint(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是可打印字符，即：
 *     * 数字：0123456789
 *     * 小写字母：abcdefghijklmnopqrstuvwxyz
 *     * 大写字母：ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *     * 标点字符：!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~
 *     * 空格（' '）
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是可打印字符，返回 非零值，否则，返回 0
 */

int isprint(int ch) {
  if (ch == EOF) return 0;

  if (::isgraph(ch) != 0) return 1;
  return ch == ' ' ? 1 : 0;
}

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
  if (ch == EOF) return 0;

  for (const char *p = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

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
  if (ch == EOF) return 0;

  for (const char *p = " \f\n\r\t\v"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

/*
 * 函数原型：
 *   int isupper(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是大写字母，即：
 *     * ABCDEFGHIJKLMNOPQRSTUVWXYZ
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是大写字母，返回 非零值，否则，返回 0
 */

int isupper(int ch) {
  if (ch == EOF) return 0;

  for (const char *p = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

/*
 * 函数原型：
 *   int isxdigit(int ch);
 *
 * 函数说明：
 *   * 检测 ch 是否是十六进制数字字符，即：
 *     * 0123456789ABCDEFabcdef
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是十六进制数字字符，返回 非零值，否则，返回 0
 */

int isxdigit(int ch) {
  if (ch == EOF) return 0;

  for (const char *p = "0123456789abcdefABCDEF"; *p != '\0'; ++p)
    if (*p == ch) return 1;
  return 0;
}

/*
 * 函数原型：
 *   int tolower(int ch);
 *
 * 函数说明：
 *   * 将大写字母转换为对应的小写字母
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是大写字母，返回其对应的小写字母
 *   * 否则，返回原值
 */

int tolower(int ch) {
  if (ch == EOF) return ch;

  const char *p_lower = "abcdefghijklmnopqrstuvwxyz";
  const char *p_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; p_upper[i] != '\0'; ++i)
    if (p_upper[i] == ch) return p_lower[i];
  return ch;
}

/*
 * 函数原型：
 *   int toupper(int ch);
 *
 * 函数说明：
 *   * 将小写字母转换为对应的大写字母
 *
 * 参数说明：
 *   * 参数 ch 必须是 EOF 或 可以用 unsigned char 表示，否则，是未定义的行为
 *
 * 返回说明：
 *   * 如果 ch 是小写字母，返回其对应的大写字母
 *   * 否则，返回原值
 */

int toupper(int ch) {
  if (ch == EOF) return ch;

  const char *p_lower = "abcdefghijklmnopqrstuvwxyz";
  const char *p_upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; p_lower[i] != '\0'; ++i)
    if (p_lower[i] == ch) return p_upper[i];
  return ch;
}

}  // namespace liuyunbin

#endif
