
#include "unique.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_unique) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  auto p1 = std::unique(str_1.begin(), str_1.end());
  liuyunbin::unique(str_2.begin(), str_2.end());
  EXPECT_TRUE(std::equal(str_1.begin(), p1, str_2.begin()));
}
