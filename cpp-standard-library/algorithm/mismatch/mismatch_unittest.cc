
#include "mismatch.h"

#include <algorithm>
#include <string>

#include <gtest/gtest.h>

TEST(test_algorithm, test_mismatch) {
  {
    std::string str_1 = "acdfbdeghi";
    std::string str_2 = "acdfbdeghi";
    EXPECT_EQ(std::mismatch(str_1.begin(), str_1.end(), str_2.begin()),
              liuyunbin::mismatch(str_1.begin(), str_1.end(), str_2.begin()));
  }
  {
    std::string str_1 = "acdfbdeghi";
    std::string str_2 = "acdfbdegh1";
    EXPECT_EQ(std::mismatch(str_1.begin(), str_1.end(), str_2.begin()),
              liuyunbin::mismatch(str_1.begin(), str_1.end(), str_2.begin()));
  }
  {
    std::string str_1 = "acdfbdeghi";
    std::string str_2 = "1cdfbdeghi";
    EXPECT_EQ(std::mismatch(str_1.begin(), str_1.end(), str_2.begin()),
              liuyunbin::mismatch(str_1.begin(), str_1.end(), str_2.begin()));
  }
}
