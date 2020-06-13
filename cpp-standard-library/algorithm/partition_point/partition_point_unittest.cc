
#include "partition_point.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partition_point) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3; };
    auto x =
        std::partition_point(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y = liuyunbin::partition_point(forward_list_1.cbegin(),
                                        forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v == 10; };
    auto x =
        std::partition_point(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y = liuyunbin::partition_point(forward_list_1.cbegin(),
                                        forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3; };
    auto x = std::partition_point(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::partition_point(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v == 10; };
    auto x = std::partition_point(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::partition_point(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3; };
    auto x = std::partition_point(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::partition_point(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v == 10; };
    auto x = std::partition_point(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::partition_point(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
}
