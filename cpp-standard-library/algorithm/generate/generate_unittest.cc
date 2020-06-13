
#include "generate.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_generate) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };

    std::generate(forward_list_1.begin(), forward_list_1.end(), f);
    liuyunbin::generate(forward_list_2.begin(), forward_list_2.end(), f);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };

    std::generate(list_1.begin(), list_1.end(), f);
    liuyunbin::generate(list_2.begin(), list_2.end(), f);
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };

    std::generate(vector_1.begin(), vector_1.end(), f);
    liuyunbin::generate(vector_2.begin(), vector_2.end(), f);
    EXPECT_EQ(vector_1, vector_2);
  }
}
