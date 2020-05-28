
#include "find_if_not.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find_if_not) {
  {
    std::string str = "abcdefghi";
    auto f = [](char ch) { return ch == 'g'; };
    EXPECT_EQ(std::find_if_not(str.begin(), str.end(), f),
              liuyunbin::find_if_not(str.begin(), str.end(), f));
  }
  {
    std::string str = "abcde";
    auto f = [](char ch) { return ch == 'g'; };
    EXPECT_EQ(std::find_if_not(str.begin(), str.end(), f),
              liuyunbin::find_if_not(str.begin(), str.end(), f));
  }
}
