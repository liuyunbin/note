
#include "prev_permutation.h"

#include <algorithm>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_prev_permutation) {
  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};
    std::prev_permutation(list_1.begin(), list_1.end());
    liuyunbin::prev_permutation(list_2.begin(), list_2.end());
    EXPECT_EQ(list_1, list_2);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 3};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 3};
    std::prev_permutation(list_1.begin(), list_1.end());
    liuyunbin::prev_permutation(list_2.begin(), list_2.end());
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};
    std::prev_permutation(vector_1.begin(), vector_1.end());
    liuyunbin::prev_permutation(vector_2.begin(), vector_2.end());
    EXPECT_EQ(vector_1, vector_2);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 3};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 3};
    std::prev_permutation(vector_1.begin(), vector_1.end());
    liuyunbin::prev_permutation(vector_2.begin(), vector_2.end());
    EXPECT_EQ(vector_1, vector_2);
  }
}
