
#include "map_set.h"

#include <string>

#include <gtest/gtest.h>

// 显示实例化
template class liuyunbin::map<int, std::string>;

TEST(test_map_set, test_map) {
  liuyunbin::map<int, std::string> ve_1 = {
      {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"},
  };
  liuyunbin::map<int, std::string> ve_2 = {
      {2, "2"}, {4, "3"}, {6, "6"}, {8, "8"}, {10, "10"},
  };

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}

// 显示实例化
template class liuyunbin::multimap<int, std::string>;

TEST(test_map_set, test_multimap) {
  liuyunbin::multimap<int, std::string> ve_1 = {
      {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"},
  };
  liuyunbin::multimap<int, std::string> ve_2 = {
      {2, "2"}, {4, "3"}, {6, "6"}, {8, "8"}, {10, "10"},
  };

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}

// 显示实例化
template class liuyunbin::multiset<int>;

TEST(test_map_set, test_multiset) {
  liuyunbin::multiset<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::multiset<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}

// 显示实例化
template class liuyunbin::set<int>;

TEST(test_map_set, test_set) {
  liuyunbin::set<int> ve_1 = {1, 2, 3, 4, 5};
  liuyunbin::set<int> ve_2 = {2, 4, 6, 8, 10};

  ve_1.swap(ve_2);

  EXPECT_NE(ve_1, ve_2);
}
