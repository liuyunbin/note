
#include "is_permutation.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_is_permutation) {
    {
      std::string str_1 = "1234abcd";
      std::string str_2 = "1234abcd";
      EXPECT_EQ(
          std::is_permutation(str_1.begin(), str_1.end(), str_2.begin()),
          liuyunbin::is_permutation(str_1.begin(), str_1.end(), str_2.begin()));
    }
    {
      std::string str_1 = "1234abcd";
      std::string str_2 = "12341234";
      EXPECT_EQ(
          std::is_permutation(str_1.begin(), str_1.end(), str_2.begin()),
          liuyunbin::is_permutation(str_1.begin(), str_1.end(), str_2.begin()));
    }
}
