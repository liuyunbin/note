
#include "replace_if.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_replace_if) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
  const char new_ch = '2';
  std::replace_if(str_1.begin(), str_1.end(), f, new_ch);
  liuyunbin::replace_if(str_2.begin(), str_2.end(), f, new_ch);
  EXPECT_EQ(str_1, str_2);
}
