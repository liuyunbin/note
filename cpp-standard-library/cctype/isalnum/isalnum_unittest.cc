
#include "isalnum.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isalnum) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isalnum(i) == 0, liuyunbin::isalnum(i) == 0);
  EXPECT_EQ(::isalnum(EOF) == 0, liuyunbin::isalnum(EOF) == 0);
}
