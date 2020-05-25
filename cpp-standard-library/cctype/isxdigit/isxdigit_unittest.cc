
#include "isxdigit.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isxdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isxdigit(i) == 0, liuyunbin::isxdigit(i) == 0);
  EXPECT_EQ(::isxdigit(EOF) == 0, liuyunbin::isxdigit(EOF) == 0);
}
