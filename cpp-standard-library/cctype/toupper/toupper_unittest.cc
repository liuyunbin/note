
#include "toupper.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_toupper) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::toupper(i), liuyunbin::toupper(i));
  EXPECT_EQ(::toupper(EOF), liuyunbin::toupper(EOF));
}
