
#include "isalpha.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isalpha) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isalpha(i) == 0, liuyunbin::isalpha(i) == 0);
  EXPECT_EQ(::isalpha(EOF) == 0, liuyunbin::isalpha(EOF) == 0);
}
