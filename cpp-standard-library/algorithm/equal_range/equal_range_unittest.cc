
#include "equal_range.h"

#include <forward_list>
#include <list>
#include <numeric>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_equal_range) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x =
        std::equal_range(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::equal_range(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x =
        std::equal_range(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::equal_range(forward_list_1.cbegin(),
                                    forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x = std::equal_range(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::equal_range(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x = std::equal_range(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::equal_range(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    int v = 3;
    auto x = std::equal_range(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::equal_range(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    int v = 10;
    auto x = std::equal_range(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::equal_range(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
}
