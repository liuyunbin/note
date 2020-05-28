
#include "remove_if.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_remove_if) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
  auto p1 = std::remove_if(str_1.begin(), str_1.end(), f);
  liuyunbin::remove_if(str_2.begin(), str_2.end(), f);
  EXPECT_TRUE(std::equal(str_1.begin(), p1, str_2.begin()));
}
