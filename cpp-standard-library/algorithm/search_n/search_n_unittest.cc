
#include "search_n.h"

#include <forward_list>
#include <list>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_search_n) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    int n = 2;
    int v = 3;
    auto x =
        std::search_n(forward_list_1.cbegin(), forward_list_1.cend(), n, v);
    auto y = liuyunbin::search_n(forward_list_1.cbegin(), forward_list_1.cend(),
                                 n, v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 3, 3, 4};

    int n = 2;
    int v = 3;
    auto x =
        std::search_n(forward_list_1.cbegin(), forward_list_1.cend(), n, v);
    auto y = liuyunbin::search_n(forward_list_1.cbegin(), forward_list_1.cend(),
                                 n, v);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    int n = 2;
    int v = 3;
    auto x = std::search_n(list_1.cbegin(), list_1.cend(), n, v);
    auto y = liuyunbin::search_n(list_1.cbegin(), list_1.cend(), n, v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 3, 3, 4};

    int n = 2;
    int v = 3;
    auto x = std::search_n(list_1.cbegin(), list_1.cend(), n, v);
    auto y = liuyunbin::search_n(list_1.cbegin(), list_1.cend(), n, v);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    int n = 2;
    int v = 3;
    auto x = std::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
    auto y = liuyunbin::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 3, 3, 4};

    int n = 2;
    int v = 3;
    auto x = std::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
    auto y = liuyunbin::search_n(vector_1.cbegin(), vector_1.cend(), n, v);
    EXPECT_EQ(x, y);
  }
}
