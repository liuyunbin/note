
#include "strncmp.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_strncmp) {
  {
    const char *lhs = "";
    const char *rhs = "";
    const int n = 10;
    EXPECT_EQ(::strncmp(lhs, rhs, n) > 0, liuyunbin::strncmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
              liuyunbin::strncmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) < 0, liuyunbin::strncmp(lhs, rhs, n) < 0);
  }
  {
    const char *lhs = "123";
    const char *rhs = "1234";
    const int n = 3;
    EXPECT_EQ(::strncmp(lhs, rhs, n) > 0, liuyunbin::strncmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
              liuyunbin::strncmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) < 0, liuyunbin::strncmp(lhs, rhs, n) < 0);
  }
  {
    const char *lhs = "1234";
    const char *rhs = "123";
    const int n = 10;
    EXPECT_EQ(::strncmp(lhs, rhs, n) > 0, liuyunbin::strncmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) == 0,
              liuyunbin::strncmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::strncmp(lhs, rhs, n) < 0, liuyunbin::strncmp(lhs, rhs, n) < 0);
  }
}
