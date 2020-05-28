
#include "is_partitioned.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_partitioned) {
  {
    std::string str = "1234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    EXPECT_EQ(std::is_partitioned(str.begin(), str.end(), f),
              liuyunbin::is_partitioned(str.begin(), str.end(), f));
  }
  {
    std::string str = "1a234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    EXPECT_EQ(std::is_partitioned(str.begin(), str.end(), f),
              liuyunbin::is_partitioned(str.begin(), str.end(), f));
  }
}
