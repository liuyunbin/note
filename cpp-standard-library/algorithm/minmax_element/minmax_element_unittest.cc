
#include "minmax_element.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_minmax_element) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 8, 4, 5};
    auto x =
        std::minmax_element(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::minmax_element(forward_list_1.cbegin(),
                                       forward_list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 8, 4, 5};
    auto x = std::minmax_element(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::minmax_element(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 8, 4, 5};
    auto x = std::minmax_element(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::minmax_element(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
}
