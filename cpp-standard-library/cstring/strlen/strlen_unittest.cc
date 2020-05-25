
#include "strlen.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strlen) {
  {
    const char *str = "";
    EXPECT_EQ(::strlen(str), liuyunbin::strlen(str));
  }
  {
    const char *str = "1234567890";
    EXPECT_EQ(::strlen(str), liuyunbin::strlen(str));
  }
}
