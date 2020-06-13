
#include "partition.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partition) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(forward_list_1.begin(), forward_list_1.end(), f);
    auto y =
        liuyunbin::partition(forward_list_1.begin(), forward_list_1.end(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(forward_list_1.begin(), forward_list_1.end(), f);
    auto y =
        liuyunbin::partition(forward_list_1.begin(), forward_list_1.end(), f);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(list_1.begin(), list_1.end(), f);
    auto y = liuyunbin::partition(list_1.begin(), list_1.end(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(list_1.begin(), list_1.end(), f);
    auto y = liuyunbin::partition(list_1.begin(), list_1.end(), f);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(vector_1.begin(), vector_1.end(), f);
    auto y = liuyunbin::partition(vector_1.begin(), vector_1.end(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::partition(vector_1.begin(), vector_1.end(), f);
    auto y = liuyunbin::partition(vector_1.begin(), vector_1.end(), f);
    EXPECT_EQ(x, y);
  }
}
