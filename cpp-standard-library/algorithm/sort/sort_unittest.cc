
#include "sort.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_sort) {
  std::string str_1 = "98653";
  std::string str_2 = "98653";
  std::sort(str_1.begin(), str_1.end());
  liuyunbin::sort(str_2.begin(), str_2.end());
  EXPECT_EQ(str_1, str_2);
}
