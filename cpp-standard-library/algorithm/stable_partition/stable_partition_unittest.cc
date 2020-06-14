
#include "stable_partition.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <iterator>
#include <list>
#include <numeric>
#include <sstream>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_stable_partition) {
  // 前向迭代器
  {
    std::forward_list<std::pair<char, std::string>> forward_list_1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::forward_list<std::pair<char, std::string>> forward_list_2(
        forward_list_1);

    auto f = [](const std::pair<char, std::string> &item) {
      return std::isdigit(item.first) ? true : false;
    };

    std::stable_partition(forward_list_1.begin(), forward_list_1.end(), f);
    liuyunbin::stable_partition(forward_list_2.begin(), forward_list_2.end(),
                                f);
    EXPECT_EQ(forward_list_1, forward_list_2);
  }

  // 双向迭代器
  {
    std::list<std::pair<char, std::string>> list_1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::list<std::pair<char, std::string>> list_2(list_1);

    auto f = [](const std::pair<char, std::string> &item) {
      return std::isdigit(item.first) ? true : false;
    };

    std::stable_partition(list_1.begin(), list_1.end(), f);
    liuyunbin::stable_partition(list_2.begin(), list_2.end(), f);

    EXPECT_EQ(list_1, list_2);
  }

  // 随机迭代器
  {
    std::vector<std::pair<char, std::string>> vector_1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::vector<std::pair<char, std::string>> vector_2(vector_1);

    auto f = [](const std::pair<char, std::string> &item) {
      return std::isdigit(item.first) ? true : false;
    };

    std::stable_partition(vector_1.begin(), vector_1.end(), f);
    liuyunbin::stable_partition(vector_2.begin(), vector_2.end(), f);

    EXPECT_EQ(vector_1, vector_2);
  }
}
