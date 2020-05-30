
#include "unordered_set.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::unordered_set<int>;

TEST(test_unordered_map_set, test_unordered_set) {
  liuyunbin::unordered_set<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::unordered_set<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);
}
