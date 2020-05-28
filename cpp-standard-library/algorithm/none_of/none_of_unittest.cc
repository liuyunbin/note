
#include "none_of.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_none_of) {
  {
    std::string str = "abcdefghi";
    auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
    EXPECT_EQ(std::none_of(str.begin(), str.end(), f),
              liuyunbin::none_of(str.begin(), str.end(), f));
  }
  {
    std::string str = "abcdefghi123";
    auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
    EXPECT_EQ(std::none_of(str.begin(), str.end(), f),
              liuyunbin::none_of(str.begin(), str.end(), f));
  }
}
