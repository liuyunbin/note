
#include "find.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find) {
  {
    std::string str = "abcdefghi";
    const char ch = 'h';
    EXPECT_EQ(std::find(str.begin(), str.end(), ch),
              liuyunbin::find(str.begin(), str.end(), ch));
  }
  {
    std::string str = "abcdefghi";
    const char ch = '\0';
    EXPECT_EQ(std::find(str.begin(), str.end(), ch),
              liuyunbin::find(str.begin(), str.end(), ch));
  }
  {
    std::string str = "abcdefghi";
    const char ch = '1';
    EXPECT_EQ(std::find(str.begin(), str.end(), ch),
              liuyunbin::find(str.begin(), str.end(), ch));
  }
}
