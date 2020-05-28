
#include "search_n.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_search_n) {
  {
    std::string str = "abcabcdaa";
    const int n = 1;
    const char ch = 'a';
    EXPECT_EQ(std::search_n(str.begin(), str.end(), n, ch),
              liuyunbin::search_n(str.begin(), str.end(), n, ch));
  }
  {
    std::string str = "abcabcdaa";
    const int n = 2;
    const char ch = 'a';
    EXPECT_EQ(std::search_n(str.begin(), str.end(), n, ch),
              liuyunbin::search_n(str.begin(), str.end(), n, ch));
  }
  {
    std::string str = "abcabcdaa";
    const int n = 3;
    const char ch = 'a';
    EXPECT_EQ(std::search_n(str.begin(), str.end(), n, ch),
              liuyunbin::search_n(str.begin(), str.end(), n, ch));
  }
  {
    std::string str = "abcabcdaa";
    const int n = 1;
    const char ch = '1';
    EXPECT_EQ(std::search_n(str.begin(), str.end(), n, ch),
              liuyunbin::search_n(str.begin(), str.end(), n, ch));
  }
}
