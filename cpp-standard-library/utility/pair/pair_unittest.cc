
#include "pair.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::pair<int, std::string>;

TEST(test_utility, test_pair) {
  liuyunbin::pair<int, std::string> ve_1 = {1, "234"};
  liuyunbin::pair<int, std::string> ve_2 = {2, "456"};

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}
