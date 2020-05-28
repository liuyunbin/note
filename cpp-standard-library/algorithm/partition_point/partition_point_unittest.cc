
#include "partition_point.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partition_point) {
  std::string str = "1234abcd";
  auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
  EXPECT_EQ(std::partition_point(str.begin(), str.end(), f),
            liuyunbin::partition_point(str.begin(), str.end(), f));
}
