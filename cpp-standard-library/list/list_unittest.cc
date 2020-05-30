
#include "list.h"

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::list<int>;

TEST(test_list, test_list) {
  liuyunbin::list<int> li_1 = {0, 1, 2, 3, 4};
  liuyunbin::list<int> li_2 = {5, 6, 7, 8, 9};

  li_1.swap(li_2);

  EXPECT_NE(li_1, li_2);
}

