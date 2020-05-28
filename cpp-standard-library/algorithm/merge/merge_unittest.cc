
#include "merge.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_merge) {
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "abcdefghi";
    std::string str_3 = "1111111111111111111111111111";
    std::string str_4 = "1111111111111111111111111111";
    std::merge(str_1.begin(), str_1.end(), str_2.begin(), str_2.end(),
               str_3.begin());
    liuyunbin::merge(str_1.begin(), str_1.end(), str_2.begin(), str_2.end(),
                     str_4.begin());
    EXPECT_EQ(str_3, str_4);
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "abc1234";
    std::string str_3 = "1111111111111111111111111111";
    std::string str_4 = "1111111111111111111111111111";
    std::merge(str_1.begin(), str_1.end(), str_2.begin(), str_2.end(),
               str_3.begin());
    liuyunbin::merge(str_1.begin(), str_1.end(), str_2.begin(), str_2.end(),
                     str_4.begin());
    EXPECT_EQ(str_3, str_4);
  }
}
