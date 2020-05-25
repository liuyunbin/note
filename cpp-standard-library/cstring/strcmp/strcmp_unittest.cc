
#include "strcmp.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strcmp) {
  {
    const char *lhs = "";
    const char *rhs = "";
    EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
    EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
    EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
  }
  {
    const char *lhs = "123";
    const char *rhs = "1234";
    EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
    EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
    EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
  }
  {
    const char *lhs = "1234";
    const char *rhs = "123";
    EXPECT_EQ(::strcmp(lhs, rhs) > 0, liuyunbin::strcmp(lhs, rhs) > 0);
    EXPECT_EQ(::strcmp(lhs, rhs) == 0, liuyunbin::strcmp(lhs, rhs) == 0);
    EXPECT_EQ(::strcmp(lhs, rhs) < 0, liuyunbin::strcmp(lhs, rhs) < 0);
  }
}
