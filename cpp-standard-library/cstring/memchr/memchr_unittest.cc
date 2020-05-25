
#include "memchr.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_memchr) {
  {
    const char *ptr = "12345678\0 90123";
    const int n = 15;
    const char ch = '1';
    EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
  }
  {
    const char *ptr = "12345678\0 90123";
    const int n = 15;
    const char ch = '9';
    EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
  }
  {
    const char *ptr = "12345678\0 90123";
    const int n = 15;
    const char ch = '\0';
    EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
  }
  {
    const char *ptr = "12345678\0 90123";
    const int n = 15;
    const char ch = 'a';
    EXPECT_EQ(::memchr(ptr, n, ch), liuyunbin::memchr(ptr, n, ch));
  }
}
