
#include "rotate_copy.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_rotate_copy) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {7, 8, 0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {7, 8, 0, 1, 2, 3, 4};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

    liuyunbin::rotate_copy(forward_list_1.cbegin(),
                           std::next(forward_list_1.cbegin(), 2),
                           forward_list_1.cend(), forward_list_3.begin());
    liuyunbin::rotate_copy(forward_list_2.cbegin(),
                           std::next(forward_list_2.cbegin(), 2),
                           forward_list_2.cend(), forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {7, 8, 0, 1, 2, 3, 4};
    std::list<int> list_2 = {7, 8, 0, 1, 2, 3, 4};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

    liuyunbin::rotate_copy(list_1.cbegin(), std::next(list_1.cbegin(), 2),
                           list_1.cend(), forward_list_3.begin());
    liuyunbin::rotate_copy(list_2.cbegin(), std::next(list_2.cbegin(), 2),
                           list_2.cend(), forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {7, 8, 0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {7, 8, 0, 1, 2, 3, 4};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0};

    liuyunbin::rotate_copy(vector_1.cbegin(), std::next(vector_1.cbegin(), 2),
                           vector_1.cend(), forward_list_3.begin());
    liuyunbin::rotate_copy(vector_2.cbegin(), std::next(vector_2.cbegin(), 2),
                           vector_2.cend(), forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
