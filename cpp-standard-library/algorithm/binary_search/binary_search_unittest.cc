
#include "binary_search.h"

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

TEST(test_algorithm, test_binary_search) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5 6 7 8 9");
    std::istringstream stream_2("1 2 3 4 5 6 7 8 9");
    int v = 5;
    auto x = std::binary_search(std::istream_iterator<int>(stream_1),
                                std::istream_iterator<int>(), v);
    auto y = liuyunbin::binary_search(std::istream_iterator<int>(stream_2),
                                      std::istream_iterator<int>(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 6 7 8 9");
    std::istringstream stream_2("1 2 3 4 6 7 8 9");
    int v = 5;
    auto x = std::binary_search(std::istream_iterator<int>(stream_1),
                                std::istream_iterator<int>(), v);
    auto y = liuyunbin::binary_search(std::istream_iterator<int>(stream_2),
                                      std::istream_iterator<int>(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 5 6 7 8 9");
    std::istringstream stream_2("1 2 3 4 5 6 7 8 9");
    char ch = '5';
    auto x = std::binary_search(std::istream_iterator<char>(stream_1),
                                std::istream_iterator<char>(), ch);
    auto y = liuyunbin::binary_search(std::istream_iterator<char>(stream_2),
                                      std::istream_iterator<char>(), ch);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 6 7 8 9");
    std::istringstream stream_2("1 2 3 4 6 7 8 9");
    char ch = '5';
    auto x = std::binary_search(std::istream_iterator<char>(stream_1),
                                std::istream_iterator<char>(), ch);
    auto y = liuyunbin::binary_search(std::istream_iterator<char>(stream_2),
                                      std::istream_iterator<char>(), ch);
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v = 5;
    auto x =
        std::binary_search(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                      forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 6, 7, 8, 9};
    int v = 5;
    auto x =
        std::binary_search(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                      forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<char> forward_list_1 = {'1', '2', '3', '4', '5',
                                              '6', '7', '8', '9'};
    char ch = '5';
    auto x =
        std::binary_search(forward_list_1.cbegin(), forward_list_1.cend(), ch);
    auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                      forward_list_1.cend(), ch);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<char> forward_list_1 = {'1', '2', '3', '4',
                                              '6', '7', '8', '9'};
    char ch = '5';
    auto x =
        std::binary_search(forward_list_1.cbegin(), forward_list_1.cend(), ch);
    auto y = liuyunbin::binary_search(forward_list_1.cbegin(),
                                      forward_list_1.cend(), ch);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v = 5;
    auto x = std::binary_search(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 6, 7, 8, 9};
    int v = 5;
    auto x = std::binary_search(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<char> list_1 = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char ch = '5';
    auto x = std::binary_search(list_1.cbegin(), list_1.cend(), ch);
    auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), ch);
    EXPECT_EQ(x, y);
  }
  {
    std::list<char> list_1 = {'1', '2', '3', '4', '6', '7', '8', '9'};
    char ch = '5';
    auto x = std::binary_search(list_1.cbegin(), list_1.cend(), ch);
    auto y = liuyunbin::binary_search(list_1.cbegin(), list_1.cend(), ch);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int v = 5;
    auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 6, 7, 8, 9};
    int v = 5;
    auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<char> vector_1 = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char ch = '5';
    auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
    auto y = liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<char> vector_1 = {'1', '2', '3', '4', '6', '7', '8', '9'};
    char ch = '5';
    auto x = std::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
    auto y = liuyunbin::binary_search(vector_1.cbegin(), vector_1.cend(), ch);
    EXPECT_EQ(x, y);
  }
}
