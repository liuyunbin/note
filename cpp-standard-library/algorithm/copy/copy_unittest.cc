
#include "copy.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_copy) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    std::forward_list<int> forward_list_3 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_4 = {5, 6, 7, 8, 9};
    std::copy(std::istream_iterator<int>(stream_1),
              std::istream_iterator<int>(), forward_list_3.begin());
    liuyunbin::copy(std::istream_iterator<int>(stream_2),
                    std::istream_iterator<int>(), forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
    std::copy(forward_list_1.cbegin(), forward_list_1.cend(),
              forward_list_2.begin());
    liuyunbin::copy(forward_list_1.cbegin(), forward_list_1.cend(),
                    forward_list_3.begin());
    EXPECT_EQ(forward_list_2, forward_list_3);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
    std::copy(list_1.cbegin(), list_1.cend(), forward_list_2.begin());
    liuyunbin::copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin());
    EXPECT_EQ(forward_list_2, forward_list_3);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_3 = {5, 6, 7, 8, 9};
    std::copy(vector_1.cbegin(), vector_1.cend(), forward_list_2.begin());
    liuyunbin::copy(vector_1.cbegin(), vector_1.cend(), forward_list_3.begin());
    EXPECT_EQ(forward_list_2, forward_list_3);
  }
}
