
#include "remove_copy_if.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_remove_copy_if) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::remove_copy_if(std::istream_iterator<int>(stream_1),
                        std::istream_iterator<int>(), forward_list_3.begin(),
                        f);
    std::remove_copy_if(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_4.begin(),
                        f);
    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

    auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::remove_copy_if(std::istream_iterator<int>(stream_1),
                        std::istream_iterator<int>(), forward_list_3.begin(),
                        f);
    std::remove_copy_if(std::istream_iterator<int>(stream_2),
                        std::istream_iterator<int>(), forward_list_4.begin(),
                        f);
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                        forward_list_3.begin(), f);
    std::remove_copy_if(forward_list_2.begin(), forward_list_2.end(),
                        forward_list_4.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(forward_list_1.cbegin(), forward_list_1.cend(),
                        forward_list_3.begin(), f);
    std::remove_copy_if(forward_list_2.begin(), forward_list_2.end(),
                        forward_list_4.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                        f);
    std::remove_copy_if(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                        f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                        f);
    std::remove_copy_if(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                        f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v < 3 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(vector_1.cbegin(), vector_1.cend(),
                        forward_list_3.begin(), f);
    std::remove_copy_if(vector_2.cbegin(), vector_2.cend(),
                        forward_list_4.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    auto f = [](const int &v) { return v > 10 ? true : false; };
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::remove_copy_if(vector_1.cbegin(), vector_1.cend(),
                        forward_list_3.begin(), f);
    std::remove_copy_if(vector_2.cbegin(), vector_2.cend(),
                        forward_list_4.begin(), f);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
