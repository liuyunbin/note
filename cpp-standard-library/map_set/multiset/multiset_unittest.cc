
#include "multiset.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::multiset<int>;

TEST(test_map_set, test_multiset) {
  liuyunbin::multiset<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::multiset<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}
