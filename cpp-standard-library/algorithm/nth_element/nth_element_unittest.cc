
#include "nth_element.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_nth_element) {
  // 随机迭代器
  std::string str_1 = "246810";
  std::string str_2 = "864210";
  std::nth_element(str_1.begin(), str_1.begin() + 3, str_1.end());
  liuyunbin::nth_element(str_2.begin(), str_2.begin() + 3, str_2.end());
  EXPECT_EQ(str_1[2], str_2[2]);
}
