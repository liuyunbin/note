
#include "islower.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_islower) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::islower(i) == 0, liuyunbin::islower(i) == 0);
  EXPECT_EQ(::islower(EOF) == 0, liuyunbin::islower(EOF) == 0);
}
