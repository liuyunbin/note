
#include "stable_partition.h"

#include <algorithm>
#include <cctype>
#include <forward_list>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_stable_partition) {
  {
    std::vector<std::pair<char, std::string>> ve1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::vector<std::pair<char, std::string>> ve2(ve1);

    auto f = [](const std::pair<char, std::string> &item) {
      return std::isdigit(item.first) ? true : false;
    };
    std::stable_partition(ve1.begin(), ve1.end(), f);
    liuyunbin::stable_partition(ve2.begin(), ve2.end(), f);
    EXPECT_EQ(ve1, ve2);
  }
  {
    std::forward_list<std::pair<char, std::string>> ve1 = {
        {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
        {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
        {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
    };
    std::forward_list<std::pair<char, std::string>> ve2(ve1);

    auto f = [](const std::pair<char, std::string> &item) {
      return std::isdigit(item.first) ? true : false;
    };
    std::stable_partition(ve1.begin(), ve1.end(), f);
    liuyunbin::stable_partition(ve2.begin(), ve2.end(), f);
    EXPECT_EQ(ve1, ve2);
  }
}
