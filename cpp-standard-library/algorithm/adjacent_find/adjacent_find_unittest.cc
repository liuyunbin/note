
#include "adjacent_find.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_adjacent_find) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    auto x = std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                      forward_list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 2, 3, 3, 4, 5};
    auto x = std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                      forward_list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<std::string> forward_list_1 = {"0",  "12", "3",
                                                     "45", "6",  "789"};
    auto x = std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                      forward_list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<std::string> forward_list_1 = {"0",  "12", "3", "3",
                                                     "45", "45", "6", "789"};
    auto x = std::adjacent_find(forward_list_1.cbegin(), forward_list_1.cend());
    auto y = liuyunbin::adjacent_find(forward_list_1.cbegin(),
                                      forward_list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<int> list_1 = {1, 2, 2, 3, 3, 4, 5};
    auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<std::string> list_1 = {"0", "12", "3", "45", "6", "789"};
    auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::list<std::string> list_1 = {"0",  "12", "3", "3",
                                     "45", "45", "6", "789"};
    auto x = std::adjacent_find(list_1.cbegin(), list_1.cend());
    auto y = liuyunbin::adjacent_find(list_1.cbegin(), list_1.cend());
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<int> vector_1 = {1, 2, 2, 3, 3, 4, 5};
    auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<std::string> vector_1 = {"0", "12", "3", "45", "6", "789"};
    auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
  {
    std::vector<std::string> vector_1 = {"0",  "12", "3", "3",
                                         "45", "45", "6", "789"};
    auto x = std::adjacent_find(vector_1.cbegin(), vector_1.cend());
    auto y = liuyunbin::adjacent_find(vector_1.cbegin(), vector_1.cend());
    EXPECT_EQ(x, y);
  }
}
