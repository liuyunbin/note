
#include "partition_copy.h"

#include <algorithm>
#include <cctype>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_partition_copy) {
  {
    std::string str_1 = "1234abcd";
    std::string str_2 = "1234abcd";
    std::string str_3 = "1234abcd";
    std::string str_4 = "1234abcd";
    std::string str_5 = "1234abcd";
    std::string str_6 = "1234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    std::partition_copy(str_1.begin(), str_1.end(), str_2.begin(),
                        str_3.begin(), f);
    liuyunbin::partition_copy(str_4.begin(), str_4.end(), str_5.begin(),
                              str_6.begin(), f);
    EXPECT_EQ(str_2, str_5);
    EXPECT_EQ(str_3, str_6);
  }
  {
    std::string str_1 = "1a234abcd";
    std::string str_2 = "1a234abcd";
    std::string str_3 = "1a234abcd";
    std::string str_4 = "1a234abcd";
    std::string str_5 = "1a234abcd";
    std::string str_6 = "1a234abcd";
    auto f = [](char ch) { return std::isdigit(ch) ? true : false; };
    std::partition_copy(str_1.begin(), str_1.end(), str_2.begin(),
                        str_3.begin(), f);
    liuyunbin::partition_copy(str_4.begin(), str_4.end(), str_5.begin(),
                              str_6.begin(), f);
    EXPECT_EQ(str_2, str_5);
    EXPECT_EQ(str_3, str_6);
  }
}
