
#include "all_of.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_all_of) {
  {
    std::string str = "abcdefghi";
    auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
    EXPECT_EQ(std::all_of(str.begin(), str.end(), f),
              liuyunbin::all_of(str.begin(), str.end(), f));
  }
  {
    std::string str = "abcdefghi123";
    auto f = [](char ch) { return std::isalpha(ch) ? true : false; };
    EXPECT_EQ(std::all_of(str.begin(), str.end(), f),
              liuyunbin::all_of(str.begin(), str.end(), f));
  }
}
