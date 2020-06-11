
#include "accumulate.h"

#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_numeric, test_accumulate) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5");
    int a = 1;
    int x = std::accumulate(std::istream_iterator<int>(stream_1),
                            std::istream_iterator<int>(), a);
    int y = liuyunbin::accumulate(std::istream_iterator<int>(stream_2),
                                  std::istream_iterator<int>(), a);
    EXPECT_EQ(x, y);
  }
  {
    std::istringstream stream_1("0 12 3 45 6 789");
    std::istringstream stream_2("0 12 3 45 6 789");
    std::string str;
    std::string x =
        std::accumulate(std::istream_iterator<std::string>(stream_1),
                        std::istream_iterator<std::string>(), str);
    std::string y =
        liuyunbin::accumulate(std::istream_iterator<std::string>(stream_2),
                              std::istream_iterator<std::string>(), str);
    EXPECT_EQ(x, y);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5};
    int a = 1;
    int x = std::accumulate(forward_list_1.cbegin(), forward_list_1.cend(), a);
    int y = liuyunbin::accumulate(forward_list_1.cbegin(),
                                  forward_list_1.cend(), a);
    EXPECT_EQ(x, y);
  }
  {
    std::forward_list<std::string> forward_list_1 = {"0",  "12", "3",
                                                     "45", "6",  "789"};
    std::string str;
    std::string x =
        std::accumulate(forward_list_1.cbegin(), forward_list_1.cend(), str);
    std::string y = liuyunbin::accumulate(forward_list_1.cbegin(),
                                          forward_list_1.cend(), str);
    EXPECT_EQ(x, y);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5};
    int a = 1;
    int x = std::accumulate(list_1.cbegin(), list_1.cend(), a);
    int y = liuyunbin::accumulate(list_1.cbegin(), list_1.cend(), a);
    EXPECT_EQ(x, y);
  }
  {
    std::list<std::string> list_1 = {"0", "12", "3", "45", "6", "789"};
    std::string str;
    std::string x = std::accumulate(list_1.cbegin(), list_1.cend(), str);
    std::string y = liuyunbin::accumulate(list_1.cbegin(), list_1.cend(), str);
    EXPECT_EQ(x, y);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5};
    int a = 1;
    int x = std::accumulate(vector_1.cbegin(), vector_1.cend(), a);
    int y = liuyunbin::accumulate(vector_1.cbegin(), vector_1.cend(), a);
    EXPECT_EQ(x, y);
  }
  {
    std::vector<std::string> vector_1 = {"0", "12", "3", "45", "6", "789"};
    std::string str;
    std::string x = std::accumulate(vector_1.cbegin(), vector_1.cend(), str);
    std::string y =
        liuyunbin::accumulate(vector_1.cbegin(), vector_1.cend(), str);
    EXPECT_EQ(x, y);
  }
}
