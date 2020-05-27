
#include "fill.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_fill) {
  std::string str_1 = "123456789";
  std::string str_2 = "123456789";
  const char ch = '7';
  std::fill(str_1.begin(), str_1.end(), ch);
  liuyunbin::fill(str_2.begin(), str_2.end(), ch);
  EXPECT_EQ(str_1, str_2);
}
