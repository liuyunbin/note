
#include "transform.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_transform) {
  {
    std::string str_1 = "1234abcdyy";
    std::string str_2 = "1234abcdyy";
    auto f = [](char ch) { return std::toupper(ch); };
    std::transform(str_1.begin(), str_1.end(), str_1.begin(), f);
    liuyunbin::transform(str_2.begin(), str_2.end(), str_2.begin(), f);
    EXPECT_EQ(str_1, str_2);
  }
  {
    std::string str_1 = "1234abcdyy";
    std::string str_2 = "1234abcdyy";
    auto f = [](char ch1, char ch2) { return std::toupper(ch1); };
    std::transform(str_1.begin(), str_1.end(), str_1.begin(), str_1.begin(), f);
    liuyunbin::transform(str_2.begin(), str_2.end(), str_2.begin(),
                         str_2.begin(), f);
    EXPECT_EQ(str_1, str_2);
  }
}
