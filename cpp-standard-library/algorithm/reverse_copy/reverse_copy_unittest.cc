
#include "reverse_copy.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_reverse_copy) {
  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::reverse_copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin());
    liuyunbin::reverse_copy(list_2.cbegin(), list_2.cend(),
                            forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::reverse_copy(vector_1.cbegin(), vector_1.cend(),
                      forward_list_3.begin());
    liuyunbin::reverse_copy(vector_2.cbegin(), vector_2.cend(),
                            forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
