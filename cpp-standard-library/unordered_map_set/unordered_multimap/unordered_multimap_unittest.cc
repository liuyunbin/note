
#include "unordered_multimap.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::unordered_multimap<int, std::string>;

TEST(test_unordered_map_set, test_unordered_multimap) {
  liuyunbin::unordered_multimap<int, std::string> ve_1 = {
      {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"},
  };
  liuyunbin::unordered_multimap<int, std::string> ve_2 = {
      {2, "2"}, {4, "3"}, {6, "6"}, {8, "8"}, {10, "10"},
  };

  ve_1.swap(ve_2);
}
