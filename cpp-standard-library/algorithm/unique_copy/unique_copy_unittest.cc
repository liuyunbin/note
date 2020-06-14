
#include "unique_copy.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_unique_copy) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 1 2 2 3 4 5");
    std::istringstream stream_2("1 1 2 2 3 4 5");

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0};

    std::unique_copy(std::istream_iterator<int>(stream_1),
                     std::istream_iterator<int>(), forward_list_3.begin());
    liuyunbin::unique_copy(std::istream_iterator<int>(stream_2),
                           std::istream_iterator<int>(),
                           forward_list_4.begin());

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 1, 2, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

    std::unique_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                     forward_list_2.begin());
    liuyunbin::unique_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_3.begin());

    EXPECT_EQ(forward_list_2, forward_list_3);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 1, 2, 2, 3, 4, 5};

    std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

    std::unique_copy(list_1.cbegin(), list_1.cend(), forward_list_2.begin());
    liuyunbin::unique_copy(list_1.cbegin(), list_1.cend(),
                           forward_list_3.begin());

    EXPECT_EQ(forward_list_2, forward_list_3);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};

    std::forward_list<int> forward_list_2 = {0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0};

    std::unique_copy(vector_1.cbegin(), vector_1.cend(),
                     forward_list_2.begin());
    liuyunbin::unique_copy(vector_1.cbegin(), vector_1.cend(),
                           forward_list_3.begin());

    EXPECT_EQ(forward_list_2, forward_list_3);
  }
}
