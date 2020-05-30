
#include "unordered_map.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::unordered_map<int, std::string>;

TEST(test_unordered_map_set, test_unordered_map) {
  liuyunbin::unordered_map<int, std::string> ve_1 = {
      {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"},
  };
  liuyunbin::unordered_map<int, std::string> ve_2 = {
      {2, "2"}, {4, "3"}, {6, "6"}, {8, "8"}, {10, "10"},
  };

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}
