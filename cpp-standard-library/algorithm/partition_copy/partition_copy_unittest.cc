
#include "partition_copy.h"

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

TEST(test_algorithm, test_partition_copy) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");
    auto f = [](int v) { return v < 5 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::partition_copy(std::istream_iterator<int>(stream_1),
                        std::istream_iterator<int>(), forward_list_3.begin(),
                        forward_list_4.begin(), f);
    std::partition_copy(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_5.begin(),
                        forward_list_6.begin(), f);
    EXPECT_EQ(forward_list_3, forward_list_5);
    EXPECT_EQ(forward_list_4, forward_list_6);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
    auto f = [](int v) { return v < 5 ? true : false; };

    std::partition_copy(forward_list_1.begin(), forward_list_1.end(),
                        forward_list_3.begin(), forward_list_4.begin(), f);
    std::partition_copy(forward_list_2.begin(), forward_list_2.end(),
                        forward_list_5.begin(), forward_list_6.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_5);
    EXPECT_EQ(forward_list_4, forward_list_6);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
    auto f = [](int v) { return v < 5 ? true : false; };

    std::partition_copy(list_1.begin(), list_1.end(), forward_list_3.begin(),
                        forward_list_4.begin(), f);
    std::partition_copy(list_2.begin(), list_2.end(), forward_list_5.begin(),
                        forward_list_6.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_5);
    EXPECT_EQ(forward_list_4, forward_list_6);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0};
    auto f = [](int v) { return v < 5 ? true : false; };

    std::partition_copy(vector_1.begin(), vector_1.end(),
                        forward_list_3.begin(), forward_list_4.begin(), f);
    std::partition_copy(vector_2.begin(), vector_2.end(),
                        forward_list_5.begin(), forward_list_6.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_5);
    EXPECT_EQ(forward_list_4, forward_list_6);
  }
}
