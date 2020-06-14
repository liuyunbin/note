
#include "set_difference.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_set_difference) {
  // 输入迭代器
  {
    std::istringstream stream_1("0 1 2 3 4");
    std::istringstream stream_2("1 3 5 5 6");
    std::istringstream stream_3("0 1 2 3 4");
    std::istringstream stream_4("1 3 5 5 6");

    std::forward_list<int> forward_list_5 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_6 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::set_difference(std::istream_iterator<int>(stream_1),
                        std::istream_iterator<int>(),
                        std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_5.begin());
    liuyunbin::set_difference(
        std::istream_iterator<int>(stream_3), std::istream_iterator<int>(),
        std::istream_iterator<int>(stream_4), std::istream_iterator<int>(),
        forward_list_6.begin());
    EXPECT_EQ(forward_list_5, forward_list_6);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {1, 3, 5, 5, 6};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::set_difference(forward_list_1.cbegin(), forward_list_1.cend(),
                        forward_list_2.cbegin(), forward_list_2.cend(),
                        forward_list_3.begin());
    liuyunbin::set_difference(forward_list_1.cbegin(), forward_list_1.cend(),
                              forward_list_2.cbegin(), forward_list_2.cend(),
                              forward_list_4.begin());
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {1, 3, 5, 5, 6};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::set_difference(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                        list_2.cend(), forward_list_3.begin());
    liuyunbin::set_difference(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                              list_2.cend(), forward_list_4.begin());

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {1, 3, 5, 5, 6};

    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::set_difference(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin(),
                        vector_2.cend(), forward_list_3.begin());

    liuyunbin::set_difference(vector_1.cbegin(), vector_1.cend(),
                              vector_2.cbegin(), vector_2.cend(),
                              forward_list_4.begin());

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
