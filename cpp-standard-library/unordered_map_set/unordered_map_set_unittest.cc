
#include "unordered_map_set.h"

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

// 显示实例化
template class liuyunbin::unordered_multiset<int>;

TEST(test_unordered_map_set, test_unordered_multiset) {
  liuyunbin::unordered_multiset<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::unordered_multiset<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);
}

// 显示实例化
template class liuyunbin::unordered_set<int>;

TEST(test_unordered_map_set, test_unordered_set) {
  liuyunbin::unordered_set<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::unordered_set<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);
}
