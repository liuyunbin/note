
#include "strcpy.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strcpy) {
  {
    const char *src = "";
    char to_1[100];
    char to_2[100];
    EXPECT_STREQ(::strcpy(to_1, src), liuyunbin::strcpy(to_2, src));
  }
  {
    const char *src = "1234567890";
    char to_1[100];
    char to_2[100];
    EXPECT_STREQ(::strcpy(to_1, src), liuyunbin::strcpy(to_2, src));
  }
}
