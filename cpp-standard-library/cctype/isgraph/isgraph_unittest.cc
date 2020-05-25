
#include "isgraph.h"

#include <ctype.h>

#include <gtest/gtest.h>

TEST(test_cctype, test_isgraph) {
  for (int i = 0; i != 256; ++i)
    EXPECT_EQ(::isgraph(i) == 0, liuyunbin::isgraph(i) == 0);
  EXPECT_EQ(::isgraph(EOF) == 0, liuyunbin::isgraph(EOF) == 0);
}
