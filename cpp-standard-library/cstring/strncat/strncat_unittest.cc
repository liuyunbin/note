
#include "strncat.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strncat) {
  {
    const char *src = "";
    char to_1[100] = "";
    char to_2[100] = "";
    const int n = 100;
    EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
  }
  {
    const char *src = "1234567890";
    char to_1[100] = "123";
    char to_2[100] = "123";
    const int n = 3;
    EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
  }
  {
    const char *src = "1234567890";
    char to_1[100] = "123";
    char to_2[100] = "123";
    const int n = 30;
    EXPECT_STREQ(::strncat(to_1, src, n), liuyunbin::strncat(to_2, src, n));
  }
}
