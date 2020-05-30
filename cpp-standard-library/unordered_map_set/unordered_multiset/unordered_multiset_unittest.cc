
#include "unordered_multiset.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::unordered_multiset<int>;

TEST(test_unordered_map_set, test_unordered_multiset) {
  liuyunbin::unordered_multiset<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::unordered_multiset<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);
}
