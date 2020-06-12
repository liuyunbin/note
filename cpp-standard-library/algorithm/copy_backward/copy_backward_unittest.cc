
#include "copy_backward.h"

#include <algorithm>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_copy_backward) {

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {0, 1, 2, 3, 4};
    std::list<int> list_3 = {5, 6, 7, 8, 9};
    std::copy_backward(list_1.cbegin(), list_1.cend(), list_2.end());
    liuyunbin::copy_backward(list_1.cbegin(), list_1.cend(), list_3.end());
    EXPECT_EQ(list_2, list_3);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {0, 1, 2, 3, 4};
    std::list<int> list_3 = {5, 6, 7, 8, 9};
    std::copy_backward(vector_1.cbegin(), vector_1.cend(), list_2.end());
    liuyunbin::copy_backward(vector_1.cbegin(), vector_1.cend(), list_3.end());
    EXPECT_EQ(list_2, list_3);
  }
}
