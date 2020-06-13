
#include "find.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find) {
  // 输入迭代器 不好测试
  /*
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    int v = 3;
    auto x = std::find(std::istream_iterator<int>(stream_1),
                       std::istream_iterator<int>(), v);
    auto y = liuyunbin::find(std::istream_iterator<int>(stream_2),
                             std::istream_iterator<int>(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    int v = 10;
    auto x = std::find(std::istream_iterator<int>(stream_1),
                       std::istream_iterator<int>(), v);
    auto y = liuyunbin::find(std::istream_iterator<int>(stream_2),
                             std::istream_iterator<int>(), v);
    EXPECT_EQ(x, y);
  }
  */

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    int v = 3;
    auto x = std::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    int v = 10;
    auto x = std::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
    auto y = liuyunbin::find(forward_list_1.cbegin(), forward_list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    int v = 3;
    auto x = std::find(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::find(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    int v = 10;
    auto x = std::find(list_1.cbegin(), list_1.cend(), v);
    auto y = liuyunbin::find(list_1.cbegin(), list_1.cend(), v);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    int v = 3;
    auto x = std::find(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::find(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    int v = 10;
    auto x = std::find(vector_1.cbegin(), vector_1.cend(), v);
    auto y = liuyunbin::find(vector_1.cbegin(), vector_1.cend(), v);
    EXPECT_EQ(x, y);
  }
}
