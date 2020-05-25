
#include "isprint.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isprint) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isprint(i) == 0, liuyunbin::isprint(i) == 0);
  EXPECT_EQ(::isprint(EOF) == 0, liuyunbin::isprint(EOF) == 0);
}
