
#include "memset.h"

#include <string.h>

#include <gtest/gtest.h>

TEST(test_cstring, test_memset) {
  char dest_1[100];
  char dest_2[100];
  const int n = 15;
  ::memset(dest_1, '\0', n);
  liuyunbin::memset(dest_2, '\0', n);
  for (int i = 0; i != n; ++i)
    EXPECT_EQ(dest_1[i], dest_2[i]);
}
