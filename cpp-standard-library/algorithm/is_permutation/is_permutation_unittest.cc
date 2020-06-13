
#include "is_permutation.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_permutation) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
    auto x = std::is_permutation(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_2.cbegin());
    auto y = liuyunbin::is_permutation(forward_list_1.cbegin(),
                                       forward_list_1.cend(),
                                       forward_list_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
    auto x = std::is_permutation(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_2.cbegin());
    auto y = liuyunbin::is_permutation(forward_list_1.cbegin(),
                                       forward_list_1.cend(),
                                       forward_list_2.cbegin());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
    auto x =
        std::is_permutation(list_1.cbegin(), list_1.cend(), list_2.cbegin());
    auto y = liuyunbin::is_permutation(list_1.cbegin(), list_1.cend(),
                                       list_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
    auto x =
        std::is_permutation(list_1.cbegin(), list_1.cend(), list_2.cbegin());
    auto y = liuyunbin::is_permutation(list_1.cbegin(), list_1.cend(),
                                       list_2.cbegin());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 5};
    auto x = std::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin());
    auto y = liuyunbin::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                       vector_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 1, 2, 2, 3, 4, 3, 4, 5, 6};
    auto x = std::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin());
    auto y = liuyunbin::is_permutation(vector_1.cbegin(), vector_1.cend(),
                                       vector_2.cbegin());
    EXPECT_EQ(x, y);
  }
}
