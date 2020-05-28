
#include "remove_copy.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_remove_copy) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  const char ch = '1';
  auto p1 = std::remove_copy(str_1.begin(), str_1.end(), str_1.begin(), ch);
  liuyunbin::remove_copy(str_2.begin(), str_2.end(), str_2.begin(), ch);
  EXPECT_TRUE(std::equal(str_1.begin(), p1, str_2.begin()));
}
