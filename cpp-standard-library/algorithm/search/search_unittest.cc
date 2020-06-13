
#include "search.h"

#include <forward_list>
#include <list>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_search) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    auto x = std::search(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_2.cbegin(), forward_list_2.cend());
    auto y = liuyunbin::search(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {2, 3, 4};

    auto x = std::search(forward_list_1.cbegin(), forward_list_1.cend(),
                         forward_list_2.cbegin(), forward_list_2.cend());
    auto y = liuyunbin::search(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    auto x = std::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                         list_2.cend());
    auto y = liuyunbin::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {2, 3, 4};

    auto x = std::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                         list_2.cend());
    auto y = liuyunbin::search(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                               list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    auto x = std::search(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                         vector_2.cend());
    auto y = liuyunbin::search(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {2, 3, 4};

    auto x = std::search(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                         vector_2.cend());
    auto y = liuyunbin::search(vector_1.cbegin(), vector_1.cend(),
                               vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
}
