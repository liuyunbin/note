
#include "inplace_merge.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_inplace_merge) {
  std::string str_1 = "acdfbdeghi";
  std::string str_2 = "acdfbdeghi";
  std::inplace_merge(str_1.begin(), str_1.begin() + 4, str_1.end());
  liuyunbin::inplace_merge(str_2.begin(), str_2.begin() + 4, str_2.end());
  EXPECT_EQ(str_1, str_2);
}
