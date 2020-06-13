
#include "merge.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_merge) {
  // 输入迭代器
  {
    std::istringstream stream_1("0 1 2 3 4");
    std::istringstream stream_2("5 6 7 8 9");
    std::istringstream stream_3("0 1 2 3 4");
    std::istringstream stream_4("5 6 7 8 9");

    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::merge(std::istream_iterator<int>(stream_1),
               std::istream_iterator<int>(),
               std::istream_iterator<int>(stream_2),
               std::istream_iterator<int>(), forward_list_5.begin());
    liuyunbin::merge(std::istream_iterator<int>(stream_3),
                     std::istream_iterator<int>(),
                     std::istream_iterator<int>(stream_4),
                     std::istream_iterator<int>(), forward_list_6.begin());
    EXPECT_EQ(forward_list_5, forward_list_6);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::merge(forward_list_1.cbegin(), forward_list_1.cend(),
               forward_list_2.cbegin(), forward_list_2.cend(),
               forward_list_3.begin());
    liuyunbin::merge(forward_list_1.cbegin(), forward_list_1.cend(),
                     forward_list_2.cbegin(), forward_list_2.cend(),
                     forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::merge(list_1.cbegin(), list_1.cend(), list_2.cbegin(), list_2.cend(),
               forward_list_3.begin());
    liuyunbin::merge(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                     list_2.cend(), forward_list_4.begin());

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1};

    std::merge(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
               vector_2.cend(), forward_list_3.begin());

    liuyunbin::merge(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                     vector_2.cend(), forward_list_4.begin());

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
