
#include "isdigit.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isdigit) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isdigit(i) == 0, liuyunbin::isdigit(i) == 0);
  EXPECT_EQ(::isdigit(EOF) == 0, liuyunbin::isdigit(EOF) == 0);
}
