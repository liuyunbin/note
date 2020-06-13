
#include "mismatch.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_mismatch) {
  // 输入迭代器 不好测试

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};

    auto x = std::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_2.cbegin());
    auto y = liuyunbin::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};

    auto x = std::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_1.cbegin());
    auto y = liuyunbin::mismatch(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_1.cbegin());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};

    auto x = std::mismatch(list_1.cbegin(), list_1.cend(), list_2.cbegin());
    auto y =
        liuyunbin::mismatch(list_1.cbegin(), list_1.cend(), list_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};

    auto x = std::mismatch(list_1.cbegin(), list_1.cend(), list_1.cbegin());
    auto y =
        liuyunbin::mismatch(list_1.cbegin(), list_1.cend(), list_1.cbegin());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};

    auto x =
        std::mismatch(vector_1.cbegin(), vector_1.cend(), vector_2.cbegin());
    auto y = liuyunbin::mismatch(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};

    auto x =
        std::mismatch(vector_1.cbegin(), vector_1.cend(), vector_1.cbegin());
    auto y = liuyunbin::mismatch(vector_1.cbegin(), vector_1.cend(),
                                 vector_1.cbegin());
    EXPECT_EQ(x, y);
  }
}
