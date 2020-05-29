
#include "forward_list.h"

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::forward_list<int>;

TEST(test_forward_list, test_forward_list) {
  liuyunbin::forward_list<int> fo_1 = {0, 1, 2, 3, 4};
  liuyunbin::forward_list<int> fo_2 = {5, 6, 7, 8, 9};

  fo_1.swap(fo_2);

  EXPECT_NE(fo_1, fo_2);
}

