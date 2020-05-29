
#include "is_sorted.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_sorted) {
  std::string str = "1234abcd";
  EXPECT_EQ(std::is_sorted(str.begin(), str.end()),
            liuyunbin::is_sorted(str.begin(), str.end()));
}
