
#include "binary_search.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_binary_search) {
  {
    std::string str = "123456789";
    const char ch = '7';
    EXPECT_EQ(std::binary_search(str.cbegin(), str.cend(), ch),
              liuyunbin::binary_search(str.cbegin(), str.cend(), ch));
  }
  {
    std::string str = "123456789";
    const char ch = 'a';
    EXPECT_EQ(std::binary_search(str.cbegin(), str.cend(), ch),
              liuyunbin::binary_search(str.cbegin(), str.cend(), ch));
  }
}
