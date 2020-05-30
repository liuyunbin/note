
#include "set.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::set<int>;

TEST(test_map_set, test_set) {
  liuyunbin::set<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::set<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}
