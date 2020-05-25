
#include "iscntrl.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_iscntrl) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::iscntrl(i) == 0, liuyunbin::iscntrl(i) == 0);
  EXPECT_EQ(::iscntrl(EOF) == 0, liuyunbin::iscntrl(EOF) == 0);
}
