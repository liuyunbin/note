
#include "stable_sort.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_stable_sort) {
  std::string str_1 = "998653";
  std::string str_2 = "998653";
  std::stable_sort(str_1.begin(), str_1.end());
  liuyunbin::stable_sort(str_2.begin(), str_2.end());
  EXPECT_EQ(str_1, str_2);
}
