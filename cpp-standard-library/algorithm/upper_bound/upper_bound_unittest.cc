
#include "upper_bound.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_upper_bound) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x =
        std::upper_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::upper_bound(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x =
        std::upper_bound(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::upper_bound(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x = std::upper_bound(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::upper_bound(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x = std::upper_bound(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::upper_bound(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x = std::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x = std::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::upper_bound(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
}
