
#include "generate.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_generate) {
  std::string str_1 = "abcdefghi";
  std::string str_2 = "abcdefghi";

  auto f = []() { return '1'; };

  std::generate(str_1.begin(), str_1.end(), f);
  liuyunbin::generate(str_2.begin(), str_2.end(), f);
  EXPECT_EQ(str_1, str_2);
}
