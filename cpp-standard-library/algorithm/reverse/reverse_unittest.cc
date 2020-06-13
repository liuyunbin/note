
#include "reverse.h"

#include <algorithm>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_reverse) {
  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::reverse(list_1.begin(), list_1.end());
    liuyunbin::reverse(list_2.begin(), list_2.end());
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::reverse(vector_1.begin(), vector_1.end());
    liuyunbin::reverse(vector_2.begin(), vector_2.end());
    EXPECT_EQ(vector_1, vector_2);
  }
}
