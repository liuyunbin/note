
#include "for_each.h"

#include <algorithm>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_for_each) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");

    std::vector<int> ve_1;
    std::vector<int> ve_2;

    auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
    auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

    std::for_each(std::istream_iterator<int>(stream_1),
                  std::istream_iterator<int>(), f_1);
    liuyunbin::for_each(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), f_2);
    EXPECT_EQ(ve_1, ve_2);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};

    std::vector<int> ve_1;
    std::vector<int> ve_2;

    auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
    auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

    std::for_each(forward_list_1.cbegin(), forward_list_1.cend(), f_1);
    liuyunbin::for_each(forward_list_1.cbegin(), forward_list_1.cend(), f_2);
    EXPECT_EQ(ve_1, ve_2);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};

    std::vector<int> ve_1;
    std::vector<int> ve_2;

    auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
    auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

    std::for_each(list_1.cbegin(), list_1.cend(), f_1);
    liuyunbin::for_each(list_1.cbegin(), list_1.cend(), f_2);
    EXPECT_EQ(ve_1, ve_2);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};

    std::vector<int> ve_1;
    std::vector<int> ve_2;

    auto f_1 = [&ve_1](const int &v) { return ve_1.push_back(v); };
    auto f_2 = [&ve_2](const int &v) { return ve_2.push_back(v); };

    std::for_each(vector_1.cbegin(), vector_1.cend(), f_1);
    liuyunbin::for_each(vector_1.cbegin(), vector_1.cend(), f_2);
    EXPECT_EQ(ve_1, ve_2);
  }
}
