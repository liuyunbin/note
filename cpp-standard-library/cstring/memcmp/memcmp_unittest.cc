
#include "memcmp.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_memcmp) {
  {
    const char *lhs = "12345678\0 90123";
    const char *rhs = "12345677\0 90123";
    const int n = 15;
    EXPECT_EQ(::memcmp(lhs, rhs, n) > 0, liuyunbin::memcmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) == 0, liuyunbin::memcmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) < 0, liuyunbin::memcmp(lhs, rhs, n) < 0);
  }
  {
    const char *lhs = "12345678\0 90123";
    const char *rhs = "12345679\0 90123";
    const int n = 15;
    EXPECT_EQ(::memcmp(lhs, rhs, n) > 0, liuyunbin::memcmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) == 0, liuyunbin::memcmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) < 0, liuyunbin::memcmp(lhs, rhs, n) < 0);
  }
  {
    const char *lhs = "12345678\0 90123";
    const char *rhs = "12345678\0 90223";
    const int n = 15;
    EXPECT_EQ(::memcmp(lhs, rhs, n) > 0, liuyunbin::memcmp(lhs, rhs, n) > 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) == 0, liuyunbin::memcmp(lhs, rhs, n) == 0);
    EXPECT_EQ(::memcmp(lhs, rhs, n) < 0, liuyunbin::memcmp(lhs, rhs, n) < 0);
  }
}
