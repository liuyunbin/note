
#include "includes.h"

#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_includes) {
  // 输入迭代器
  {
    std::istringstream stream_1("0 1 2 3 4");
    std::istringstream stream_2("5 6 7 8 9");
    std::istringstream stream_3("0 1 2 3 4");
    std::istringstream stream_4("5 6 7 8 9");

    auto x = std::includes(
        std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
        std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
    auto y = liuyunbin::includes(
        std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
        std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("0 1 2 3 4");
    std::istringstream stream_2("2 3 4");
    std::istringstream stream_3("0 1 2 3 4");
    std::istringstream stream_4("2 3 4");

    auto x = std::includes(
        std::istream_iterator<int>(stream_1), std::istream_iterator<int>(),
        std::istream_iterator<int>(stream_2), std::istream_iterator<int>());
    auto y = liuyunbin::includes(
        std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
        std::istream_iterator<int>(stream_4), std::istream_iterator<int>());
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    auto x = std::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_2.cbegin(), forward_list_2.cend());
    auto y =
        liuyunbin::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {2, 3, 4};

    auto x = std::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_2.cbegin(), forward_list_2.cend());
    auto y =
        liuyunbin::includes(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    auto x = std::includes(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                           list_2.cend());
    auto y = liuyunbin::includes(list_1.cbegin(), list_1.cend(),
                                 list_2.cbegin(), list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {2, 3, 4};

    auto x = std::includes(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                           list_2.cend());
    auto y = liuyunbin::includes(list_1.cbegin(), list_1.cend(),
                                 list_2.cbegin(), list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    auto x = std::includes(vector_1.cbegin(), vector_1.cend(),
                           vector_2.cbegin(), vector_2.cend());
    auto y = liuyunbin::includes(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {2, 3, 4};

    auto x = std::includes(vector_1.cbegin(), vector_1.cend(),
                           vector_2.cbegin(), vector_2.cend());
    auto y = liuyunbin::includes(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
}
