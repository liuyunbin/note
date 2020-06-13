
#include "iter_swap.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_iter_swap) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};
    std::iter_swap(forward_list_1.begin(),
                   std::next(forward_list_1.begin(), 2));
    liuyunbin::iter_swap(forward_list_2.begin(),
                         std::next(forward_list_2.begin(), 2));
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};
    std::iter_swap(list_1.begin(), std::next(list_1.begin(), 2));
    liuyunbin::iter_swap(list_2.begin(), std::next(list_2.begin(), 2));
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};
    std::iter_swap(vector_1.begin(), std::next(vector_1.begin(), 2));
    liuyunbin::iter_swap(vector_2.begin(), std::next(vector_2.begin(), 2));
    EXPECT_EQ(vector_1, vector_2);
  }
}
