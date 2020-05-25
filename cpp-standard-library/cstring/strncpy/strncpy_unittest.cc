
#include "strncpy.h"

#include <string.h>

#include <string>

#include <gtest/gtest.h>

TEST(test_cstring, test_strncpy) {
  {
    const char *src = "";
    char to_1[100];
    char to_2[100];
    const int n = 10;
    EXPECT_STREQ(::strncpy(to_1, src, n), liuyunbin::strncpy(to_2, src, n));
  }
  {
    const char *src = "1234567890";
    char to_1[100];
    char to_2[100];
    const int n = 5;
    std::string str_to_1(::strncpy(to_1, src, n), n);
    std::string str_to_2(liuyunbin::strncpy(to_2, src, n), n);
    EXPECT_EQ(str_to_1, str_to_2);
  }
  {
    const char *src = "1234567890";
    char to_1[100];
    char to_2[100];
    const int n = 50;
    EXPECT_STREQ(::strncpy(to_1, src, n), liuyunbin::strncpy(to_2, src, n));
  }
}
