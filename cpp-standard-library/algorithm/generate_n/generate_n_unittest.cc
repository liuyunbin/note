
#include "generate_n.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_generate_n) {
  std::string str_1 = "abcdefghi";
  std::string str_2 = "abcdefghi";

  auto f = []() { return '1'; };

  const int n = 5;

  std::generate_n(str_1.begin(), n, f);
  liuyunbin::generate_n(str_2.begin(), n, f);
  EXPECT_EQ(str_1, str_2);
}
