
#include "ispunct.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_ispunct) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::ispunct(i) == 0, liuyunbin::ispunct(i) == 0);
  EXPECT_EQ(::ispunct(EOF) == 0, liuyunbin::ispunct(EOF) == 0);
}
