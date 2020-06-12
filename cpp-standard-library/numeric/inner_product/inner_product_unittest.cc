
#include "inner_product.h"

#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_numeric, test_inner_product) {
  // 输入迭代器
  {
    std::istringstream stream_1("0 1 2 3 4");
    std::istringstream stream_2("5 6 7 8 9");
    std::istringstream stream_3("0 1 2 3 4");
    std::istringstream stream_4("5 6 7 8 9");

    int a = 1;
    int x = std::inner_product(std::istream_iterator<int>(stream_1),
                               std::istream_iterator<int>(),
                               std::istream_iterator<int>(stream_2), a);
    int y = liuyunbin::inner_product(std::istream_iterator<int>(stream_3),
                                     std::istream_iterator<int>(),
                                     std::istream_iterator<int>(stream_4), a);
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {0, 1, 2, 3, 4};
    std::forward_list<int> forward_list_2 = {5, 6, 7, 8, 9};
    int a = 1;
    int x = std::inner_product(forward_list_1.cbegin(), forward_list_1.cend(),
                               forward_list_2.begin(), a);
    int y =
        liuyunbin::inner_product(forward_list_1.cbegin(), forward_list_1.cend(),
                                 forward_list_2.begin(), a);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {0, 1, 2, 3, 4};
    std::list<int> list_2 = {5, 6, 7, 8, 9};
    int a = 1;
    int x =
        std::inner_product(list_1.cbegin(), list_1.cend(), list_2.begin(), a);
    int y = liuyunbin::inner_product(list_1.cbegin(), list_1.cend(),
                                     list_2.begin(), a);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {0, 1, 2, 3, 4};
    std::vector<int> vector_2 = {5, 6, 7, 8, 9};
    int a = 1;
    int x = std::inner_product(vector_1.cbegin(), vector_1.cend(),
                               vector_2.begin(), a);
    int y = liuyunbin::inner_product(vector_1.cbegin(), vector_1.cend(),
                                     vector_2.begin(), a);
    EXPECT_EQ(x, y);
  }
}
