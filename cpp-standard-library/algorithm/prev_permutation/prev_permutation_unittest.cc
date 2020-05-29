
#include "prev_permutation.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_prev_permutation) {
  {
    std::string str_1 = "1234abcd";
    std::string str_2 = "1234abcd";
    std::prev_permutation(str_1.begin(), str_1.end());
    liuyunbin::prev_permutation(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
  {
    std::string str_1 = "1234dcba";
    std::string str_2 = "1234dcba";
    std::prev_permutation(str_1.begin(), str_1.end());
    liuyunbin::prev_permutation(str_2.begin(), str_2.end());
    EXPECT_EQ(str_1, str_2);
  }
}
