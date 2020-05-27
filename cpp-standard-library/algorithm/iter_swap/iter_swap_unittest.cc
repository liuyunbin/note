
#include "iter_swap.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_iter_swap) {
  std::string str_1 = "1234";
  std::string str_2 = "1234";
  std::iter_swap(str_1.begin(), str_1.begin() + 1);
  liuyunbin::iter_swap(str_2.begin(), str_2.begin() + 1);
  EXPECT_EQ(str_1, str_2);
}
