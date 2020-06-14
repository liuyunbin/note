
#include "swap_ranges.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_swap_ranges) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
    std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};

    std::swap_ranges(forward_list_1.begin(), forward_list_1.end(),
                     forward_list_2.begin());
    liuyunbin::swap_ranges(forward_list_3.begin(), forward_list_3.end(),
                           forward_list_4.begin());
    EXPECT_EQ(forward_list_1, forward_list_3);
    EXPECT_EQ(forward_list_2, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};
    std::list<int> list_3 = {0, 1, 2, 3, 4};
    std::list<int> list_4 = {5, 6, 7, 8, 9};

    std::swap_ranges(list_1.begin(), list_1.end(), list_2.begin());
    liuyunbin::swap_ranges(list_3.begin(), list_3.end(), list_4.begin());
    EXPECT_EQ(list_1, list_3);
    EXPECT_EQ(list_2, list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};
    std::vector<int> vector_3 = {0, 1, 2, 3, 4};
    std::vector<int> vector_4 = {5, 6, 7, 8, 9};

    std::swap_ranges(vector_1.begin(), vector_1.end(), vector_2.begin());
    liuyunbin::swap_ranges(vector_3.begin(), vector_3.end(), vector_4.begin());
    EXPECT_EQ(vector_1, vector_3);
    EXPECT_EQ(vector_2, vector_4);
  }
}
