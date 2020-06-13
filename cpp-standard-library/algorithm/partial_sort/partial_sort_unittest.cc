
#include "partial_sort.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partial_sort) {
  // 随机迭代器
  std::string str_1 = "98653";
  std::string str_2 = "98653";
  std::partial_sort(str_1.begin(), str_1.begin() + 3, str_1.end());
  liuyunbin::partial_sort(str_2.begin(), str_2.begin() + 3, str_2.end());
  EXPECT_EQ(std::equal(str_1.begin(), str_1.begin() + 3, str_2.begin()), true);
}
