
#include "iota.h"

#include <forward_list>
#include <list>
#include <numeric>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_numeric, test_iota) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
    int a = 1;
    std::iota(forward_list_1.begin(), forward_list_1.end(), a);
    liuyunbin::iota(forward_list_2.begin(), forward_list_2.end(), a);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};
    int a = 1;
    std::iota(list_1.begin(), list_1.end(), a);
    liuyunbin::iota(list_2.begin(), list_2.end(), a);
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};
    int a = 1;
    std::iota(vector_1.begin(), vector_1.end(), a);
    liuyunbin::iota(vector_2.begin(), vector_2.end(), a);
    EXPECT_EQ(vector_1, vector_2);
  }
}
