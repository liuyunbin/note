
#include "find_first_of.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_find_first_of) {
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "abcdefghi";
    EXPECT_EQ(std::find_first_of(str_1.begin(), str_1.end(), str_2.begin(),
                                 str_2.end()),
              liuyunbin::find_first_of(str_1.begin(), str_1.end(),
                                       str_2.begin(), str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "de";
    EXPECT_EQ(std::find_first_of(str_1.begin(), str_1.end(), str_2.begin(),
                                 str_2.end()),
              liuyunbin::find_first_of(str_1.begin(), str_1.end(),
                                       str_2.begin(), str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "123";
    EXPECT_EQ(std::find_first_of(str_1.begin(), str_1.end(), str_2.begin(),
                                 str_2.end()),
              liuyunbin::find_first_of(str_1.begin(), str_1.end(),
                                       str_2.begin(), str_2.end()));
  }
}
