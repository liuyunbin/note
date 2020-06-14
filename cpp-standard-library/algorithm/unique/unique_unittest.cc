
#include "unique.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <list>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_unique) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::unique(forward_list_1.begin(), forward_list_1.end());
    liuyunbin::unique(forward_list_2.begin(), forward_list_2.end());

    EXPECT_EQ(forward_list_1, forward_list_2);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 1, 2, 2, 3, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 3, 4, 5};

    std::unique(forward_list_1.begin(), forward_list_1.end());
    liuyunbin::unique(forward_list_2.begin(), forward_list_2.end());

    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::unique(list_1.begin(), list_1.end());
    liuyunbin::unique(list_2.begin(), list_2.end());

    EXPECT_EQ(list_1, list_2);
  }
  {
    std::list<int> list_1 = {1, 1, 2, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 5};

    std::unique(list_1.begin(), list_1.end());
    liuyunbin::unique(list_2.begin(), list_2.end());

    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    std::unique(vector_1.begin(), vector_1.end());
    liuyunbin::unique(vector_2.begin(), vector_2.end());

    EXPECT_EQ(vector_1, vector_2);
  }
  {
    std::vector<int> vector_1 = {1, 1, 2, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 5};

    std::unique(vector_1.begin(), vector_1.end());
    liuyunbin::unique(vector_2.begin(), vector_2.end());

    EXPECT_EQ(vector_1, vector_2);
  }
}
