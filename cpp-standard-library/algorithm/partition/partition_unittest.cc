
#include "partition.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partition) {
  {
    std::string str = "1234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    liuyunbin::partition(str.begin(), str.end(), f);
    EXPECT_EQ(std::is_partitioned(str.begin(), str.end(), f), true);
  }
  {
    std::string str = "1a234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    liuyunbin::partition(str.begin(), str.end(), f);
    EXPECT_EQ(std::is_partitioned(str.begin(), str.end(), f), true);
  }
}
