
#include "count_if.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_count_if) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    auto f = [](int v) { return v < 3 ? true : false; };
    auto x = std::count_if(std::istream_iterator<int>(stream_1),
                           std::istream_iterator<int>(), f);
    auto y = liuyunbin::count_if(std::istream_iterator<int>(stream_2),
                                 std::istream_iterator<int>(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    auto f = [](int v) { return v < 0 ? true : false; };
    auto x = std::count_if(std::istream_iterator<int>(stream_1),
                           std::istream_iterator<int>(), f);
    auto y = liuyunbin::count_if(std::istream_iterator<int>(stream_2),
                                 std::istream_iterator<int>(), f);
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3 ? true : false; };
    auto x = std::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y =
        liuyunbin::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 0 ? true : false; };
    auto x = std::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
    auto y =
        liuyunbin::count_if(forward_list_1.cbegin(), forward_list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3 ? true : false; };
    auto x = std::count_if(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::count_if(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 0 ? true : false; };
    auto x = std::count_if(list_1.cbegin(), list_1.cend(), f);
    auto y = liuyunbin::count_if(list_1.cbegin(), list_1.cend(), f);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 3 ? true : false; };
    auto x = std::count_if(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::count_if(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto f = [](int v) { return v < 0 ? true : false; };
    auto x = std::count_if(vector_1.cbegin(), vector_1.cend(), f);
    auto y = liuyunbin::count_if(vector_1.cbegin(), vector_1.cend(), f);
    EXPECT_EQ(x, y);
  }
}
