
#include "tolower.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_tolower) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::tolower(i), liuyunbin::tolower(i));
  EXPECT_EQ(::tolower(EOF), liuyunbin::tolower(EOF));
}
