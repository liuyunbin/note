
#include "replace.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_replace) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  const char old_ch = '1';
  const char new_ch = '2';
  std::replace(str_1.begin(), str_1.end(), old_ch, new_ch);
  liuyunbin::replace(str_2.begin(), str_2.end(), old_ch, new_ch);
  EXPECT_EQ(str_1, str_2);
}
