
#include "stable_sort.h"

#include <algorithm>
#include <string>
#include <vector>

#include <gtest/gtest.h>

TEST(test_algorithm, test_stable_sort) {
  // 随机迭代器
  std::vector<std::pair<char, std::string>> vector_1 = {
      {'1', "100"}, {'2', "102"}, {'3', "103"}, {'4', "104"}, {'a', "105"},
      {'b', "106"}, {'c', "107"}, {'d', "108"}, {'1', "109"}, {'2', "110"},
      {'e', "111"}, {'f', "112"}, {'g', "113"}, {'1', "114"}, {'2', "115"},
  };
  std::vector<std::pair<char, std::string>> vector_2(vector_1);

  std::stable_sort(vector_1.begin(), vector_1.end());
  liuyunbin::stable_sort(vector_2.begin(), vector_2.end());
  EXPECT_EQ(vector_1, vector_2);
}
