
#include "min.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_min) {
  {
    int x = 10;
    int y = 5;
    EXPECT_EQ(std::min(x, y), liuyunbin::min(x, y));
  }
  {
    std::initializer_list<int> li = {1, 2, 3, 4, 5};
    EXPECT_EQ(std::min(li), liuyunbin::min(li));
  }
}
