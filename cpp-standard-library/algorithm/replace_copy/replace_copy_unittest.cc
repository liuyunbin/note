
#include "replace_copy.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_replace_copy) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  const char old_ch = '1';
  const char new_ch = '1';
  std::replace_copy(str_1.begin(), str_1.end(), str_1.begin(), old_ch, new_ch);
  liuyunbin::replace_copy(str_2.begin(), str_2.end(), str_2.begin(), old_ch,
                          new_ch);
  EXPECT_EQ(str_1, str_2);
}
