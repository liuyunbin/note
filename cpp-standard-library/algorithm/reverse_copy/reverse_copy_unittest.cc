
#include "reverse_copy.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_reverse_copy) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  std::string str_3 = "12341234abcd";
  std::string str_4 = "12341234abcd";
  std::reverse_copy(str_1.begin(), str_1.end(), str_3.begin());
  liuyunbin::reverse_copy(str_2.begin(), str_2.end(), str_4.begin());
  EXPECT_EQ(str_1, str_2);
  EXPECT_EQ(str_3, str_4);
}
