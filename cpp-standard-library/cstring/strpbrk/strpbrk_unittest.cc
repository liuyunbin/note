
#include "strpbrk.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strpbrk) {
  {
    const char *dest = "1234567890123";
    const char *breakset = "13";
    EXPECT_EQ(::strpbrk(dest, breakset), liuyunbin::strpbrk(dest, breakset));
  }
  {
    const char *dest = "1234567890123";
    const char *breakset = "abc";
    EXPECT_EQ(::strpbrk(dest, breakset), liuyunbin::strpbrk(dest, breakset));
  }
  {
    const char *dest = "1234567890123";
    const char *breakset = "123abc";
    EXPECT_EQ(::strpbrk(dest, breakset), liuyunbin::strpbrk(dest, breakset));
  }
}
