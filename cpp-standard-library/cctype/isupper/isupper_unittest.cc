
#include "isupper.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isupper) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isupper(i) == 0, liuyunbin::isupper(i) == 0);
  EXPECT_EQ(::isupper(EOF) == 0, liuyunbin::isupper(EOF) == 0);
}
