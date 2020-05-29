
#include "is_sorted_until.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_sorted_until) {
  std::string str = "1234abcd";
  EXPECT_EQ(std::is_sorted_until(str.begin(), str.end()),
            liuyunbin::is_sorted_until(str.begin(), str.end()));
}
