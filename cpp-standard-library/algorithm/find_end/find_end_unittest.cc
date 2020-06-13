
#include "find_end.h"

#include <forward_list>
#include <list>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find_end) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {1, 2, 3};

    auto x = std::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_2.cbegin(), forward_list_2.cend());
    auto y =
        liuyunbin::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4, 0, 2, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {1, 2, 4};

    auto x = std::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                           forward_list_2.cbegin(), forward_list_2.cend());
    auto y =
        liuyunbin::find_end(forward_list_1.cbegin(), forward_list_1.cend(),
                            forward_list_2.cbegin(), forward_list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    std::list<int> list_2 = {1, 2, 3};

    auto x = std::find_end(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                           list_2.cend());
    auto y = liuyunbin::find_end(list_1.cbegin(), list_1.cend(),
                                 list_2.cbegin(), list_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    std::list<int> list_2 = {1, 2, 4};

    auto x = std::find_end(list_1.cbegin(), list_1.cend(), list_2.cbegin(),
                           list_2.cend());
    auto y = liuyunbin::find_end(list_1.cbegin(), list_1.cend(),
                                 list_2.cbegin(), list_2.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {1, 2, 3};

    auto x = std::find_end(vector_1.cbegin(), vector_1.cend(),
                           vector_2.cbegin(), vector_2.cend());
    auto y = liuyunbin::find_end(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4, 0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {1, 2, 3};

    auto x = std::find_end(vector_1.cbegin(), vector_1.cend(),
                           vector_2.cbegin(), vector_2.cend());
    auto y = liuyunbin::find_end(vector_1.cbegin(), vector_1.cend(),
                                 vector_2.cbegin(), vector_2.cend());
    EXPECT_EQ(x, y);
  }
}
