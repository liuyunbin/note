
#include "is_partitioned.h"

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

TEST(test_algorithm, test_is_partitioned) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(std::istream_iterator<int>(stream_1),
                                 std::istream_iterator<int>(), f);
    auto y = liuyunbin::is_partitioned(std::istream_iterator<int>(stream_2),
                                       std::istream_iterator<int>(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 5 7 9 8 6");
    std::istringstream stream_2("1 2 3 4 5 7 9 8 6");
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(std::istream_iterator<int>(stream_1),
                                 std::istream_iterator<int>(), f);
    auto y = liuyunbin::is_partitioned(std::istream_iterator<int>(stream_2),
                                       std::istream_iterator<int>(), f);
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x =
        std::is_partitioned(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y = liuyunbin::is_partitioned(forward_list_1.cbegin(),
                                       forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x =
        std::is_partitioned(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y = liuyunbin::is_partitioned(forward_list_1.cbegin(),
                                       forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::is_partitioned(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::is_partitioned(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 7, 9, 8, 6};
    auto f = [](int v) { return v < 5 ? true : false; };
    auto x = std::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::is_partitioned(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
}
