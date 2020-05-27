
#include "fill_n.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_fill_n) {
  std::string str_1 = "123456789";
  std::string str_2 = "123456789";
  const char ch = '7';
  const int n = 5;
  std::fill_n(str_1.begin(), n, ch);
  liuyunbin::fill_n(str_2.begin(), n, ch);
  EXPECT_EQ(str_1, str_2);
}
