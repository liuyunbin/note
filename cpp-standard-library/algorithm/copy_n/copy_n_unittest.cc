
#include "copy_n.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_copy_n) {
  std::string str_from_1 = "1234";
  std::string str_from_2 = "1234";
  std::string str_to_1 = "abcd";
  std::string str_to_2 = "abcd";
  const int n = 3;
  std::copy_n(str_from_1.begin(), n, str_to_1.begin());
  liuyunbin::copy_n(str_from_2.begin(), n, str_to_2.begin());
  EXPECT_EQ(str_from_1, str_from_2);
  EXPECT_EQ(str_to_1, str_to_2);
}
