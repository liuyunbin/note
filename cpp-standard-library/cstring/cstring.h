#ifndef CPP_STANDARD_LIBRARY_CSTRING_H_
#define CPP_STANDARD_LIBRARY_CSTRING_H_

#include <stdio.h>

namespace liuyunbin {

/*
 * 函数原型：
 *   const void* memchr(const void* ptr, int ch, size_t count);
 *         void* memchr(      void* ptr, int ch, size_t count);
 *
 * 函数说明：
 *   * 查找 ptr 所指向的数组中的 ch 第一次出现的位置
 *   * ptr 将转化为 unsigned char*
 *   * ch  将转化为 unsigned char
 *
 * 返回说明：
 *   * 如果找到，返回 ch 第一次出现的位置
 *   * 否则，返回 NULL
 *
 */

const void *memchr(const void *ptr, int ch, size_t count) {
  auto new_ptr = static_cast<unsigned char *>(const_cast<void *>(ptr));
  auto new_ch = static_cast<unsigned char>(ch);
  for (size_t i = 0; i < count; ++i)
    if (new_ptr[i] == new_ch) return static_cast<void *>(new_ptr + i);
  return NULL;
}

void *memchr(void *ptr, int ch, size_t count) {
  return const_cast<void *>(memchr(const_cast<const void *>(ptr), ch, count));
}

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
  if (lhs == rhs) return 0;

  auto new_lhs = static_cast<const unsigned char *>(lhs);
  auto new_rhs = static_cast<const unsigned char *>(rhs);

  for (size_t i = 0; i < count; ++i)
    if (new_lhs[i] != new_rhs[i]) return new_lhs[i] < new_rhs[i] ? -1 : 1;
  return 0;
}

/*
 * 函数原型：
 *   void* memcpy(void* dest, const void* src, size_t count);
 *
 * 函数说明：
 *   * 将 src 指向的数组复制到 dest 所指向的数组，复制 count 个字符
 *   * dest 将转化为 unsigned char*
 *   * src  将转化为 unsigned char*
 *   * 本函数不能处理数组重叠的情况
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

void *memcpy(void *dest, const void *src, size_t count) {
  if (dest == src) return dest;

  auto new_dest = static_cast<unsigned char *>(dest);
  auto new_src = static_cast<const unsigned char *>(src);
  for (size_t i = 0; i < count; ++i) new_dest[i] = new_src[i];
  return dest;
}

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
  if (dest == src) return dest;

  if (dest < src) return ::memcpy(dest, src, count);

  auto new_dest = static_cast<unsigned char *>(dest);
  auto new_src = static_cast<const unsigned char *>(src);

  for (size_t i = 0; i < count; ++i)
    new_dest[count - i - 1] = new_src[count - i - 1];
  return dest;
}

/*
 * 函数原型：
 *   void* memset(void* dest, int ch, size_t count);
 *
 * 函数说明：
 *   * 将 dest 所指向的数组中的前 count 个字符设置为 ch
 *   * dest 将转化为 unsigned char*
 *   * ch   将转化为 unsigned char
 *
 * 参数要求：
 *   * dest 所指向的数组的大小最小为 count
 *
 * 返回说明：
 *   * 返回 dest
 */

void *memset(void *dest, int ch, size_t count) {
  auto new_dest = static_cast<unsigned char *>(dest);
  auto new_ch = static_cast<unsigned char>(ch);
  for (size_t i = 0; i < count; ++i) new_dest[i] = new_ch;
  return dest;
}

/*
 * 函数原型：
 *   char* strcat(char* dest, const char* src);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），添加到 dest 所指向的字符串之后
 *
 * 参数要求：
 *   * dest 为指向以 '\0' 结尾的的字符串的指针
 *   * src  为指向以 '\0' 结尾的的字符串的指针
 *   * dest 所指向的字符数组的长度最小为：strlen(dest) + strlen(src) + 1
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终将包含 '\0'
 */

char *strcat(char *dest, const char *src) {
  size_t dest_size = ::strlen(dest);
  for (size_t i = 0;; ++i) {
    dest[dest_size + i] = src[i];
    if (dest[dest_size + i] == '\0') break;
  }

  return dest;
}

/*
 * 函数原型：
 *   const char* strchr(const char* str, int ch);
 *         char* strchr(      char* str, int ch);
 *
 * 函数说明：
 *   * 查找 str 所指向的字符串中的第一个 ch 的位置
 *   * ch 将转化为 char 比较
 *   * ch 可以是 '\0'
 *   * str 所指向的字符串中的 '\0' 也会被查找
 *
 * 参数要求：
 *   * src 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回 str 所指向的字符串中的第一个 ch 的位置
 *   * 如果未找到，将返回 NULL
 *
 */

const char *strchr(const char *str, int ch) {
  for (;;) {
    if (*str == static_cast<char>(ch)) return str;
    if (*str == '\0') return NULL;
    ++str;
  }
}

char *strchr(char *str, int ch) {
  return const_cast<char *>(strchr(const_cast<const char *>(str), ch));
}

/*
 * 函数原型：
 *   int strcmp(const char* lhs, const char* rhs);
 *
 * 函数说明：
 *   比较 lhs 和 rhs 所指向字符串的大小，将转化为 unsigned char 比较
 *
 * 参数要求：
 *   * lhs 所指向的字符数组中一定包含 '\0'
 *   * rhs 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果 lhs >  rhs，返回 1
 *   * 如果 lhs == rhs，返回 0
 *   * 如果 lhs <  rhs，返回 -1
 *
 * 优化：
 *   * 如果，lhs 和 rhs 的值相同，则无需比较，直接相同
 */

int strcmp(const char *lhs, const char *rhs) {
  if (lhs == rhs) return 0;

  for (size_t i = 0;; ++i) {
    unsigned char lhs_char = lhs[i];
    unsigned char rhs_char = rhs[i];

    if (lhs_char != rhs_char) return lhs_char < rhs_char ? -1 : 1;

    if (lhs[i] == '\0') return 0;
  }
}

/*
 * 函数原型：
 *   char* strcpy(char* dest, const char* src);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），拷贝到 dest 所指向的字符数组中
 *
 * 参数要求：
 *   * src 为指向以 '\0' 结尾的的字符串的指针
 *   * dest 所指向的字符数组的长度最小为：strlen(src) + 1
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终将包含 '\0'
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则无需复制
 */

char *strcpy(char *dest, const char *src) {
  if (dest == src) return dest;

  for (size_t i = 0;; ++i) {
    dest[i] = src[i];
    if (dest[i] == '\0') break;
  }

  return dest;
}

/*
 * 函数原型：
 *   size_t strcspn(const char* dest, const char* src);
 *
 * 函数说明：
 *   * 查找 dest 所指向的字符串中，从头开始，不包含 src 中的字符的最大长度
 *
 * 参数要求：
 *   * dest 所指向的字符数组中一定包含 '\0'
 *   * src  所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 返回 dest 所指向的字符串中，从头开始，不包含 src 中的字符的最大长度
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则直接返回
 */

size_t strcspn(const char *dest, const char *src) {
  if (dest == src) return 0;

  for (size_t i = 0;; ++i) {
    if (dest[i] == '\0') return i;
    if (::strchr(src, dest[i]) != NULL) return i;
  }
}

/*
 * 函数原型：
 *   size_t strlen(const char* str);
 *
 * 函数说明：
 *   * 求 str 所指向字符串的长度
 *
 * 参数要求：
 *   * str 为指向以 '\0' 结尾的的字符串的指针
 *
 * 返回说明：
 *   * 返回 src 所指向的字符串（不包括 '\0'）的长度
 */

size_t strlen(const char *str) {
  for (size_t i = 0;; ++i)
    if (str[i] == '\0') return i;
}

/*
 * 函数原型：
 *   char* strncat(char* dest, const char* src, size_t count);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），添加到 dest
 *      所指向的字符串之后，最多拷贝 count 个字符
 *
 * 参数要求：
 *   * src  所指向的字符数组不一定包含 '\0'
 *   * dest 所指向的字符数组中一定包含 '\0'
 *   * dest 所指向的字符数组的长度最小为：
 *       strlen(dest) + min(strlen(src), count) + 1
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终一定包含 '\0'
 *
 * 特别说明：
 *   * src 所指向的字符数组的长度小于 count，且 src 所指向的字符数组不包括
 *        '\0'，是未定义的行为
 *
 * 优化：
 *   * 如果，count <= 0，则无需添加
 */

char *strncat(char *dest, const char *src, size_t count) {
  if (count <= 0) return dest;

  size_t dest_size = ::strlen(dest);
  for (size_t i = 0;; ++i) {
    if (i == count) {
      dest[dest_size + i] = '\0';
      break;
    }
    dest[dest_size + i] = src[i];
    if (dest[dest_size + i] == '\0') break;
  }
  return dest;
}

/*
 * 函数原型：
 *   int strncmp(const char* lhs, const char* rhs, size_t count);
 *
 * 函数说明：
 *   比较 lhs 和 rhs 所指向字符串的大小，将转化为 unsigned char 比较，最多比较
 * count 个字符
 *
 * 参数要求：
 *   * lhs 所指向的字符数组中不一定包含 '\0'
 *   * rhs 所指向的字符数组中不一定包含 '\0'
 *
 * 返回说明：
 *   * 如果 lhs >  rhs，返回 1
 *   * 如果 lhs == rhs，返回 0
 *   * 如果 lhs <  rhs，返回 -1
 *
 * 未定义的行为：
 *   * 当 lhs 或 rhs 指向的字符数组不包括 '\0'，且比较时，超出其对应的数组大小
 *
 * 优化：
 *   * 如果，lhs 和 rhs 的值相同，则无需比较，直接相同
 *   * 如果，count <= 0，则无需比较，直接相同
 */

int strncmp(const char *lhs, const char *rhs, size_t count) {
  if (lhs == rhs || count <= 0) return 0;

  for (size_t i = 0; i < count; ++i) {
    unsigned char lhs_char = lhs[i];
    unsigned char rhs_char = rhs[i];
    if (lhs_char != rhs_char) return lhs_char < rhs_char ? -1 : 1;
    if (lhs[i] == '\0') return 0;
  }
  return 0;
}

/*
 * 函数原型：
 *   char* strncpy(char* dest, const char* src, size_t count);
 *
 * 函数说明：
 *   将 src 所指向的字符串（包括 '\0'），拷贝到 dest
 *     所指向的字符数组中，最多拷贝 count 个字符
 *
 * 参数要求：
 *   * src  所指向的字符数组不一定包含 '\0'
 *   * dest 所指向的字符数组的长度最小为：count
 *   * src 和 dest 所指向的字符数组不能重叠
 *
 * 返回说明：
 *   * 返回 dest，dest 所指向的字符数组最终不一定包含 '\0'
 *
 * 特别说明：
 *   * src 所指向的字符数组的长度小于 count，且 src 所指向的字符数组不包括
 *       '\0'，是未定义的行为
 *   * 当已复制了 src 的所有元素（包括 '\0'）时，个数却未到 count
 *       时，程序将继续填充 '\0'，直到 count 个字符
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则无需复制
 *   * 如果，count <= 0，则无需复制
 */

char *strncpy(char *dest, const char *src, size_t count) {
  if (dest == src || count <= 0) return dest;

  for (size_t i = 0; i != count; ++i) {
    dest[i] = src[i];
    if (dest[i] == '\0') {
      while (++i != count) dest[i] = '\0';
      break;
    }
  }

  return dest;
}

/*
 * 函数原型：
 *   const char* strpbrk(const char* dest, const char* breakset);
 *         char* strpbrk(      char* dest, const char* breakset);
 *
 * 函数说明：
 *   * 查找 dest 所指向的字符串中，第一个在 breakset 中出现的字符的位置
 *
 * 参数要求：
 *   * dest     所指向的字符数组中一定包含 '\0'
 *   * breakset 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回该字符的位置
 *   * 否则，返回 NULL
 *
 * 优化：
 *   * 如果，dest 和 breakset 的值相同，则直接返回
 */

const char *strpbrk(const char *dest, const char *breakset) {
  if (dest == breakset) return dest;

  for (size_t i = 0; dest[i] != '\0'; ++i)
    if (::strchr(breakset, dest[i]) != NULL) return dest + i;
  return NULL;
}

char *strpbrk(char *dest, const char *breakset) {
  return const_cast<char *>(strpbrk(const_cast<const char *>(dest), breakset));
}

/*
 * 函数原型：
 *   const char* strrchr(const char* str, int ch);
 *         char* strrchr(      char* str, int ch);
 *
 * 函数说明：
 *   * 查找 str 所指向的字符串中的最后一个 ch 的位置
 *   * ch 将转化为 char 比较
 *   * ch 可以是 '\0'
 *   * str 所指向的字符串中的 '\0' 也会被查找
 *
 * 参数要求：
 *   * src 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回 str 所指向的字符串中的最后一个 ch 的位置
 *   * 如果未找到，将返回 NULL
 */

const char *strrchr(const char *str, int ch) {
  auto last = str + ::strlen(str);
  for (;;) {
    if (*last == static_cast<char>(ch)) return last;
    if (last == str) return NULL;
    --last;
  }
}

char *strrchr(char *str, int ch) {
  return const_cast<char *>(strrchr(const_cast<const char *>(str), ch));
}

/*
 * 函数原型：
 *   size_t strspn(const char* dest, const char* src);
 *
 * 函数说明：
 *   * 查找 dest 所指向的字符串中，从头开始，只包含 src 中的字符的最大长度
 *
 * 参数要求：
 *   * dest 所指向的字符数组中一定包含 '\0'
 *   * src  所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 返回 dest 所指向的字符串中，从头开始，只包含 src 中的字符的最大长度
 *
 * 优化：
 *   * 如果，dest 和 src 的值相同，则直接返回
 */

size_t strspn(const char *dest, const char *src) {
  if (dest == src) return ::strlen(dest);

  for (size_t i = 0;; ++i) {
    if (dest[i] == '\0') return i;
    if (::strchr(src, dest[i]) == NULL) return i;
  }
}

/*
 * 函数原型：
 *   const char* strstr(const char* str, const char* target);
 *         char* strstr(      char* str, const char* target);
 *
 * 函数说明：
 *   * 查找 str 所指向的字符串中和 target 相同的子序列的首位置
 *
 * 参数要求：
 *   * str    所指向的字符数组中一定包含 '\0'
 *   * target 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回首位置
 *   * 否则，返回 NULL
 *
 * 优化：
 *   * 如果，str 和 target 的值相同，则直接返回
 */

const char *strstr(const char *str, const char *target) {
  if (str == target) return str;

  for (;;) {
    auto temp = str;
    auto it = target;
    for (;;) {
      if (*it == '\0') return str;
      if (*temp == '\0') return NULL;
      if (*it != *temp) break;
      ++it;
      ++temp;
    }
    ++str;
  }
}

char *strstr(char *str, const char *target) {
  return const_cast<char *>(strstr(const_cast<const char *>(str), target));
}

/*
 * 函数原型：
 *   char* strtok(char* str, const char* delim);
 *
 * 函数说明：
 *   * 使用 delim 中的字符，对 str 字符数组进行切割
 *
 * 参数要求：
 *   * str   可能是 NULL
 *   * str   所指向的字符数组中一定包含 '\0'
 *   * delim 所指向的字符数组中一定包含 '\0'
 *
 * 返回说明：
 *   * 如果找到，返回首位置
 *   * 否则，返回 NULL
 *
 * 特别说明：
 *   * 此函数，线程不安全
 *
 */

char *strtok(char *str, const char *delim) {
  static char *p = NULL;

  if (str != NULL) p = str;
  if (p == NULL) return NULL;
  p = p + ::strspn(p, delim);
  if (*p == '\0') {
    p = NULL;
    return NULL;
  }
  char *return_str = p;
  p = p + ::strcspn(p, delim);
  if (*p == '\0')
    p = NULL;
  else
    *p++ = '\0';
  return return_str;
}

}  // namespace liuyunbin

#endif
