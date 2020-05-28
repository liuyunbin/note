
#include "remove.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_remove) {
  std::string str_1 = "12341234abcd";
  std::string str_2 = "12341234abcd";
  const char ch = '1';
  auto p1 = std::remove(str_1.begin(), str_1.end(), ch);
  liuyunbin::remove(str_2.begin(), str_2.end(), ch);
  EXPECT_TRUE(std::equal(str_1.begin(), p1, str_2.begin()));
}
