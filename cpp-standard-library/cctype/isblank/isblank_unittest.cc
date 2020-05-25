
#include "isblank.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isblank) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isblank(i) == 0, liuyunbin::isblank(i) == 0);
  EXPECT_EQ(::isblank(EOF) == 0, liuyunbin::isblank(EOF) == 0);
}
