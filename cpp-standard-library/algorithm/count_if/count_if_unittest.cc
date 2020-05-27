
#include "count_if.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_count_if) {
  std::string str = "12341234abcd";
  auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
  EXPECT_EQ(std::count_if(str.cbegin(), str.cend(), f),
            liuyunbin::count_if(str.cbegin(), str.cend(), f));
}
