
#include "generate_n.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_generate_n) {
  // 输出迭代器 不好测试

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };
    int n = 5;

    std::generate_n(forward_list_1.begin(), n, f);
    liuyunbin::generate_n(forward_list_2.begin(), n, f);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };
    int n = 5;

    std::generate_n(list_1.begin(), n, f);
    liuyunbin::generate_n(list_2.begin(), n, f);
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    auto f = []() { return 1; };
    int n = 5;

    std::generate_n(vector_1.begin(), n, f);
    liuyunbin::generate_n(vector_2.begin(), n, f);
    EXPECT_EQ(vector_1, vector_2);
  }
}
