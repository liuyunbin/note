
#include "remove.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_remove) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

    int v = 3;
    std::remove(forward_list_1.begin(), forward_list_1.end(), v);
    liuyunbin::remove(forward_list_2.begin(), forward_list_2.end(), v);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

    int v = 10;
    std::remove(forward_list_1.begin(), forward_list_1.end(), v);
    liuyunbin::remove(forward_list_2.begin(), forward_list_2.end(), v);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};

    int v = 3;
    std::remove(list_1.begin(), list_1.end(), v);
    liuyunbin::remove(list_2.begin(), list_2.end(), v);
    EXPECT_EQ(list_1, list_2);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};

    int v = 10;
    std::remove(list_1.begin(), list_1.end(), v);
    liuyunbin::remove(list_2.begin(), list_2.end(), v);
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};

    int v = 3;
    std::remove(vector_1.begin(), vector_1.end(), v);
    liuyunbin::remove(vector_2.begin(), vector_2.end(), v);
    EXPECT_EQ(vector_1, vector_2);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};

    int v = 10;
    std::remove(vector_1.begin(), vector_1.end(), v);
    liuyunbin::remove(vector_2.begin(), vector_2.end(), v);
    EXPECT_EQ(vector_1, vector_2);
  }
}
