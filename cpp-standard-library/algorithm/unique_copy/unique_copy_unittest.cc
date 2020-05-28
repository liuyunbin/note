
#include "unique_copy.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_unique_copy) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  auto p1 = std::unique_copy(str_1.begin(), str_1.end(), str_1.begin());
  liuyunbin::unique_copy(str_2.begin(), str_2.end(), str_2.begin());
  EXPECT_TRUE(std::equal(str_1.begin(), p1, str_2.begin()));
}
