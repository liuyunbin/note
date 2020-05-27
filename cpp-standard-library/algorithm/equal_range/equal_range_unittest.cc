
#include "equal_range.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_equal_range) {
  {
    std::string str = "123456789";
    const char ch = '7';
    EXPECT_EQ(std::equal_range(str.cbegin(), str.cend(), ch),
              liuyunbin::equal_range(str.cbegin(), str.cend(), ch));
  }
  {
    std::string str = "123456789";
    const char ch = 'a';
    EXPECT_EQ(std::equal_range(str.cbegin(), str.cend(), ch),
              liuyunbin::equal_range(str.cbegin(), str.cend(), ch));
  }
}
