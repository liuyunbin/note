
#include "memmove.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_memmove) {
  {
    char src_1[100] = "12345678\0 90123";
    char src_2[100] = "12345678\0 90123";
    char to_1[100];
    char to_2[100];
    const int n = 11;
    ::memmove(to_1, src_1, n);
    liuyunbin::memmove(to_2, src_2, n);
    for (int i = 0; i != n; ++i)
      EXPECT_EQ(to_1[i], to_2[i]);
  }
  {
    char src_1[100] = "12345678\0 90123";
    char src_2[100] = "12345678\0 90123";
    const int n = 11;
    ::memmove(src_1, src_1, n);
    liuyunbin::memmove(src_2, src_2, n);
    for (int i = 0; i != n; ++i)
      EXPECT_EQ(src_1[i], src_2[i]);
  }
  {
    char src_1[100] = "12345678\0 90123";
    char src_2[100] = "12345678\0 90123";
    const int n = 11;
    ::memmove(src_1, src_1 + 1, n);
    liuyunbin::memmove(src_2, src_2 + 1, n);
    for (int i = 0; i != n; ++i)
      EXPECT_EQ(src_1[i], src_2[i]);
  }
  {
    char src_1[100] = "12345678\0 90123";
    char src_2[100] = "12345678\0 90123";
    const int n = 11;
    ::memmove(src_1 + 1, src_1, n);
    liuyunbin::memmove(src_2 + 1, src_2, n);
    for (int i = 0; i != n; ++i)
      EXPECT_EQ(src_1[i + 1], src_2[i + 1]);
  }
}
