
#include "adjacent_find.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_adjacent_find) {
  {
    std::string str = "abcdefghi";
    EXPECT_EQ(std::adjacent_find(str.begin(), str.end()),
              liuyunbin::adjacent_find(str.begin(), str.end()));
  }
  {
    std::string str = "abcddefghi";
    EXPECT_EQ(std::adjacent_find(str.begin(), str.end()),
              liuyunbin::adjacent_find(str.begin(), str.end()));
  }
}
