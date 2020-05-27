
#include "lower_bound.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_lower_bound) {
  {
    std::string str = "123456789";
    const char ch = '7';
    EXPECT_EQ(std::lower_bound(str.cbegin(), str.cend(), ch),
              liuyunbin::lower_bound(str.cbegin(), str.cend(), ch));
  }
  {
    std::string str = "123456789";
    const char ch = 'a';
    EXPECT_EQ(std::lower_bound(str.cbegin(), str.cend(), ch),
              liuyunbin::lower_bound(str.cbegin(), str.cend(), ch));
  }
}
