
#include "for_each.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_for_each) {
  std::string str_1 = "abcdefghi";
  std::string str_2 = "abcdefghi";

  auto f = [](char &ch) { return ch = std::toupper(ch); };

  std::for_each(str_1.begin(), str_1.end(), f);
  liuyunbin::for_each(str_2.begin(), str_2.end(), f);
  EXPECT_EQ(str_1, str_2);
}
