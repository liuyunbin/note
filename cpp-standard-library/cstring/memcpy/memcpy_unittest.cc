
#include "memcpy.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_memcpy) {
  const char *src = "12345678\0 90123";
  char to_1[100];
  char to_2[100];
  const int n = 15;
  ::memcpy(to_1, src, n);
  liuyunbin::memcpy(to_2, src, n);
  for (int i = 0; i != n; ++i)
    EXPECT_EQ(to_1[i], to_2[i]);
}
