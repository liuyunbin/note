
#include "find_end.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find_end) {
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "abcdefghi";
    EXPECT_EQ(
        std::find_end(str_1.begin(), str_1.end(), str_2.begin(), str_2.end()),
        liuyunbin::find_end(str_1.begin(), str_1.end(), str_2.begin(),
                            str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "defghi";
    EXPECT_EQ(
        std::find_end(str_1.begin(), str_1.end(), str_2.begin(), str_2.end()),
        liuyunbin::find_end(str_1.begin(), str_1.end(), str_2.begin(),
                            str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "123456";
    EXPECT_EQ(
        std::find_end(str_1.begin(), str_1.end(), str_2.begin(), str_2.end()),
        liuyunbin::find_end(str_1.begin(), str_1.end(), str_2.begin(),
                            str_2.end()));
  }
  {
    std::string str_1 = "abcdabcd";
    std::string str_2 = "abcd";
    EXPECT_EQ(
        std::find_end(str_1.begin(), str_1.end(), str_2.begin(), str_2.end()),
        liuyunbin::find_end(str_1.begin(), str_1.end(), str_2.begin(),
                            str_2.end()));
  }
}
