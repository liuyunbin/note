
#include "isspace.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isspace) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isspace(i) == 0, liuyunbin::isspace(i) == 0);
  EXPECT_EQ(::isspace(EOF) == 0, liuyunbin::isspace(EOF) == 0);
}
