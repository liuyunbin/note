
#include "max.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_max) {
  {
    int x = 10;
    int y = 5;
    EXPECT_EQ(std::max(x, y), liuyunbin::max(x, y));
  }
  {
    std::initializer_list<int> li = {1, 2, 3, 4, 5};
    EXPECT_EQ(std::max(li), liuyunbin::max(li));
  }
}
