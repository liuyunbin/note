
#include "swap_ranges.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_swap_ranges) {
  std::string str_lhs_1 = "1234";
  std::string str_lhs_2 = "1234";
  std::string str_rhs_1 = "abcd";
  std::string str_rhs_2 = "abcd";
  std::swap_ranges(str_lhs_1.begin(), str_lhs_1.end(), str_rhs_1.begin());
  liuyunbin::swap_ranges(str_lhs_2.begin(), str_lhs_2.end(), str_rhs_2.begin());
  EXPECT_EQ(str_lhs_1, str_lhs_2);
  EXPECT_EQ(str_rhs_1, str_rhs_2);
}
