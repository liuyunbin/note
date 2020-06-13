
#include "replace_if.h"

#include <algorithm>
#include <forward_list>
#include <list>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_replace_if) {
  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::replace_if(forward_list_1.begin(), forward_list_1.end(), f, new_v);
    liuyunbin::replace_if(forward_list_2.begin(), forward_list_2.end(), f,
                          new_v);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::replace_if(forward_list_1.begin(), forward_list_1.end(), f, new_v);
    liuyunbin::replace_if(forward_list_2.begin(), forward_list_2.end(), f,
                          new_v);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::replace_if(list_1.begin(), list_1.end(), f, new_v);
    liuyunbin::replace_if(list_2.begin(), list_2.end(), f, new_v);
    EXPECT_EQ(list_1, list_2);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::replace_if(list_1.begin(), list_1.end(), f, new_v);
    liuyunbin::replace_if(list_2.begin(), list_2.end(), f, new_v);
    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::replace_if(vector_1.begin(), vector_1.end(), f, new_v);
    liuyunbin::replace_if(vector_2.begin(), vector_2.end(), f, new_v);
    EXPECT_EQ(vector_1, vector_2);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5};

    int new_v = 5;
    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::replace_if(vector_1.begin(), vector_1.end(), f, new_v);
    liuyunbin::replace_if(vector_2.begin(), vector_2.end(), f, new_v);
    EXPECT_EQ(vector_1, vector_2);
  }
}
