
#include "replace_copy.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_replace_copy) {
  // 输入迭代器
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

    int old_v = 3;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::replace_copy(std::istream_iterator<int>(stream_1),
                      std::istream_iterator<int>(), forward_list_3.begin(),
                      old_v, new_v);
    std::replace_copy(std::istream_iterator<int>(stream_2),
                      std::istream_iterator<int>(), forward_list_4.begin(),
                      old_v, new_v);
    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::istringstream stream_1("1 2 3 4 5 1 2 3 4 5");
    std::istringstream stream_2("1 2 3 4 5 1 2 3 4 5");

    int old_v = 10;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::replace_copy(std::istream_iterator<int>(stream_1),
                      std::istream_iterator<int>(), forward_list_3.begin(),
                      old_v, new_v);
    std::replace_copy(std::istream_iterator<int>(stream_2),
                      std::istream_iterator<int>(), forward_list_4.begin(),
                      old_v, new_v);
    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 前向迭代器
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 3;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                      forward_list_3.begin(), old_v, new_v);
    std::replace_copy(forward_list_2.begin(), forward_list_2.end(),
                      forward_list_4.begin(), old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::forward_list<int> forward_list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::forward_list<int> forward_list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 10;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(forward_list_1.cbegin(), forward_list_1.cend(),
                      forward_list_3.begin(), old_v, new_v);
    std::replace_copy(forward_list_2.begin(), forward_list_2.end(),
                      forward_list_4.begin(), old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 双向迭代器
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 3;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                      old_v, new_v);
    std::replace_copy(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                      old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::list<int> list_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::list<int> list_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 10;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(list_1.cbegin(), list_1.cend(), forward_list_3.begin(),
                      old_v, new_v);
    std::replace_copy(list_2.cbegin(), list_2.cend(), forward_list_4.begin(),
                      old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }

  // 随机迭代器
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 3;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(vector_1.cbegin(), vector_1.cend(),
                      forward_list_3.begin(), old_v, new_v);
    std::replace_copy(vector_2.cbegin(), vector_2.cend(),
                      forward_list_4.begin(), old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
  {
    std::vector<int> vector_1 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    std::vector<int> vector_2 = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};

    int old_v = 10;
    int new_v = 5;
    std::forward_list<int> forward_list_3 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::forward_list<int> forward_list_4 = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    std::replace_copy(vector_1.cbegin(), vector_1.cend(),
                      forward_list_3.begin(), old_v, new_v);
    std::replace_copy(vector_2.cbegin(), vector_2.cend(),
                      forward_list_4.begin(), old_v, new_v);

    EXPECT_EQ(forward_list_3, forward_list_4);
  }
}
