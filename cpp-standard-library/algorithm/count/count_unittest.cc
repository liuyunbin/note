
#include "count.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_count) {
  std::string str = "12341234";
  char ch = '1';
  EXPECT_EQ(std::count(str.cbegin(), str.cend(), ch),
            liuyunbin::count(str.cbegin(), str.cend(), ch));
}
