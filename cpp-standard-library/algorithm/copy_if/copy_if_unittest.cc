
#include "copy_if.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_copy_if) {
  std::string str_from_1 = "1234abcd";
  std::string str_from_2 = "1234abcd";
  std::string str_to_1 = "abcd";
  std::string str_to_2 = "abcd";

  auto f = [](char ch) { return std::isdigit(ch) ? true : false; };

  std::copy_if(str_from_1.begin(), str_from_1.end(), str_to_1.begin(), f);
  liuyunbin::copy_if(str_from_2.begin(), str_from_2.end(), str_to_2.begin(), f);
  EXPECT_EQ(str_from_1, str_from_2);
  EXPECT_EQ(str_to_1, str_to_2);
}
