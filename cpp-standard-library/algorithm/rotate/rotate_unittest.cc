
#include "rotate.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_rotate) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  std::rotate(str_1.begin(), str_1.begin() + 3, str_1.end());
  liuyunbin::rotate(str_2.begin(), str_2.begin() + 3, str_2.end());
  EXPECT_EQ(str_1, str_2);
}
