
#include "reverse.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_reverse) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  std::reverse(str_1.begin(), str_1.end());
  liuyunbin::reverse(str_2.begin(), str_2.end());
  EXPECT_EQ(str_1, str_2);
}
