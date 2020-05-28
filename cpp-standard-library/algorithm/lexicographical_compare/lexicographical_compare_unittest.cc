
#include "lexicographical_compare.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_lexicographical_compare) {
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "abcdefghi";
    EXPECT_EQ(std::lexicographical_compare(str_1.begin(), str_1.end(),
                                           str_2.begin(), str_2.end()),
              liuyunbin::lexicographical_compare(str_1.begin(), str_1.end(),
                                                 str_2.begin(), str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "defghi";
    EXPECT_EQ(std::lexicographical_compare(str_1.begin(), str_1.end(),
                                           str_2.begin(), str_2.end()),
              liuyunbin::lexicographical_compare(str_1.begin(), str_1.end(),
                                                 str_2.begin(), str_2.end()));
  }
  {
    std::string str_1 = "abcdefghi";
    std::string str_2 = "123456";
    EXPECT_EQ(std::lexicographical_compare(str_1.begin(), str_1.end(),
                                           str_2.begin(), str_2.end()),
              liuyunbin::lexicographical_compare(str_1.begin(), str_1.end(),
                                                 str_2.begin(), str_2.end()));
  }
}
