
#include "minmax.h"

#include <algorithm>
#include <initializer_list>

#include <gtest/gtest.h>

TEST(test_algorithm, test_minmax) {
  {
    int x = 10;
    int y = 5;
    EXPECT_EQ(std::minmax(x, y), liuyunbin::minmax(x, y));
  }
  {
    std::initializer_list<int> li = {1, 2, 3, 4, 5};
    EXPECT_EQ(std::minmax(li), liuyunbin::minmax(li));
  }
}
