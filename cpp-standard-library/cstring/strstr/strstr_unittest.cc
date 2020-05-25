
#include "strstr.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strstr) {
  {
    const char *str = "1234567890123";
    const char *target = "13";
    EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
  }
  {
    const char *str = "1234567890123";
    const char *target = "abc";
    EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
  }
  {
    const char *str = "1234567890123";
    const char *target = "123abc";
    EXPECT_EQ(::strstr(str, target), liuyunbin::strstr(str, target));
  }
}
